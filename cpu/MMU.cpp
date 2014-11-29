#include "MMU.hpp"
#include <stdio.h>
#include <cstdlib>
#include <cassert>
#include <sys/mman.h>

MMU::MMU() {
	void *temp = mmap(nullptr, 1L << 32, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
	base = (uint64_t) temp;
	printf("MMU base addr 0x%016llx\n", base);
}

void *MMU::GetPtr(uint32_t ptr) {
	return (void *) (base + ptr);
}

uint32_t MMU::PtrToOffset(void *ptr) {
	uint64_t temp = (uint64_t) ptr;
	assert(temp >= base && (temp - base) < (1L << 32));
	return (uint32_t) (temp - base);
}

bool MMU::AllocAt(uint32_t ptr, uint32_t size) {
	return true;
}

uint32_t MMU::Alloc(uint32_t size) {
	assert(false);
	return 0;
}

void MMU::Free(uint32_t ptr) {
	assert(false);
}
