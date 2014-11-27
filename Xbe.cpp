#include <cassert>
#include "Xbe.hpp"

Xbe::Xbe(char *fn) {
	fp = fopen(fn, "rb");
	fread(&header, sizeof(XbeHeader), 1, fp);
	fseek(fp, 0, SEEK_SET);
	assert(header.soh == 0x1000);
	full_header = new uint8_t[header.soh];
	fread(full_header, header.soh, 1, fp);

	sections = new XbeSection[header.numsects];
	for(int i = 0; i < header.numsects; ++i) {
		fseek(fp, (header.secthdrs - header.base) + sizeof(XbeSection) * i, SEEK_SET);
		fread(&sections[i], sizeof(XbeSection), 1, fp);
		printf("%s %x\n", &full_header[sections[i].nameaddr - header.base], sections[i].vaddr);
	}
}

void Xbe::LoadSection(int num, void *addr) {
	fseek(fp, sections[num].raddr, SEEK_SET);
	fread(addr, sections[num].rsize, 1, fp);
}
