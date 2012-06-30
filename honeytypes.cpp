#include <iostream>
#include <memory>
#include <type_traits>
#include <string.h>

#include "honeytypes/var.h"
#include "honeytypes/types/int.h"
#include "honeytypes/types/string.h"

// #define HT_VERBOSE_FUNCCALL

namespace ht
{
	
namespace detail
{
	template class VarWrap<IntV>;
	static_assert(sizeof(VarWrap<IntV>) < SZ_VARIMPL, "sizeof(VarIntV) larger than fixed-allocation size");

	template class VarWrap<StringV>;
};
	
int
StringV::to_int()
{
	return strtol(m_impl.c_str(), nullptr, 0);
}

} // end of namespace ht

