#include "InstructionDispatcher.hpp"

InstructionDispatcher::InstructionDispatcher() {
}

#define FLAG_MATCH(prefix, flag) case prefix: Flags |= InstructionFlags::flag; break
void InstructionDispatcher::Dispatch(void *addr) {
	unsigned char *bytes = (unsigned char *) addr;
	bool found_prefix = true, branched = false;
	Flags = InstructionFlags::None;
	while(found_prefix) {
		switch(*(bytes++)) {
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
				bytes--;
				found_prefix = false;
				break;
		}
	}
	unsigned char opcode_1 = *bytes;
	printf("foo %02x\n", opcode_1);
#include "dispatcher_gen.cpp"
}
