#include "honeytypes/types/string.h"

#include <sstream>

namespace ht
{
	
int
StringV::to_int() const
{
	return strtol(m_impl.c_str(), nullptr, 0);
}

bool
StringV::to_bool() const
{
	if(m_impl.empty()) return false;

	if(m_impl == "FALSE") return false;

	return true;
}

double
StringV::to_double() const
{
	std::istringstream ss(m_impl);
	double ret;
	if(! (ss >> ret)) return 0.0;
	return ret;
}
	
} // end of namespace ht

