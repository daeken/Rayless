#include "cpu/Cpu.hpp"
#include "Xbe.hpp"

class System {
public:
	Cpu *cpu;
	MMU *mmu;

	System() {
		mmu = new MMU();
		cpu = new Cpu(mmu);
	}

	void LoadXbe(char *fn) {
		Xbe xbe(fn);
		assert(mmu->AllocAt(xbe.header.base, xbe.header.soh));
		memcpy(mmu->GetPtr(xbe.header.base), xbe.full_header, xbe.header.soh);

		for(int i = 0; i < xbe.header.numsects; ++i) {
			XbeSection *sect = &xbe.sections[i];
			assert(mmu->AllocAt(sect->vaddr, sect->vsize));
			xbe.LoadSection(i, mmu->GetPtr(sect->vaddr));
		}
	}
};

int main(int argc, char **argv) {
	if(argc != 2) {
		printf("Need xbe argument\n");
		return 1;
	}
	System sys;
	sys.LoadXbe(argv[1]);
	return 0;
}
