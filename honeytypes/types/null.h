#ifndef _ht_types_null_h_
#define _ht_types_null_h_

#include "types.h"

namespace ht
{
	
class NullV
{
public:
	constexpr static impltype_t IMPLTYPE = impltype_t::T_NullV;
	
	NullV()
	{ /* NOP */ }
	
	int to_int()
	{
		return 0;	
	}
	
	int cstr(char*, size_t)
	{
		return 0;
	}
	
	std::string to_str()
	{
		return std::string();	
	}
};

} // end of namespace ht

#endif // _ht_types_null_h_
