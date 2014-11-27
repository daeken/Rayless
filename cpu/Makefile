all: ../build/Cpu.so

../build/Cpu.so: Cpu.cpp MMU.cpp InstructionDispatcher.cpp cpugen.py opcodes.py opcodes.txt cpu.def
	python cpugen.py
	clang++ -g `/usr/local/bin/llvm-config --cxxflags --ldflags --libs all` -lz -lncurses -shared -o ../build/Cpu.so Cpu.cpp MMU.cpp InstructionDispatcher.cpp
