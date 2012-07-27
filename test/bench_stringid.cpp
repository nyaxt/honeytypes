// #define HT_FALLBACK_STRINGID
#include "honeytypes/stringid.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>

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
	typedef std::chrono::high_resolution_clock HighResClock;
	typedef std::chrono::time_point<HighResClock> HighResTimeStamp;

	bench_init();	

	std::cout << "bench start" << std::endl;
	HighResTimeStamp ts = HighResClock::now();
	{
		bench_main();
	}	
	HighResTimeStamp te = HighResClock::now();
	std::cout << "bench end" << std::endl;
	
	std::cout << "time took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(te - ts).count() << "ms" << std::endl;
}

