#ifndef _ht_types_types_h_
#define _ht_types_types_h_

#include <stdint.h> // various int types
#include <unistd.h> // size_t
#include <string>

namespace ht
{
	
enum class impltype_t : uint8_t
{
	T_NullV,
	T_IntV,
	T_StringV,
};

} // end of namespace ht

#endif // _ht_types_types_h_
