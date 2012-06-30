#ifndef _ht_var_h_
#define _ht_var_h_

#include "types/types.h"
#include "types/null.h"

#ifdef HT_VERBOSE_FUNCCALL
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
	
	virtual int to_int() = 0;
	virtual std::string to_str() = 0;
	
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
	
	virtual int to_int()
	{
		return m_impl.to_int();
	}
	
	virtual std::string to_str()
	{
		return m_impl.to_str();	
	}
	
	virtual impltype_t getType()
	{
		return IMPLTYPE;	
	}
	
	VALUETYPE* getImpl()
	{
		return &m_impl;
	}
	
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
	
	template<typename T>
	explicit Var(T&& o)
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
	
	~Var()
	{
		getWrap()->~VarWrapBase();	
	}
	
	int to_int()
	{
		return getWrap()->to_int();	
	}

	std::string to_str()
	{
		return getWrap()->to_str();	
	}
	
	impltype_t getType()
	{
		return getWrap()->getType();
	}

private:
	detail::VarWrapBase* getWrap()
	{
		return reinterpret_cast<detail::VarWrapBase*>(m_implbuf);
	}
	
	union
	{
		char m_implbuf[SZ_VARIMPL];
		char* dummy[2];
	};
};

} // end of namespace ht

#endif // _ht_var_h_