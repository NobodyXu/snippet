all: a.out g.out
a.out: main.cc
	clang++ -std=c++17 -lbenchmark -lpthread -Ofast main.cc
g.out: main.cc
	clang++ -std=c++17 -lbenchmark -lpthread -O0 -g main.cc -o g.out
clear: *.out
	rm *.out
