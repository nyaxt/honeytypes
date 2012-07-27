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
	bool to_bool() const;
	double to_double() const;
	
	int cstr(char* buf, size_t len) const
	{
		::strncpy(buf, m_impl.data(), len);
		return static_cast<int>(m_impl.size());
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

	std::string& get()
	{
		return m_impl;	
	}

	const std::string& get() const
	{
		return m_impl;	
	}
	
private:
	std::string m_impl;
};
	
} // end of namespace ht

#endif // _ht_types_string_h_

