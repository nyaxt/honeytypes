#include "honeytypes/types/float.h"

#include <sstream>

namespace ht
{
	
std::string
FloatV::inspect() const
{
	std::ostringstream o;
	o << "#<FloatV: " << m_impl << ">";	

	return o.str();
}
	
} // end of namespace ht

