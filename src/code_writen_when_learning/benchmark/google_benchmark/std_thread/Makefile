CXXFLAGS := -Ofast -pipe -flto
LDFLAGS := -pipe -flto -Wl,--icf=all,-O2,--as-needed,--strip-all,--plugin-opt=O3

all: a.out
a.out: a.cc Makefile
	${CXX} -std=c++17 -L /usr/local/lib -lbenchmark -lpthread -Ofast a.cc

.PHONY: clear
clear:
	rm -f a.out
