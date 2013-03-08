#ifndef _ht_types_int_h_
#define _ht_types_int_h_

#include "types.h"

namespace ht
{
	
class IntV
{
public:
	constexpr static impltype_t IMPLTYPE = impltype_t::T_IntV;
		
	typedef int INT_T;	

	IntV(INT_T n = 0)
	:	m_impl(n)
	{ /* NOP */ }

	bool operator==(const IntV& o) const
	{
		return m_impl == o.m_impl;
	}

	bool operator!=(const IntV& o) const
	{
		return m_impl != o.m_impl;	
	}
	
	int to_int() const
	{
		return m_impl;
	}

	bool to_bool() const
	{
		return (m_impl != 0);
	}

	double to_double() const
	{
		return static_cast<double>(m_impl);
	}

	int cstr(char* buf, size_t len) const
	{
		return snprintf(buf, len, "%d", m_impl);
	}
	
	std::string to_str() const
	{
		char buf[256];
		snprintf(buf, sizeof buf, "%d", m_impl);
		return std::string(buf);
	}
	
	std::string inspect() const;
	
	size_t hash() const
	{
		return std::hash<INT_T>()(m_impl);	
	}

private:
	INT_T m_impl;
};

} // end of namespace ht

#endif // _ht_types_int_h_
