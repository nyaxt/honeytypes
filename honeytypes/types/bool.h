#ifndef _ht_types_bool_h_
#define _ht_types_bool_h_

#include "types.h"
#include <string.h>

namespace ht
{
	
class BoolV
{
public:
	constexpr static impltype_t IMPLTYPE = impltype_t::T_BoolV;
		
	BoolV(bool b = 0)
	:	m_impl(b)
	{ /* NOP */ }

	bool operator==(const BoolV& o) const
	{
		return m_impl == o.m_impl;
	}

	bool operator!=(const BoolV& o) const
	{
		return m_impl != o.m_impl;	
	}
	
	int to_int() const
	{
		return m_impl ? 1 : 0;
	}

	bool to_bool() const
	{
		return m_impl;	
	}

	double to_double() const
	{
		return m_impl ? 1.0 : 0.0;			
	}

	int cstr(char* buf, size_t len) const
	{
		if(m_impl)
		{
			::strncpy(buf, "TRUE", len);
			return 4;
		}
		else
		{
			::strncpy(buf, "FALSE", len);
			return 5;	
		}
	}
	
	std::string to_str() const
	{
		return std::string(m_impl ? "TRUE" : "FALSE");
	}
	
	std::string inspect() const;

private:
	bool m_impl;
};

} // end of namespace ht

#endif // _ht_types_bool_h_
