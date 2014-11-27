#include "MMU.hpp"
#include <stdio.h>
#include <cstdlib>
#include <cassert>
#include <sys/mman.h>

MMU::MMU() {
	void *temp = malloc(4096);
	Base = (uint64_t) temp;
	free(temp);
}

void *MMU::GetPtr(uint32_t ptr) {
	return (void *) (Base + ptr);
}

uint32_t MMU::PtrToOffset(void *ptr) {
	uint64_t temp = (uint64_t) ptr;
	assert(temp >= Base && (temp - Base) < (1L << 32));
	return (uint32_t) (temp - Base);
}

bool MMU::AllocAt(uint32_t ptr, uint32_t size) {
	return mmap(
		GetPtr(ptr), 
		size, 
		PROT_READ|PROT_WRITE, 
		MAP_SHARED|MAP_ANON, 
		-1, 
		0
	) != MAP_FAILED;
}

uint32_t MMU::Alloc(uint32_t size) {
	return PtrToOffset(malloc(size));
}

void MMU::Free(uint32_t ptr) {
	free(GetPtr(ptr));
}
