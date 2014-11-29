#include "InstructionDispatcher.hpp"
void InstructionDispatcher::add_Eb_Gb() {
	printf("0x%08x ('add', ['Eb', 'Gb'], ['dest', 'b'], [['set', 'dest', ['+', 'dest', 'b']]])\n", curEip);
	CalcModRM();
	abort("Not implemented\n");
}
void InstructionDispatcher::add_Ev_Gv() {
	printf("0x%08x ('add', ['Ev', 'Gv'], ['dest', 'b'], [['set', 'dest', ['+', 'dest', 'b']]])\n", curEip);
	CalcModRM();
	Builder.CreateStore(Builder.CreateAdd(Builder.CreateLoad(GetRM(OperandSize())), Builder.CreateLoad(GetReg(OperandSize()))), GetRM(OperandSize()));
}
void InstructionDispatcher::add_Gb_Eb() {
	printf("0x%08x ('add', ['Gb', 'Eb'], ['dest', 'b'], [['set', 'dest', ['+', 'dest', 'b']]])\n", curEip);
	CalcModRM();
	abort("Not implemented\n");
}
void InstructionDispatcher::add_Gv_Ev() {
	printf("0x%08x ('add', ['Gv', 'Ev'], ['dest', 'b'], [['set', 'dest', ['+', 'dest', 'b']]])\n", curEip);
	CalcModRM();
	Builder.CreateStore(Builder.CreateAdd(Builder.CreateLoad(GetReg(OperandSize())), Builder.CreateLoad(GetRM(OperandSize()))), GetReg(OperandSize()));
}
void InstructionDispatcher::add_AL_Ib() {
	printf("0x%08x ('add', ['AL', 'Ib'], ['dest', 'b'], [['set', 'dest', ['+', 'dest', 'b']]])\n", curEip);
	immediateSize += 1;
	abort("Not implemented\n");
}
void InstructionDispatcher::add_rAX_Iz() {
	printf("0x%08x ('add', ['rAX', 'Iz'], ['dest', 'b'], [['set', 'dest', ['+', 'dest', 'b']]])\n", curEip);
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	Builder.CreateStore(Builder.CreateAdd(Builder.CreateLoad(Builder.CreateStructGEP(stateArg, 1)), GetImmediateOp32()), Builder.CreateStructGEP(stateArg, 1));
}
void InstructionDispatcher::sub_Eb_Gb() {
	printf("0x%08x ('sub', ['Eb', 'Gb'], ['dest', 'b'], [['set', 'dest', ['-', 'dest', 'b']]])\n", curEip);
	CalcModRM();
	abort("Not implemented\n");
}
void InstructionDispatcher::sub_Ev_Gv() {
	printf("0x%08x ('sub', ['Ev', 'Gv'], ['dest', 'b'], [['set', 'dest', ['-', 'dest', 'b']]])\n", curEip);
	CalcModRM();
	Builder.CreateStore(Builder.CreateSub(Builder.CreateLoad(GetRM(OperandSize())), Builder.CreateLoad(GetReg(OperandSize()))), GetRM(OperandSize()));
}
void InstructionDispatcher::sub_Gb_Eb() {
	printf("0x%08x ('sub', ['Gb', 'Eb'], ['dest', 'b'], [['set', 'dest', ['-', 'dest', 'b']]])\n", curEip);
	CalcModRM();
	abort("Not implemented\n");
}
void InstructionDispatcher::sub_Gv_Ev() {
	printf("0x%08x ('sub', ['Gv', 'Ev'], ['dest', 'b'], [['set', 'dest', ['-', 'dest', 'b']]])\n", curEip);
	CalcModRM();
	Builder.CreateStore(Builder.CreateSub(Builder.CreateLoad(GetReg(OperandSize())), Builder.CreateLoad(GetRM(OperandSize()))), GetReg(OperandSize()));
}
void InstructionDispatcher::sub_AL_Ib() {
	printf("0x%08x ('sub', ['AL', 'Ib'], ['dest', 'b'], [['set', 'dest', ['-', 'dest', 'b']]])\n", curEip);
	immediateSize += 1;
	abort("Not implemented\n");
}
void InstructionDispatcher::sub_rAX_Iz() {
	printf("0x%08x ('sub', ['rAX', 'Iz'], ['dest', 'b'], [['set', 'dest', ['-', 'dest', 'b']]])\n", curEip);
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	Builder.CreateStore(Builder.CreateSub(Builder.CreateLoad(Builder.CreateStructGEP(stateArg, 1)), GetImmediateOp32()), Builder.CreateStructGEP(stateArg, 1));
}
void InstructionDispatcher::mov_Eb_Gb() {
	printf("0x%08x ('mov', ['Eb', 'Gb'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	CalcModRM();
	abort("Not implemented\n");
}
void InstructionDispatcher::mov_Ev_Gv() {
	printf("0x%08x ('mov', ['Ev', 'Gv'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	CalcModRM();
	Builder.CreateStore(Builder.CreateLoad(GetReg(OperandSize())), GetRM(OperandSize()));
}
void InstructionDispatcher::mov_Gb_Eb() {
	printf("0x%08x ('mov', ['Gb', 'Eb'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	CalcModRM();
	abort("Not implemented\n");
}
void InstructionDispatcher::mov_Gv_Ev() {
	printf("0x%08x ('mov', ['Gv', 'Ev'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	CalcModRM();
	Builder.CreateStore(Builder.CreateLoad(GetRM(OperandSize())), GetReg(OperandSize()));
}
void InstructionDispatcher::mov_AL_Ov() {
	printf("0x%08x ('mov', ['AL', 'Ov'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	abort("Not implemented\n");
}
void InstructionDispatcher::mov_rAX_Ov() {
	printf("0x%08x ('mov', ['rAX', 'Ov'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	Builder.CreateStore(Builder.CreateLoad(CreatePointer(GetImmediateOp32(), 32)), Builder.CreateStructGEP(stateArg, 1));
}
void InstructionDispatcher::mov_Ov_AL() {
	printf("0x%08x ('mov', ['Ov', 'AL'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	abort("Not implemented\n");
}
void InstructionDispatcher::mov_Ov_rAX() {
	printf("0x%08x ('mov', ['Ov', 'rAX'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	abort("Not implemented\n");
}
void InstructionDispatcher::mov_AL_Ib() {
	printf("0x%08x ('mov', ['AL', 'Ib'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	immediateSize += 1;
	abort("Not implemented\n");
}
void InstructionDispatcher::mov_CL_Ib() {
	printf("0x%08x ('mov', ['CL', 'Ib'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	immediateSize += 1;
	abort("Not implemented\n");
}
void InstructionDispatcher::mov_DL_Ib() {
	printf("0x%08x ('mov', ['DL', 'Ib'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	immediateSize += 1;
	abort("Not implemented\n");
}
void InstructionDispatcher::mov_BL_Ib() {
	printf("0x%08x ('mov', ['BL', 'Ib'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	immediateSize += 1;
	abort("Not implemented\n");
}
void InstructionDispatcher::mov_AH_Ib() {
	printf("0x%08x ('mov', ['AH', 'Ib'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	immediateSize += 1;
	abort("Not implemented\n");
}
void InstructionDispatcher::mov_CH_Ib() {
	printf("0x%08x ('mov', ['CH', 'Ib'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	immediateSize += 1;
	abort("Not implemented\n");
}
void InstructionDispatcher::mov_DH_Ib() {
	printf("0x%08x ('mov', ['DH', 'Ib'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	immediateSize += 1;
	abort("Not implemented\n");
}
void InstructionDispatcher::mov_BH_Ib() {
	printf("0x%08x ('mov', ['BH', 'Ib'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	immediateSize += 1;
	abort("Not implemented\n");
}
void InstructionDispatcher::mov_rAX_Iv() {
	printf("0x%08x ('mov', ['rAX', 'Iv'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	Builder.CreateStore(GetImmediateOp32(), Builder.CreateStructGEP(stateArg, 1));
}
void InstructionDispatcher::mov_rCX_Iv() {
	printf("0x%08x ('mov', ['rCX', 'Iv'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	abort("Not implemented\n");
}
void InstructionDispatcher::mov_rDX_Iv() {
	printf("0x%08x ('mov', ['rDX', 'Iv'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	abort("Not implemented\n");
}
void InstructionDispatcher::mov_rBX_Iv() {
	printf("0x%08x ('mov', ['rBX', 'Iv'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	abort("Not implemented\n");
}
void InstructionDispatcher::mov_rSP_Iv() {
	printf("0x%08x ('mov', ['rSP', 'Iv'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	abort("Not implemented\n");
}
void InstructionDispatcher::mov_rBP_Iv() {
	printf("0x%08x ('mov', ['rBP', 'Iv'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	abort("Not implemented\n");
}
void InstructionDispatcher::mov_rSI_Iv() {
	printf("0x%08x ('mov', ['rSI', 'Iv'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	abort("Not implemented\n");
}
void InstructionDispatcher::mov_rDI_Iv() {
	printf("0x%08x ('mov', ['rDI', 'Iv'], ['dest', 'src'], [['set', 'dest', 'src']])\n", curEip);
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	abort("Not implemented\n");
}
void InstructionDispatcher::jmp_Jz() {
	printf("0x%08x ('jmp', ['Jz'], ['dest'], [['reljmp', 'dest']])\n", curEip);
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	Builder.CreateStore(Builder.CreateAdd(ConstantInt::get(Type::getInt32Ty(Builder.getContext()), curEip+opcodeSize+modRMSize+immediateSize), Builder.CreateSExtOrBitCast(GetImmediateOp32(), Type::getInt32Ty(Builder.getContext()))), Builder.CreateStructGEP(stateArg, 0));
	branched = true;
}
void InstructionDispatcher::jmp_Ap() {
	printf("0x%08x ('jmp', ['Ap'], ['dest'], [['reljmp', 'dest']])\n", curEip);
	abort("Not implemented\n");
	branched = true;
}
void InstructionDispatcher::jmp_Jb() {
	printf("0x%08x ('jmp', ['Jb'], ['dest'], [['reljmp', 'dest']])\n", curEip);
	immediateSize += 1;
	Builder.CreateStore(Builder.CreateAdd(ConstantInt::get(Type::getInt32Ty(Builder.getContext()), curEip+opcodeSize+modRMSize+immediateSize), Builder.CreateSExtOrBitCast(GetImmediateOp8(), Type::getInt32Ty(Builder.getContext()))), Builder.CreateStructGEP(stateArg, 0));
	branched = true;
}
