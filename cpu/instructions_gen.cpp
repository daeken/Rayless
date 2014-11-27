#include "InstructionDispatcher.hpp"
void InstructionDispatcher::add_Eb_Gb() {
	printf("('add', ['Eb', 'Gb'], ['dest', 'b'], [['set', 'dest', ['+', 'dest', 'b']]])\n");
	CalcModRM();
	Builder.CreateStore(0, 0);
}
void InstructionDispatcher::add_Ev_Gv() {
	printf("('add', ['Ev', 'Gv'], ['dest', 'b'], [['set', 'dest', ['+', 'dest', 'b']]])\n");
	CalcModRM();
	Builder.CreateStore(0, 0);
}
void InstructionDispatcher::add_Gb_Eb() {
	printf("('add', ['Gb', 'Eb'], ['dest', 'b'], [['set', 'dest', ['+', 'dest', 'b']]])\n");
	CalcModRM();
	Builder.CreateStore(0, 0);
}
void InstructionDispatcher::add_Gv_Ev() {
	printf("('add', ['Gv', 'Ev'], ['dest', 'b'], [['set', 'dest', ['+', 'dest', 'b']]])\n");
	CalcModRM();
	Builder.CreateStore(0, 0);
}
void InstructionDispatcher::add_AL_Ib() {
	printf("('add', ['AL', 'Ib'], ['dest', 'b'], [['set', 'dest', ['+', 'dest', 'b']]])\n");
	immediateSize += 1;
	Builder.CreateStore(0, 0);
}
void InstructionDispatcher::add_rAX_Iz() {
	printf("('add', ['rAX', 'Iz'], ['dest', 'b'], [['set', 'dest', ['+', 'dest', 'b']]])\n");
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	Builder.CreateStore(Builder.CreateAdd(Builder.CreateLoad(Builder.CreateStructGEP(stateArg, 1)), GetImmediateOp32()), Builder.CreateStructGEP(stateArg, 1));
}
void InstructionDispatcher::sub_Eb_Gb() {
	printf("('sub', ['Eb', 'Gb'], ['dest', 'b'], [['set', 'dest', ['-', 'dest', 'b']]])\n");
	CalcModRM();
	Builder.CreateStore(0, 0);
}
void InstructionDispatcher::sub_Ev_Gv() {
	printf("('sub', ['Ev', 'Gv'], ['dest', 'b'], [['set', 'dest', ['-', 'dest', 'b']]])\n");
	CalcModRM();
	Builder.CreateStore(0, 0);
}
void InstructionDispatcher::sub_Gb_Eb() {
	printf("('sub', ['Gb', 'Eb'], ['dest', 'b'], [['set', 'dest', ['-', 'dest', 'b']]])\n");
	CalcModRM();
	Builder.CreateStore(0, 0);
}
void InstructionDispatcher::sub_Gv_Ev() {
	printf("('sub', ['Gv', 'Ev'], ['dest', 'b'], [['set', 'dest', ['-', 'dest', 'b']]])\n");
	CalcModRM();
	Builder.CreateStore(0, 0);
}
void InstructionDispatcher::sub_AL_Ib() {
	printf("('sub', ['AL', 'Ib'], ['dest', 'b'], [['set', 'dest', ['-', 'dest', 'b']]])\n");
	immediateSize += 1;
	Builder.CreateStore(0, 0);
}
void InstructionDispatcher::sub_rAX_Iz() {
	printf("('sub', ['rAX', 'Iz'], ['dest', 'b'], [['set', 'dest', ['-', 'dest', 'b']]])\n");
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	Builder.CreateStore(Builder.CreateSub(Builder.CreateLoad(Builder.CreateStructGEP(stateArg, 1)), GetImmediateOp32()), Builder.CreateStructGEP(stateArg, 1));
}
void InstructionDispatcher::mov_Eb_Gb() {
	printf("('mov', ['Eb', 'Gb'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	CalcModRM();
	Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_Ev_Gv() {
	printf("('mov', ['Ev', 'Gv'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	CalcModRM();
	Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_Gb_Eb() {
	printf("('mov', ['Gb', 'Eb'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	CalcModRM();
	Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_Gv_Ev() {
	printf("('mov', ['Gv', 'Ev'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	CalcModRM();
	Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_AL_Ov() {
	printf("('mov', ['AL', 'Ov'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_rAX_Ov() {
	printf("('mov', ['rAX', 'Ov'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	Builder.CreateStore(0, Builder.CreateStructGEP(stateArg, 1));
}
void InstructionDispatcher::mov_Ov_AL() {
	printf("('mov', ['Ov', 'AL'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	Builder.CreateStore(0, 0);
}
void InstructionDispatcher::mov_Ov_rAX() {
	printf("('mov', ['Ov', 'rAX'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	Builder.CreateStore(Builder.CreateLoad(Builder.CreateStructGEP(stateArg, 1)), 0);
}
void InstructionDispatcher::mov_AL_Ib() {
	printf("('mov', ['AL', 'Ib'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	immediateSize += 1;
	Builder.CreateStore(GetImmediateOp8(), 0);
}
void InstructionDispatcher::mov_CL_Ib() {
	printf("('mov', ['CL', 'Ib'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	immediateSize += 1;
	Builder.CreateStore(GetImmediateOp8(), 0);
}
void InstructionDispatcher::mov_DL_Ib() {
	printf("('mov', ['DL', 'Ib'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	immediateSize += 1;
	Builder.CreateStore(GetImmediateOp8(), 0);
}
void InstructionDispatcher::mov_BL_Ib() {
	printf("('mov', ['BL', 'Ib'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	immediateSize += 1;
	Builder.CreateStore(GetImmediateOp8(), 0);
}
void InstructionDispatcher::mov_AH_Ib() {
	printf("('mov', ['AH', 'Ib'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	immediateSize += 1;
	Builder.CreateStore(GetImmediateOp8(), 0);
}
void InstructionDispatcher::mov_CH_Ib() {
	printf("('mov', ['CH', 'Ib'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	immediateSize += 1;
	Builder.CreateStore(GetImmediateOp8(), 0);
}
void InstructionDispatcher::mov_DH_Ib() {
	printf("('mov', ['DH', 'Ib'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	immediateSize += 1;
	Builder.CreateStore(GetImmediateOp8(), 0);
}
void InstructionDispatcher::mov_BH_Ib() {
	printf("('mov', ['BH', 'Ib'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	immediateSize += 1;
	Builder.CreateStore(GetImmediateOp8(), 0);
}
void InstructionDispatcher::mov_rAX_Iv() {
	printf("('mov', ['rAX', 'Iv'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	Builder.CreateStore(GetImmediateOp32(), Builder.CreateStructGEP(stateArg, 1));
}
void InstructionDispatcher::mov_rCX_Iv() {
	printf("('mov', ['rCX', 'Iv'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	Builder.CreateStore(GetImmediateOp32(), 0);
}
void InstructionDispatcher::mov_rDX_Iv() {
	printf("('mov', ['rDX', 'Iv'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	Builder.CreateStore(GetImmediateOp32(), 0);
}
void InstructionDispatcher::mov_rBX_Iv() {
	printf("('mov', ['rBX', 'Iv'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	Builder.CreateStore(GetImmediateOp32(), 0);
}
void InstructionDispatcher::mov_rSP_Iv() {
	printf("('mov', ['rSP', 'Iv'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	Builder.CreateStore(GetImmediateOp32(), 0);
}
void InstructionDispatcher::mov_rBP_Iv() {
	printf("('mov', ['rBP', 'Iv'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	Builder.CreateStore(GetImmediateOp32(), 0);
}
void InstructionDispatcher::mov_rSI_Iv() {
	printf("('mov', ['rSI', 'Iv'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	Builder.CreateStore(GetImmediateOp32(), 0);
}
void InstructionDispatcher::mov_rDI_Iv() {
	printf("('mov', ['rDI', 'Iv'], ['dest', 'src'], [['set', 'dest', 'src']])\n");
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	Builder.CreateStore(GetImmediateOp32(), 0);
}
void InstructionDispatcher::jmp_Jz() {
	printf("('jmp', ['Jz'], ['dest'], [['reljmp', 'dest']])\n");
	immediateSize += ((flags & InstructionFlags::Opsize) == 0) ? 4 : 2;
	Builder.CreateStore(Builder.CreateAdd(ConstantInt::get(Type::getInt32Ty(Builder.getContext()), curEip+opcodeSize+modRMSize+immediateSize), Builder.CreateSExtOrBitCast(0, Type::getInt32Ty(Builder.getContext()))), Builder.CreateStructGEP(stateArg, 0));
	branched = true;
}
void InstructionDispatcher::jmp_Ap() {
	printf("('jmp', ['Ap'], ['dest'], [['reljmp', 'dest']])\n");
	Builder.CreateStore(Builder.CreateAdd(ConstantInt::get(Type::getInt32Ty(Builder.getContext()), curEip+opcodeSize+modRMSize+immediateSize), Builder.CreateSExtOrBitCast(0, Type::getInt32Ty(Builder.getContext()))), Builder.CreateStructGEP(stateArg, 0));
	branched = true;
}
void InstructionDispatcher::jmp_Jb() {
	printf("('jmp', ['Jb'], ['dest'], [['reljmp', 'dest']])\n");
	immediateSize += 1;
	Builder.CreateStore(Builder.CreateAdd(ConstantInt::get(Type::getInt32Ty(Builder.getContext()), curEip+opcodeSize+modRMSize+immediateSize), Builder.CreateSExtOrBitCast(GetImmediateOp8(), Type::getInt32Ty(Builder.getContext()))), Builder.CreateStructGEP(stateArg, 0));
	branched = true;
}
