#include <iostream>
#include "Cpu.hpp"

Cpu::Cpu(MMU *_mmu) {
	mmu = _mmu;
	InitializeNativeTarget();
	memset(&state, 0, sizeof(CpuState));

	module = new class Module("Rayless", getGlobalContext());
	std::vector<Type *> stypes(2, Type::getInt32Ty(module->getContext()));
	CpuStateType = StructType::create(module->getContext(), stypes, "CpuState");
	std::string err = "";
	ee = EngineBuilder(module)
		.setErrorStr(&err)
		.setEngineKind(EngineKind::JIT)
		.create();
	if(ee == nullptr)
		std::cout << "Error " << err << std::endl;
	fpm = new FunctionPassManager(module);
	fpm->add(new DataLayoutPass(*ee->getDataLayout()));
	fpm->add(createBasicAliasAnalysisPass());
	fpm->add(createInstructionCombiningPass());
	fpm->add(createReassociatePass());
	fpm->add(createGVNPass());
	fpm->add(createCFGSimplificationPass());
	fpm->doInitialization();
}

void Cpu::Run() {
	while(true)
		RunOneBlock();
}

void Cpu::RunOneBlock() {
	BlockFunction fp;
	if(blockFunctions.count(state.eip) == 0) {
		unsigned char name[15];
		std::vector<Type *> args(1, CpuStateType->getPointerTo());
		FunctionType *ft = FunctionType::get(Type::getVoidTy(module->getContext()), args, false);
		sprintf((char *) name, "block_%08x", state.eip);
		Function *f = Function::Create(ft, Function::ExternalLinkage, (char *) name, module);
		module->dump();

		InstructionDispatcher dispatcher(this, f);
		printf("Dispatching...\n");
		uint32_t addr = state.eip;
		while(1) {
			uint32_t len = dispatcher.Dispatch(addr);
			if(len == -1)
				break;
			printf("Total instruction length %i\n", len);
			addr += len;
		}
		printf("Done\n");

		Builder.CreateRetVoid();

		module->dump();
		fpm->run(*f);
		module->dump();
		void *fptr = ee->getPointerToFunction(f);
		blockFunctions[state.eip] = fp = (BlockFunction) fptr;
	} else
		fp = blockFunctions[state.eip];
	printf("Before...\n");
	DumpState();
	fp(&state);
	printf("After...\n");
	DumpState();
	fflush(stdout);
}

void Cpu::DumpState() {
	printf("====CPU State====\n");
	printf("EIP: %08x\n", state.eip);
	printf("EAX: %08x\n", state.eax);
	printf("=================\n");
}
