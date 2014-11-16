all:
	python cpugen.py
	clang++ `llvm-config --cxxflags --ldflags --libs core` -lncurses -o test test.cpp InstructionDispatcher.cpp instructions_gen.cpp
	./test