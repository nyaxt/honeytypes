#define HT_VERBOSE_FUNCCALL

#include "honeytypes/var.h"
#include "honeytypes/types/bool.h"
#include "honeytypes/types/int.h"
#include "honeytypes/types/float.h"
#include "honeytypes/types/string.h"

namespace ht
{
	
// no explicit instantiation for now
#if 0

namespace detail
{

#define INSTANTIATE(TYPE) \
	template class VarWrap<TYPE>; \
	static_assert(sizeof(VarWrap<TYPE>) < SZ_VARIMPL, "sizeof(VarWrap<" #TYPE ">) larger than fixed-allocation size");

	INSTANTIATE(BoolV);
	INSTANTIATE(IntV);
	INSTANTIATE(FloatV);
	INSTANTIATE(StringV);
#undef INSTANTIATE

};

#endif

void
Var::copyCtorImpl(const Var& o)
{
	switch(o.getType())
	{
	case impltype_t::T_NullV:
		new (m_implbuf)detail::VarWrap<NullV>();
		break;
#define DEFCASE(TYPE) \
	case impltype_t::T_##TYPE: \
		new (m_implbuf)detail::VarWrap<TYPE>(*o.getWrapImpl<TYPE>()); \
		break;
	DEFCASE(BoolV);
	DEFCASE(IntV);
	DEFCASE(FloatV);
	DEFCASE(StringV);
#undef DEFCASE
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
#define DEFCASE(TYPE) \
		case impltype_t::T_##TYPE: \
			*getWrapImpl<TYPE>() = *o.getWrapImpl<TYPE>(); \
			break;

		case impltype_t::T_NullV:
			break;

		DEFCASE(BoolV);
		DEFCASE(IntV);
		DEFCASE(FloatV);
		DEFCASE(StringV);
#undef DEFCASE
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

bool
Var::operator==(const Var& o) const
{
	if(getType() != o.getType()) return false;

	switch(getType())
	{
#define DEFCASE(TYPE) \
		case impltype_t::T_##TYPE: \
			return *getWrapImpl<TYPE>()->getImpl() == *o.getWrapImpl<TYPE>()->getImpl();
		DEFCASE(NullV);
		DEFCASE(BoolV);
		DEFCASE(IntV);
		DEFCASE(FloatV);
		DEFCASE(StringV);
#undef DEFCASE
	}

	/* NOT REACHED */
	return false;
}

} // end of namespace ht

