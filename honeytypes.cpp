#include <iostream>
#include <memory>
#include <type_traits>
#include <string.h>

namespace ht
{

enum class impltype_t : uint8_t
{
	T_NullV,
	T_IntV,
	T_StringV,
};

class NullV
{
public:
	constexpr static impltype_t IMPLTYPE = impltype_t::T_NullV;
	
	NullV()
	{ /* NOP */ }
	
	int to_int()
	{
		return 0;	
	}
	
	int cstr(char*, size_t)
	{
		return 0;
	}
	
	std::string to_str()
	{
		return std::string();	
	}
};

// template<typename INT_T>
class IntV
{
public:
	constexpr static impltype_t IMPLTYPE = impltype_t::T_IntV;
		
	typedef int INT_T;	

	IntV(INT_T n = 0)
	:	m_impl(n)
	{ /* NOP */ }
	
	int to_int()
	{
		return m_impl;
	}

	int cstr(char* buf, size_t len)
	{
		return snprintf(buf, len, "%d", m_impl);
	}
	
	std::string to_str()
	{
		char buf[256];
		snprintf(buf, sizeof buf, "%d", m_impl);
		return std::string(buf);
	}

private:
	INT_T m_impl;
};

class StringV
{
public:
	constexpr static impltype_t IMPLTYPE = impltype_t::T_StringV;

	int to_int();
	
	int cstr(char* buf, size_t len)
	{
		char* pe = ::strncpy(buf, m_impl.data(), len);	
		return pe - buf;
	}
	
	std::string to_str()
	{
		return std::string(m_impl);	
	}
	
private:
	std::string m_impl;
};

int
StringV::to_int()
{
	return strtol(m_impl.c_str(), nullptr, 0);
}

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
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	VarWrap(VALUETYPE&& o)
	:	VarWrapBase(IMPLTYPE), m_impl(std::move(o))
	{ 
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
	
	VarWrap& operator=(const VALUETYPE& o)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;

		m_impl = o;
		
		return *this;
	}
	
	VarWrap& operator=(VALUETYPE&& o)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;

		m_impl = std::forward<VALUETYPE>(o);
		
		return *this;
	}
	
	// VarWrap(const VarWrap<T>& o)
	// :	VarWrapBase(IMPLTYPE), m_impl(o.m_impl)
	// { /* NOP */ std::cout <<"copy vw";}
	// 
	// VarWrap(VarWrap<T>&& o)
	// :	VarWrapBase(IMPLTYPE), m_impl(std::move(o.m_impl))
	// { /* NOP */ std::cout <<"move vw"; }

	// template<typename ...ARGS>
	// VarWrap(ARGS ...args)
	// :	VarWrapBase(IMPLTYPE), m_impl(std::forward<ARGS>(args)...)
	// { /* NOP */ }
	
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

template class VarWrap<IntV>;
static_assert(sizeof(VarWrap<IntV>) < SZ_VARIMPL, "sizeof(VarIntV) larger than fixed-allocation size");

template class VarWrap<StringV>;

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
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		typedef typename std::decay<T>::type VALUETYPE;
		new (m_implbuf)detail::VarWrap<VALUETYPE>(std::forward<T>(o));
	}
	
	//! copy assign-op
	template<typename T>
	Var& operator=(T&& o)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
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
	
	//! move assign-op
	// todo
	
	// void reset() // todo
	
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

