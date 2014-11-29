#pragma once

#include "llvm/Analysis/Passes.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/PassManager.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/ExecutionEngine/JIT.h"
#include <iostream>

using namespace llvm;

extern IRBuilder<> Builder;

#include "Cpu.hpp"

enum InstructionFlags {
	None   = 0x0000,
	Opsize = 0x0001,
	Adsize = 0x0002, 
	Rep    = 0x0004,
	Repne  = 0x0008, 
	Lock   = 0x0010, 
	CS     = 0x0020, BranchTaken    = 0x0020, 
	SS     = 0x0040, 
	DS     = 0x0080, BranchNotTaken = 0x0080, 
	ES     = 0x0100, 
	FS     = 0x0200, 
	GS     = 0x0400
};
inline InstructionFlags operator|(InstructionFlags a, InstructionFlags b) {
	return static_cast<InstructionFlags>(static_cast<int>(a) | static_cast<int>(b));
}
inline InstructionFlags& operator|=(InstructionFlags &a, InstructionFlags b) {
	return a = static_cast<InstructionFlags>(static_cast<int>(a) | static_cast<int>(b));
}

typedef class InstructionDispatcher {
public:
	InstructionDispatcher(class Cpu *cpu, class Function *function);
	int Dispatch(unsigned int addr);

	void CalcModRM();
	ConstantInt *GetImmediateOp32();
	ConstantInt *GetImmediateOp8();
	int OperandSize();
	Value *GetReg(int size);
	Value *GetRM(int size);
	Value *CreatePointer(Value *addr, int size);

	Cpu *cpu;
	InstructionFlags flags;
	unsigned char *bytes;
	unsigned int opcodeSize, modRMSize, immediateSize, curEip;
	bool branched;
	Function *function;
	Value *stateArg;

#include "instruction_decl.hpp"
} InstructionDispatcher_t;