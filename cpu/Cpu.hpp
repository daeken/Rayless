#pragma once

#include "InstructionDispatcher.hpp"
#include "CpuState.hpp"
#include "MMU.hpp"

#define abort(args...) do { printf(args); exit(1); } while(0)

typedef void (*BlockFunction)(CpuState *);

class Cpu {
public:
	CpuState state;
	MMU *mmu;
	class Module *module;
	StructType *CpuStateType;
	ExecutionEngine *ee;
	FunctionPassManager *fpm;
	std::map<unsigned int, BlockFunction> blockFunctions;
	Cpu(MMU *_mmu);
	void Run();
	void RunOneBlock();
	void DumpState();
};
