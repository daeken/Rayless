all: build rayless test

build: FORCE
	mkdir -p build

all: rayless test

build/Cpu.so: FORCE
	$(MAKE) -C cpu

FORCE:

rayless: build/Cpu.so main.cpp
	clang++ -o build/rayless -g `/usr/local/bin/llvm-config --cxxflags --ldflags` -lz -lncurses build/Cpu.so main.cpp Xbe.cpp

test: rayless
	cd build; ./rayless ../test1.xbe
