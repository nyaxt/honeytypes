#define HT_VERBOSE_FUNCCALL

#include "honeytypes/var.h"
#include "honeytypes/types/int.h"
#include "honeytypes/types/string.h"

namespace ht
{
	
namespace detail
{
	template class VarWrap<IntV>;
	static_assert(sizeof(VarWrap<IntV>) < SZ_VARIMPL, "sizeof(VarIntV) larger than fixed-allocation size");

	template class VarWrap<StringV>;
	static_assert(sizeof(VarWrap<StringV>) < SZ_VARIMPL, "sizeof(VarIntV) larger than fixed-allocation size");
};

void
Var::copyCtorImpl(const Var& o)
{
	switch(o.getType())
	{
	case impltype_t::T_NullV:
		new (m_implbuf)detail::VarWrap<NullV>();
		break;
	case impltype_t::T_IntV:
		new (m_implbuf)detail::VarWrap<IntV>(*o.getWrapImpl<IntV>());
		break;
	case impltype_t::T_StringV:
		new (m_implbuf)detail::VarWrap<StringV>(*o.getWrapImpl<StringV>());
		break;
	}
}

Var&
Var::operator=(const Var& o)
{
	HT_PRINT_FUNCNAME;
	
	impltype_t mytype = getType();
	if(mytype == o.getType())
	{
		// same impl. type...

		// call assign op.	
		switch(getType())
		{
		case impltype_t::T_NullV:
			break;
		case impltype_t::T_IntV:
			*getWrapImpl<IntV>() = *o.getWrapImpl<IntV>();
			break;
		case impltype_t::T_StringV:
			*getWrapImpl<StringV>() = *o.getWrapImpl<StringV>();
			break;
		}
	}
	else
	{
		// different impl. type...

		// destruct once and re-init using copy-ctor
		this->~Var();
		try
		{
			copyCtorImpl(o);
		}
		catch(...)
		{
			new (m_implbuf)detail::VarWrap<NullV>();
			throw;	
		}
	}

	return *this;
}

} // end of namespace ht

