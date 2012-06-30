#ifndef _ht_types_string_h_
#define _ht_types_string_h_

#include "types.h"

namespace ht
{
	
class StringV
{
public:
	constexpr static impltype_t IMPLTYPE = impltype_t::T_StringV;
	
	StringV()
	{}

	StringV(const std::string& o)
	: m_impl(o)	
	{}

	int to_int();
	
	int cstr(char* buf, size_t len)
	{
		char* pe = ::strncpy(buf, m_impl.data(), len);	
		return pe - buf;
	}
	
	std::string to_str()
	{
		return std::string(m_impl);	
	}
	
private:
	std::string m_impl;
};
	
} // end of namespace ht

#endif // _ht_types_string_h_
