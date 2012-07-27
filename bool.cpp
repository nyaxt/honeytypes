#include "honeytypes/types/bool.h"

#include <sstream>

namespace ht
{
	
std::string
BoolV::inspect() const
{
	std::ostringstream o;
	o << "#<BoolV: " << (m_impl ? "TRUE" : "FALSE") << ">";	

	return o.str();
}
	
} // end of namespace ht

