#ifndef _ht_types_string_h_
#define _ht_types_string_h_

#include "types.h"
#include <string.h>

namespace ht
{
	
class StringV
{
public:
	constexpr static impltype_t IMPLTYPE = impltype_t::T_StringV;
	
	StringV()
	{ /* NOP */ }

	StringV(const std::string& o)
	: m_impl(o)	
	{ /* NOP */ }

	int to_int() const;
	
	int cstr(char* buf, size_t len) const
	{
		char* pe = ::strncpy(buf, m_impl.data(), len);	
		return pe - buf;
	}
	
	std::string to_str() const
	{
		return std::string(m_impl);	
	}
	
	std::string inspect() const
	{
		// FIXME: escape control chars
		return std::string("#<StringV: \"")+m_impl+"\">";
	}
	
private:
	std::string m_impl;
};
	
} // end of namespace ht

#endif // _ht_types_string_h_
