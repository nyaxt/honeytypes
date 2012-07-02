// #define HT_FALLBACK_STRINGID
#include "honeytypes/stringid.h"

#include <iostream>
#include <sstream>
#include <vector>
#include "time.h"

using namespace ht;

std::vector<StringId> v;

void bench_init()
{
	for(int i = 0; i < 1000000; ++ i)
	{
		std::ostringstream s;
		s << "column" << i;
		
		v.push_back(StringId(s.str()));
	}
}

void bench_main()
{
	size_t count = 0;

	StringId pick("column300");
	for(auto& x: v)
	{
		if(pick == x) ++ count;
	}
	
	__asm("" ::"r"(count)); // make sure _count_ is counted
	// std::cout << count << std::endl;
}

int
main()
{
	bench_init();	

	std::cout << "bench start" << std::endl;
	struct timespec ts, te;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	{
		bench_main();
	}	
	clock_gettime(CLOCK_MONOTONIC, &te);
	std::cout << "bench end" << std::endl;
	
	double diff = (te.tv_sec - ts.tv_sec) * 1000;
	diff += (double)(te.tv_nsec - ts.tv_nsec) / 1000000.0;
	std::cout << "time took: " << diff << "ms" << std::endl;
}

