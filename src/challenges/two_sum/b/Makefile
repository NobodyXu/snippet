CXXFLAGS = -Ofast -pipe -flto
LDFLAGS = -flto -pipe -Wl,--icf=all,-O2,--as-needed,--strip-all,--plugin-opt=O3
LIBS = -lpthread

CXXFLAGS_G = -O1 -pipe -g -fsanitize=address
LDFLAGS_G = -pipe

# Rules
%.out: %.cc findtwoSum.hpp
	$(CXX) -std=c++17 $(CXXFLAGS) $(LDFLAGS) $(LIBS) $< -o $@
	$(runtime_op) ./$@

all: debug.out performance_test.cc

debug.out: CXXFLAGS := $(CXXFLAGS_G)
debug.out: LDFLAGS := $(LDFLAGS_G)
debug.out: runtime_op := ASAN_OPTIONS=detect_leaks=1

.PHONY: clean
clean:
	rm -rf *.out
