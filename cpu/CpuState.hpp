#pragma once

#define REG32(letter) \
union { \
	uint32_t e##letter##x; \
	struct { \
		uint16_t letter##x; \
		uint16_t letter##_pad1; \
	}; \
	struct { \
		uint8_t letter##l; \
		uint8_t letter##h; \
		uint16_t letter##_pad2; \
	}; \
}

#define REG32_16(term) \
union { \
	uint32_t e##term; \
	struct { \
		uint16_t term; \
		uint16_t term##_pad1; \
	}; \
}

struct CpuState {
	uint32_t eip;
	REG32(a);
	REG32(c);
	REG32(d);
	REG32(b);
	REG32_16(sp);
	REG32_16(bp);
	REG32_16(si);
	REG32_16(di);
	REG32_16(flags);
};
