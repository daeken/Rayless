lines = file('opcodes.txt').read()

opcodes = {}
for line in lines.split('\n'):
	opcd, rest = line.split(' ', 1)
	if ' ' in rest:
		insn, args = rest.split(' ', 1)
	else:
		insn, args = rest, None
	if insn[0] == '-':
		continue

	opcodes[int(opcd, 16)] = insn.lower(), [] if args is None else args.split(',')
__all__='opcodes',