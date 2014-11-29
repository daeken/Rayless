#include "InstructionDispatcher.hpp"

IRBuilder<> Builder(getGlobalContext());

InstructionDispatcher::InstructionDispatcher(class Cpu *_cpu, class Function *_function) {
	cpu = _cpu;
	function = _function;

	BasicBlock *BB = BasicBlock::Create(function->getContext(), "entry", function);
	Builder.SetInsertPoint(BB);
	stateArg = (Value *) function->arg_begin();
}

#define FLAG_MATCH(prefix, flag) case prefix: flags |= InstructionFlags::flag; break
int InstructionDispatcher::Dispatch(unsigned int addr) {
	curEip = addr;
	bytes = (unsigned char *) cpu->mmu->GetPtr(addr);
	bool found_prefix = true;
	opcodeSize = modRMSize = immediateSize = 0;
	flags = InstructionFlags::None;
	branched = false;
	while(found_prefix) {
		switch(bytes[opcodeSize++]) {
			FLAG_MATCH(0xF0, Lock);
			FLAG_MATCH(0xF2, Repne);
			FLAG_MATCH(0xF3, Rep);
			FLAG_MATCH(0x2E, CS);
			FLAG_MATCH(0x36, SS);
			FLAG_MATCH(0x3E, DS);
			FLAG_MATCH(0x26, ES);
			FLAG_MATCH(0x64, FS);
			FLAG_MATCH(0x65, GS);
			FLAG_MATCH(0x66, Opsize);
			FLAG_MATCH(0x67, Adsize);
			default:
				opcodeSize--;
				found_prefix = false;
				break;
		}
	}
	unsigned char opcode_1 = bytes[opcodeSize++];
#include "dispatcher_gen.cpp"

	if(branched)
		return -1;
	else
		return opcodeSize + modRMSize + immediateSize;
}

void InstructionDispatcher::CalcModRM() {
	unsigned char modrm = bytes[opcodeSize];
	modRMSize++;
	int mod = modrm >> 6, rm = modrm & 7, reg = (modrm >> 3) & 7;
	if(mod == 0 && rm == 5)
		modRMSize += 4;
	else if(mod == 1)
		modRMSize += 1;
	else if(mod == 2)
		modRMSize += 4;

	if(mod != 3 && rm == 4) {
		unsigned char sib = bytes[opcodeSize + 1];
		int base = sib & 7;
		if(base == 5)
			switch(mod) {
				case 0: modRMSize += 4; break;
				// Should the 1/2 cases stack with the size from the modrm?
				// Sounds like they should.
				case 1: modRMSize += 1; break;
				case 2: modRMSize += 4; break;
			}
	}
}

ConstantInt *InstructionDispatcher::GetImmediateOp32() {
	if((flags & InstructionFlags::Opsize) == 0)
		return ConstantInt::get(Type::getInt32Ty(Builder.getContext()), *((unsigned int *) &bytes[opcodeSize + modRMSize]));
	else
		return ConstantInt::get(Type::getInt16Ty(Builder.getContext()), *((unsigned short int *) &bytes[opcodeSize + modRMSize]));
}

ConstantInt *InstructionDispatcher::GetImmediateOp8() {
	return ConstantInt::get(Type::getInt8Ty(Builder.getContext()), *((unsigned char *) &bytes[opcodeSize + modRMSize]));
}

int InstructionDispatcher::OperandSize() {
	if((flags & InstructionFlags::Opsize) == 0)
		return 32;
	else
		return 16;
}

Value *InstructionDispatcher::GetReg(int size) {
	unsigned char modrm = bytes[opcodeSize];
	int reg = (modrm >> 3) & 7;
	printf("GetReg %i\n", reg);
	switch(size) {
		case 32:
			switch(reg) {
				case 0: return Builder.CreateStructGEP(stateArg, 1);
				case 1: return Builder.CreateStructGEP(stateArg, 2);
				case 2: return Builder.CreateStructGEP(stateArg, 3);
				case 3: return Builder.CreateStructGEP(stateArg, 4);
				case 4: return Builder.CreateStructGEP(stateArg, 5);
				case 5: return Builder.CreateStructGEP(stateArg, 6);
				case 6: return Builder.CreateStructGEP(stateArg, 7);
				case 7: return Builder.CreateStructGEP(stateArg, 8);
			}
		default:
			abort("Unknown size to GetReg: %i\n", size);
	}
	return nullptr;
}

Value *InstructionDispatcher::GetRM(int size) {
	unsigned char modrm = bytes[opcodeSize];
	int mod = modrm >> 6, rm = modrm & 7;
	printf("GetRM %i %i\n", mod, rm);
	Value *addr = nullptr;
	switch(size) {
		case 32:
			switch(mod) {
				case 0:
					switch(rm) {
						case 0:
							addr = Builder.CreateStructGEP(stateArg, 1);
							break;
						case 1:
							addr = Builder.CreateStructGEP(stateArg, 2);
							break;
						case 2:
							addr = Builder.CreateStructGEP(stateArg, 3);
							break;
						case 3:
							addr = Builder.CreateStructGEP(stateArg, 4);
							break;
						case 5:
							addr = ConstantInt::get(Type::getInt32Ty(Builder.getContext()), *((unsigned int *) &bytes[opcodeSize + 1]));
							break;
						default:
							abort("Unknown rm to GetRM(mod=0): %i\n", rm);
					}
					break;
				case 3:
					switch(rm) {
						case 1:
							return Builder.CreateStructGEP(stateArg, 2);
						default:
							abort("Unknown rm to GetRM(mod=3): %i\n", rm);
					}
					break;
				default:
					abort("Unknown mod to GetRM: %i\n", mod);
			}
			break;
		default:
			abort("Unknown size to GetRM: %i\n", size);
	}
	return CreatePointer(addr, 32);
}

Value *InstructionDispatcher::CreatePointer(Value *addr, int size) {
	Type *stype = Type::getInt32Ty(Builder.getContext())->getPointerTo();
	Value *base = ConstantInt::get(Type::getInt64Ty(Builder.getContext()), cpu->mmu->base);
	Value *upaddr = Builder.CreateIntCast(addr, Type::getInt64Ty(Builder.getContext()), false);
	return Builder.CreateIntToPtr(Builder.CreateAdd(base, upaddr), stype);
}

#include "instructions_gen.cpp"
