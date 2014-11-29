from opcodes import opcodes

import re, sys
from pprint import pprint
from sets import Set
from cStringIO import StringIO

import os.path

files = 'cpugen.py opcodes.py opcodes.txt cpu.def'
comp = os.path.getmtime('dispatcher_gen.cpp')

newer = False
for fn in files.split(' '):
	if os.path.getmtime(fn) > comp:
		newer = True
if not newer:
	print 'cpugen up to date'
	sys.exit()

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

baseregs = 'ip ax cx dx bx sp bp si di flags'.split(' ')
def reg(name):
	global notimp
	if name.startswith('e') and name[1:] in baseregs:
		return 'Builder.CreateStructGEP(stateArg, %i)' % baseregs.index(name[1:])
	else:
		notimp = True
		return '0'

def setter(type, value):
	global notimp
	if type.endswith('AX'):
		dest = reg('eax')
	elif type == 'Gv':
		dest = 'GetReg(OperandSize())'
	elif type == 'Ev':
		dest = 'GetRM(OperandSize())'
	else:
		notimp = True
		dest = '0'
	return 'Builder.CreateStore(%s, %s)' % (value, dest)

def getter(type):
	global notimp
	if type in ('Iv', 'Iz', 'Jz'):
		return 'GetImmediateOp32()'
	elif type == 'Ov':
		return 'Builder.CreateLoad(CreatePointer(GetImmediateOp32(), 32))'
	elif type in ('Ib', 'Jb'):
		return 'GetImmediateOp8()'
	elif type.endswith('AX'):
		return 'Builder.CreateLoad(%s)' % reg('eax')
	elif type == 'Gv':
		return 'Builder.CreateLoad(GetReg(OperandSize()))'
	elif type == 'Ev':
		return 'Builder.CreateLoad(GetRM(OperandSize()))'
	else:
		notimp = True
		return '0'

def emit(atom, op_map):
	global branches, notimp
	if not isinstance(atom, list):
		if atom in op_map:
			return getter(op_map[atom])
		else:
			print 'Unknown', atom
			assert False

	if atom[0] == 'set':
		dest, src = atom[1:]
		print >>insns, '\t' + setter(op_map[dest], emit(src, op_map)) + ';'
		return dest
	elif atom[0] in '+-':
		a, b = atom[1:]
		if emit(a, op_map) == '0' or emit(b, op_map) == '0':
			notimp = True
			return '0'
		return 'Builder.Create%s(%s, %s)' % ({'+':'Add', '-':'Sub'}[atom[0]], emit(a, op_map), emit(b, op_map))
	elif atom[0] == 'neg':
		return 'Builder.CreateNeg(%s)' % emit(atom[1], op_map)
	elif atom[0] == 'reljmp':
		branches = True
		destoff = 'Builder.CreateSExtOrBitCast(%s, Type::getInt32Ty(Builder.getContext()))' % emit(atom[1], op_map)
		print >>insns, '\tBuilder.CreateStore(Builder.CreateAdd(ConstantInt::get(Type::getInt32Ty(Builder.getContext()), curEip+opcodeSize+modRMSize+immediateSize), %s), Builder.CreateStructGEP(stateArg, 0));' % destoff
	else:
		print 'unk', atom
		assert False

def insn_func(name, ops):
	return '%s%s' % (name, ('_'+'_'.join(ops)) if ops else '')

needs_modrm = 'Gv,Ev,Gb,Eb'.split(',')

global branches

notimp = True
def emit_instruction(name, ops, args, body):
	global branches, insns, notimp
	branches = False
	print >>decl, 'void', insn_func(name, ops) + '();'
	print >>insns, 'void InstructionDispatcher::' + insn_func(name, ops) + '() {'
	print >>insns, '\tprintf("0x%%08x %r\\n", curEip);' % ((name, ops, args, body), )

	if True in [op in needs_modrm for op in ops]:
		print >>insns, '\tCalcModRM();'
	for op in ops:
		if op == 'Ib' or op == 'Jb':
			print >>insns, '\timmediateSize += 1;'
		elif op == 'Iv' or op == 'Iz' or op == 'Jz' or op == 'Ov':
			print >>insns, '\timmediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;'
		elif op == 'Iw':
			print >>insns, '\timmediateSize += 4;'

	op_map = dict((arg, ops[i]) for i, arg in enumerate(args))

	notimp = False
	oldout = insns
	insns = StringIO()
	for elem in body:
		emit(elem, op_map)
	buffer = insns.getvalue()
	insns = oldout
	if notimp:
		print >>insns, '\tabort("Not implemented\\n");'
	else:
		insns.write(buffer)

	if branches:
		print >>insns, '\tbranched = true;'
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
	print >>fp, '\t'*depth+'\tabort("Unknown opcode %%02x\\n", %s);' % switch
	print >>fp, '\t'*depth+'\treturn -1;'
	print >>fp, '\t'*depth+'}'

with file('dispatcher_gen.cpp', 'w') as fp:
	emit_group(fp, 'opcode_1', opcode_groups[None], 0)
