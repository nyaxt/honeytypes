#include "honeytypes/types/types.h"

#include <sstream>

namespace ht
{

std::ostream&
operator<<(std::ostream& s, const ht::impltype_t t)
{
	switch(t)
	{
	#define DEFCASE(TYPE) case ht::impltype_t::T_##TYPE: s << "T_" #TYPE; break;
	DEFCASE(NullV);
	DEFCASE(BoolV);
	DEFCASE(IntV);
	DEFCASE(FloatV);
	DEFCASE(StringV);
	#undef DEFCASE
	}
	
	return s;
}
	
} // end of namespace ht

