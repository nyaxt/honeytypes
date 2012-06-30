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
	
	int to_int()
	{
		return m_impl;
	}

	int cstr(char* buf, size_t len)
	{
		return snprintf(buf, len, "%d", m_impl);
	}
	
	std::string to_str()
	{
		char buf[256];
		snprintf(buf, sizeof buf, "%d", m_impl);
		return std::string(buf);
	}

private:
	INT_T m_impl;
};

} // end of namespace ht

#endif // _ht_types_int_h_
