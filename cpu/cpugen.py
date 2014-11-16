from opcodes import opcodes

import re, sys
from pprint import pprint
from sets import Set

def matcher(regexp):
	regexp = re.compile(regexp)

	def sub(data):
		match = regexp.match(data)
		if match == None:
			return None
		return match.group(0)
	return sub

hex = matcher(r'0x[0-9a-fA-F]+')
number = matcher(r'-?[0-9]+')
name = matcher(r'[a-zA-Z\-_+*/<>\[\]=\^&|%~!][a-zA-Z0-9\-_+*/<>\[\]=\^&|%~!]*')

def parseAtom(code):
	code = code.lstrip()
	if code[0] == '(':
		code = code[1:].lstrip()
		atom = []
		while code[0] != ')':
			val, code = parseAtom(code)
			code = code.lstrip()
			atom.append(val)
		return atom, code[1:]
	if hex(code):
		val = hex(code)
		return int(val[2:], 16), code[len(val):]
	elif number(code):
		val = number(code)
		return int(val), code[len(val):]
	elif name(code):
		val = name(code)
		return val, code[len(val):]
	else:
		print 'bailing!'
		print code
		sys.exit(1)

def parse_instructions():
	atom, rest = parseAtom(file('cpu.def').read())
	assert rest.strip() == ''
	assert atom[0] == 'cpu'

	insns = {}

	for elem in atom[1:]:
		assert elem[0] == 'insn'
		insns[elem[1]] = elem[2], elem[3:]

	return insns

def setter(type, value):
	return 'Builder.CreateStore(%s, %s)' % (value, 0)

def getter(type):
	#return type
	return '0'

def emit(atom, op_map):
	if not isinstance(atom, list):
		if atom in op_map:
			return getter(op_map[atom])
		else:
			print 'foo?', atom
			assert False

	if atom[0] == 'set':
		dest, src = atom[1:]
		print >>insns, '\t' + setter(op_map[dest], emit(src, op_map)) + ';'
		return dest
	elif atom[0] in '+-':
		a, b = atom[1:]
		return 'Builder.Create%s(%s, %s)' % ({'+':'Add', '-':'Sub'}[atom[0]], emit(a, op_map), emit(b, op_map))
	else:
		print 'unk', atom
		assert False

def insn_func(name, ops):
	return '%s%s' % (name, ('_'+'_'.join(ops)) if ops else '')

def emit_instruction(name, ops, args, body):
	print >>decl, 'void', insn_func(name, ops) + '();'
	print >>insns, 'void InstructionDispatcher::' + insn_func(name, ops) + '() {'
	print >>insns, '\tprintf("%r\\n");' % ((name, ops, args, body), )

	op_map = dict((arg, ops[i]) for i, arg in enumerate(args))

	for elem in body:
		emit(elem, op_map)
	print >>insns, '}'

decl = file('instruction_decl.hpp', 'w')
insns = file('instructions_gen.cpp', 'w')
print >>insns, '#include "InstructionDispatcher.hpp"'

_insns = parse_instructions()
stubs = []

opcode_groups = {None: {}}

for opcd, (name, ops) in opcodes.items():
	if name not in _insns:
		if name not in stubs:
			#print 'Undefined', name
			stubs.append(name)
		continue

	emit_instruction(name, ops, *_insns[name])

	if isinstance(opcd, tuple):
		assert False
	else:
		opcode_groups[None][opcd] = insn_func(name, ops)

def emit_group(fp, switch, elems, depth):
	print >>fp, '\t'*depth+'switch(%s) {' % switch
	for opcd, func in elems.items():
		print >>fp, '\t'*depth+'case 0x%02x:' % opcd
		print >>fp, '\t'*depth+'\t%s();' % func
		print >>fp, '\t'*depth+'\tbreak;'
	print >>fp, '\t'*depth+'default:'
	print >>fp, '\t'*depth+'\tprintf("Unknown opcode %%02x\\n", %s);' % switch
	print >>fp, '\t'*depth+'\tassert(false);'
	print >>fp, '\t'*depth+'}'

with file('dispatcher_gen.cpp', 'w') as fp:
	emit_group(fp, 'opcode_1', opcode_groups[None], 0)
