#include "llvm/DerivedTypes.h"
#include "llvm/IRBuilder.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"

using namespace llvm;

static IRBuilder<> Builder(getGlobalContext());

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

class InstructionDispatcher {
public:
	InstructionDispatcher();
	void Dispatch(void *addr);

	InstructionFlags Flags;

#include "instruction_decl.hpp"
};