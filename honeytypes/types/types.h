#ifndef _ht_types_types_h_
#define _ht_types_types_h_

#include <iostream>
#include <stdint.h> // various int types
#include <unistd.h> // size_t
#include <string>

namespace ht
{
	
class NullV;
class BoolV;
class IntV;
class FloatV;
class StringV;

enum class impltype_t : uint8_t
{
	T_NullV,
	T_BoolV,
	T_IntV,
	T_FloatV,
	T_StringV,
};
std::ostream& operator<<(std::ostream& s, const impltype_t type);

} // end of namespace ht

#endif // _ht_types_types_h_
