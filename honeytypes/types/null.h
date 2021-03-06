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

	bool operator==(const BoolV& o) const
	{
		return true;
	}

	bool operator!=(const BoolV& o) const
	{
		return false;
	}
	
	int to_int() const
	{
		return 0;	
	}
	
	bool to_bool() const
	{
		return false;	
	}

	double to_double() const
	{
		return 0.0;	
	}
	
	int cstr(char*, size_t) const
	{
		return 0;
	}
	
	std::string to_str() const
	{
		return std::string();	
	}
	
	std::string inspect() const
	{
		return std::string("#<NullV>");	
	}
	
	size_t hash() const
	{
		return ~static_cast<size_t>(0);
	}
};

} // end of namespace ht

#endif // _ht_types_null_h_
