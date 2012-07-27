#ifndef _ht_types_float_h_
#define _ht_types_float_h_

#include <cmath>
#include "types.h"

namespace ht
{
	
class FloatV
{
public:
	constexpr static impltype_t IMPLTYPE = impltype_t::T_FloatV;
		
	typedef double FLOAT_T;	

	FloatV(FLOAT_T n = static_cast<FLOAT_T>(0.0))
	:	m_impl(n)
	{ /* NOP */ }
	
	int to_int() const
	{
		return static_cast<int>(m_impl);
	}

	bool to_bool() const
	{
		constexpr FLOAT_T THRESHOLD = static_cast<FLOAT_T>(1e-8);
		return std::fabs(m_impl) < THRESHOLD;
	}

	double to_double() const
	{
		return m_impl;	
	}

	int cstr(char* buf, size_t len) const
	{
		return snprintf(buf, len, "%f", m_impl);
	}
	
	std::string to_str() const
	{
		char buf[256];
		snprintf(buf, sizeof buf, "%f", m_impl);
		return std::string(buf);
	}
	
	std::string inspect() const;

private:
	FLOAT_T m_impl;
};

} // end of namespace ht

#endif // _ht_types_float_h_
