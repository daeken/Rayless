#include <stdio.h>
#include "InstructionDispatcher.hpp"

int main(void) {
	InstructionDispatcher dispatcher;
	unsigned char instructions[] = {0x05, 0xEF, 0xBE, 0xAD, 0xDE};
	printf("Dispatching...\n");
	dispatcher.Dispatch((void *) instructions);
	printf("Done\n");
}
