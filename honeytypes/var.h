#ifndef _ht_var_h_
#define _ht_var_h_

#include <string>
#include <string.h>

#include "types/types.h"
#include "types/null.h"
#include <honeytypes/methods.gen.h>

#ifdef HT_VERBOSE_FUNCCALL
#include <iostream>
#define HT_PRINT_FUNCNAME do { std::cout << __PRETTY_FUNCTION__ << std::endl; } while(false);
#else
#define HT_PRINT_FUNCNAME 
#endif

namespace ht
{
	
constexpr size_t SZ_VARIMPL = 128; // sizeof(ptr)*2 should be enough!
	
namespace detail
{

class VarWrapBase
{
public:
	VarWrapBase(impltype_t impltype)
	:	m_impltype(impltype)
	{ /* NOP */ }
	
	virtual ~VarWrapBase() = 0;
	
	METHODS_VARWRAPBASE
	
	// ====== accessor methods ======
	
	impltype_t getType() const
	{
		return m_impltype;	
	}
	
private:
	impltype_t m_impltype;
};

inline
VarWrapBase::~VarWrapBase()
{ /* NOP */ }

template<typename T>
class VarWrap : public VarWrapBase
{
public:
	// typedef typename std::decay<T>::type VALUETYPE;
	typedef T VALUETYPE;
	constexpr static impltype_t IMPLTYPE = T::IMPLTYPE;
	
	VarWrap()
	:	VarWrapBase(IMPLTYPE)
	{ /* NOP */ }
	
	VarWrap(const VALUETYPE& o)
	:	VarWrapBase(IMPLTYPE), m_impl(o)
	{
		HT_PRINT_FUNCNAME;
	}

	VarWrap(VALUETYPE&& o)
	:	VarWrapBase(IMPLTYPE), m_impl(std::move(o))
	{ 
		HT_PRINT_FUNCNAME;
	}
	
	VarWrap& operator=(const VALUETYPE& o)
	{
		HT_PRINT_FUNCNAME;

		m_impl = o;
		
		return *this;
	}
	
	VarWrap& operator=(VALUETYPE&& o)
	{
		HT_PRINT_FUNCNAME;

		m_impl = std::move(o);
		
		return *this;
	}
	
	virtual ~VarWrap()
	{ /* NOP */ }
	
	virtual impltype_t getType()
	{
		return IMPLTYPE;	
	}
	
	VALUETYPE* getImpl()
	{
		return &m_impl;
	}
	
	const VALUETYPE* getImpl() const
	{
		return &m_impl;
	}
	
	METHODS_VAR(virtual, getImpl())
	
private:
	VALUETYPE m_impl;
};

} // end of namespace detail

class Var
{
public:
	//! default c-tor
	/*!
	 *  init as "NullV" value
	 */
	Var()
	{
		new (m_implbuf)detail::VarWrap<NullV>();
	}
	
	~Var()
	{
		getWrap()->~VarWrapBase();	
	}

	//! copy c-tor
	Var(const Var& o)
	{
		HT_PRINT_FUNCNAME;
		copyCtorImpl(o);
	}
	
	//! copy assign op.
	Var& operator=(const Var& o);
	
	//! move c-tor
	Var(Var&& o)
	{
		HT_PRINT_FUNCNAME;
		
		::memcpy(m_implbuf, o.m_implbuf, sizeof(m_implbuf));
		new (o.m_implbuf)detail::VarWrap<NullV>();
	}
	
	//! move assign op.
	Var& operator=(Var&& o)
	{
		HT_PRINT_FUNCNAME;
		
		this->~Var();
		::memcpy(m_implbuf, o.m_implbuf, sizeof(m_implbuf));
		new (o.m_implbuf)detail::VarWrap<NullV>();
		
		return *this;
	}
	
	template<typename T>
	Var(T&& o)
	{
		HT_PRINT_FUNCNAME;
		typedef typename std::decay<T>::type VALUETYPE;
		new (m_implbuf)detail::VarWrap<VALUETYPE>(std::forward<T>(o));
	}
	
	template<typename T>
	Var& operator=(T&& o)
	{
		HT_PRINT_FUNCNAME;
		typedef typename std::decay<T>::type VALUETYPE;
		
		if(getType() == detail::VarWrap<VALUETYPE>::IMPLTYPE) // FIXME: add opt. compare vtable ptr == should be enough
		{
			// call assign op if possible (string can use a shared buffer for instance)
			auto vw = reinterpret_cast<detail::VarWrap<VALUETYPE>*>(getWrap());
			*vw = std::forward<T>(o);
		}
		else
		{
			getWrap()->~VarWrapBase();
			try
			{
				new (m_implbuf)detail::VarWrap<VALUETYPE>(std::forward<T>(o));
			}
			catch(...)
			{
				new (m_implbuf)detail::VarWrap<NullV>();
				throw;
			}
		}
		
		return *this;
	}
	
	METHODS_VAR(, getWrap())
	
	impltype_t getType() const
	{
		return getWrap()->getType();
	}
	
private:
	void copyCtorImpl(const Var& o);	

	detail::VarWrapBase* getWrap()
	{
		return reinterpret_cast<detail::VarWrapBase*>(m_implbuf);
	}
	
	const detail::VarWrapBase* getWrap() const
	{
		return reinterpret_cast<const detail::VarWrapBase*>(m_implbuf);
	}
	
	template<typename T>
	detail::VarWrap<T>* getWrapImpl()
	{
		return reinterpret_cast<detail::VarWrap<T>*>(m_implbuf);
	}
	
	template<typename T>
	const detail::VarWrap<T>* getWrapImpl() const
	{
		return reinterpret_cast<const detail::VarWrap<T>*>(m_implbuf);
	}
	
	union
	{
		char m_implbuf[SZ_VARIMPL];
		char* dummy[2];
	};
};

#undef METHODS_VARWRAPBASE
#undef METHODS_VAR

} // end of namespace ht

#endif // _ht_var_h_
