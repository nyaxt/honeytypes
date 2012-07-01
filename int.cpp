#include "honeytypes/types/int.h"

#include <sstream>

namespace ht
{
	
std::string
IntV::inspect() const
{
	std::ostringstream o;
	o << "#<IntV: " << m_impl << ">";	

	return o.str();
}
	
} // end of namespace ht

