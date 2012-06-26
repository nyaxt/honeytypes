#include <iostream>
#include <memory>
#include <type_traits>
#include <string.h>

namespace ht
{

enum class impltype_t : uint8_t
{
	T_Null,
	T_Int,
	T_String,
};

class Null
{
public:
	constexpr static impltype_t IMPLTYPE = impltype_t::T_Null;
	
	Null()
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
class Int
{
public:
	constexpr static impltype_t IMPLTYPE = impltype_t::T_Int;
		
	typedef int INT_T;	

	Int(INT_T n = 0)
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

class String
{
public:
	constexpr static impltype_t IMPLTYPE = impltype_t::T_String;

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
String::to_int()
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

	template<typename ...ARGS>
	VarWrap(ARGS ...args)
	:	VarWrapBase(IMPLTYPE), m_impl(std::forward<ARGS>(args)...)
	{ /* NOP */ }
	
	virtual ~VarWrap()
	{ /* NOP */ 
		std::cout << "~varimpl:: type: " << static_cast<uint16_t>(IMPLTYPE) << std::endl;
	}
	
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

template class VarWrap<Int>;
static_assert(sizeof(VarWrap<Int>) < SZ_VARIMPL, "sizeof(VarInt) larger than fixed-allocation size");

template class VarWrap<String>;

} // end of namespace detail

class Var
{
public:
	//! default c-tor
	/*!
	 *  init as "Null" value
	 */
	Var()
	{
		new (m_implbuf)detail::VarWrap<Null>();
	}
	
	//! copy c-tor
	template<typename T>
	explicit Var(const T& o)
	{
		new (m_implbuf)detail::VarWrap<T>(o);
	}
	
	//! move c-tor
	template<typename T>
	explicit Var(T&& o)
	{
		typedef typename std::decay<T>::type VALUETYPE;
		new (m_implbuf)detail::VarWrap<VALUETYPE>(std::forward<T>(o));
	}
	
	//! copy assign-op
	template<typename T>
	Var& operator=(const T& o)
	{
		if(getType() == detail::VarWrap<T>::IMPLTYPE)
		{
			// call assign op if possible (string can use a shared buffer for instance)
			T* p = reinterpret_cast<detail::VarWrap<T>*>(getWrap())->getImpl();
			*p = o;
		}
		else
		{
			getWrap()->~VarWrapBase();
			try
			{
				new (m_implbuf)detail::VarWrap<T>(o);
			}
			catch(...)
			{
				new (m_implbuf)detail::VarWrap<Null>();
				throw;
			}
		}
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

using namespace ht;

int main(int argc, char* argv[])
{
	Int intv;
	intv = Int(30);
	std::cout << "i: " << intv.to_str() << std::endl;
	
	Var v(intv);
	std::cout << "v: " << v.to_str() << std::endl;
	
	Var v2(Int(50));
	std::cout << "v2: " << v.to_str() << std::endl;

	return 0;
}
