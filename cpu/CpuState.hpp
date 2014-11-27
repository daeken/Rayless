#pragma once

struct CpuState {
	uint32_t eip;
	union {
		uint32_t eax;
		struct {
			uint16_t ax;
			uint16_t _pad1;
		};
		struct {
			uint8_t al;
			uint8_t ah;
			uint16_t _pad2;
		};
	};
};
