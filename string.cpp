#include "honeytypes/types/string.h"

namespace ht
{
	
int
StringV::to_int() const
{
	return strtol(m_impl.c_str(), nullptr, 0);
}
	
} // end of namespace ht

