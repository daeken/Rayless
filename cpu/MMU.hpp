#pragma once

#include <stdint.h>
#include <malloc/malloc.h>

class MMU {
public:
	MMU();
	void *GetPtr(uint32_t ptr);
	uint32_t PtrToOffset(void *ptr);
	bool AllocAt(uint32_t ptr, uint32_t size);
	uint32_t Alloc(uint32_t size);
	void Free(uint32_t ptr);

	uint64_t base;
};
