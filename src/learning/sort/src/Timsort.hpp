//c++14
//use "#define __DEBUG_ON__" to enable debug mode.
#ifndef __sort_Timsort_HPP__
#define __Timsort_HPP__

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#include <cassert>	    //to use assert micro
#include <utility>	    //std::move()
#include "rest.hpp"
#include "binarysort.hpp"
namespace NB {
//This is a steady sort algorithm combined with binary sort, and merge sort.
//The data need to be at least copiable.The iterators feeded in should be assignable.
template <typename it, typename Lesser = std::less<> >//it should not be a reference
struct Timsort {
using T = It_val<it>;
using diff_t = It_diff_t<it>;
    Timsort(const it first, const it last, diff_t n, Lesser Less = {}):
	    end(last), L(Less), N(n) {
        base = first;
        assert(It_dis(first, last) > 1);
        assert(n > 1);
	    switch((int) n > minimal_run ? 2 : 1) {
		    case 2:
	          tmp = new T[n >> 2];
    		    runBase = new it[StackLen];
	    	    runLen = new diff_t[StackLen];
	 	        do_Timsort();
		        break;
    		case 1:
	     	    binarysort(first, first + 1, last);
	    }
	}
	~Timsort() noexcept {
	    delete [] tmp;
	    delete [] runBase;
	    delete [] runLen;
	}
	const static diff_t minimal_run = 64;
	const static diff_t MIN_GALLOP = 7;
	const static unsigned char StackLen = 50;
private:
	unsigned char StackSize = 0;
	it *runBase;
	diff_t *runLen;
	diff_t min_gallop = MIN_GALLOP;
	const diff_t N;
public:
	Lesser L;
	const it end;
private:
	T *tmp;
	it base;
	diff_t index = 0;
	void do_Timsort() {
	    do {
		make_run();
		collapse_merge();
	    } while(base != end);
	    assert(StackSize <= StackLen);
	    if(StackSize > 1) force_collapse_merge();
	    assert(std::is_sorted(beg, end, L));
	}
	//probably buggy
	void make_run() {//Θ(n)
	    auto i = base + 1;
	    diff_t cnt = 2, buf;
	    if(unlikely(i == end)) {
    		base = i;
	    	return;
	    } else if(L(i, base)) {
		    for(++i; i != end && L(*i, *(i - 1)); ++i, ++cnt);
		    std::reverse(base, i);
	    } else
            for(++i; i != end && !L(*i, *(i - 1)); ++i, ++cnt);
	    if(buf = (cnt >= minimal_run ? 0 :
				       i == end ? 0 :
		((N - index - cnt) < minimal_run) ? (N - index - cnt) : minimal_run))
		binarysort(base, i, (i = base + buf));
	    runBase[StackSize] = base;
	    runLen[StackSize] = buf ? buf : cnt;
	    StackSize++;
	    assert(StackSize < StackLen);
	    index += buf ? buf : cnt;
	    base = i;
	}
	void collapse_merge() {
	    for(diff_t i = StackSize - 2; i >= 0; --i)
		//The contion when runLen[i - 1] == runLen[i + 1] can be seperated from it
		//and become a special optimization if needed.
		switch((int) 	i > 0 && runLen[i - 1] <= runLen[i + 1] ? 1 :
		  i > 1 && runLen[i - 2] <= (runLen[i - 1] + runLen[i]) ? 1 :
		  i > 0 && runLen[i - 1] <= (runLen[i] + runLen[i + 1]) ? 0 :
					     runLen[i] <= runLen[i + 1] ? 0 : -1) {
		    case -1:
	 		assert(check_run_conditions());
			return;
		    case 1:
			mergeLeft(i);
			break;
		    case 0:
			mergeRight(i);
		}
	}
	void force_collapse_merge() {
	    for(diff_t i = StackSize - 2; i >= 0; --i)
		//The condition when runLen[i - 1] == runLen[i + 1] can be seperated from it
		//and become a special optimization if needed.
		if(i != 0 && runLen[i - 1] >= runLen[i + 1]) mergeRight(i);
		else					     mergeLeft(i);
	}
	void mergeRight(diff_t i) {
	    merge(runBase[i], runBase[i + 1], runBase[i + 1] + runLen[i + 1]);
	    runLen[i] += runLen[i + 1];
	    --StackSize;
	}
	void mergeLeft(diff_t i) {
    	    merge(runBase[i - 1], runBase[i], runBase[i] + runLen[i]);
	    runLen[i - 1] += runLen[i];
	    runBase[i] = runBase[i + 1];
	    runLen[i] = runLen[i + 1];
	    --StackSize;
	}
	void merge(it left, it mid, it right) {
	    min_gallop = Merge{, min_gallop}(minimal_run);
	}
	void binarysort(it left, it i, it end) {
	    assert(It_dis_is_enough(left, i, 1));
	    assert(It_dis_is_enough(i, end, 1));
	    algorithms::binarysort(left, i, end, L);
	}
	int check_run_conditions() noexcept {
	    if(StackSize > 1 && runLen[StackSize - 2] <= runLen[StackSize - 1]) return 0;
	    for(diff_t i = StackSize - 3; i >= 0; --i)
		if(runLen[i] <= runLen[i + 1] + runLen[i + 2]) return 0;
	    return 1;
	}
    };//The end of the define of class Timsort
}
#endif
