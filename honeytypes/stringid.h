#ifndef _ht_stringid_h_
#define _ht_stringid_h_

#include <string>
#include <string.h>
#include <functional> // for std::hash

// #define HT_FALLBACK_STRINGID

#ifdef HT_FALLBACK_STRINGID
namespace ht
{
	typedef std::string StringId;
};
#else
namespace ht
{

class StringId
{
public:
	StringId()
	{ 
		/* NOP */
	}
	
	StringId(const StringId& o)
	:	m_str(o.m_str),
		m_hash(o.m_hash)
	{
		/* NOP */
	}
	
	StringId& operator=(const StringId& o)
	{
		m_str = o.m_str;
		m_hash = o.m_hash;
		
		return *this;
	}

	StringId(StringId&& o)
	:	m_str(std::move(o.m_str)),
		m_hash(o.m_hash)
	{
		/* NOP */
	}
	
	StringId& operator=(StringId&& o)
	{
		m_str = std::move(o.m_str);
		m_hash = o.m_hash;
		
		return *this;
	}

	//! c-tor
	/*!
	 *	@param [in] str
	 *	  str may not contain null bytes '\0' inside.
	 */
	StringId(const std::string& str)
	:	m_str(str)
	{
		updateHash();
	}

	//! c-tor: from null term c string
	StringId(const char* cstr)
	:	m_str(cstr)
	{
		updateHash();	
	}
	
	StringId& operator=(const std::string& str)
	{
		m_str = str;
		updateHash();	
		
		return *this;
	}
	
	StringId(std::string&& str)
	:	m_str(std::move(str))
	{
		updateHash();
	}
	
	StringId& operator=(std::string&& str)
	{
		m_str = std::move(str);
		updateHash();
		
		return *this;
	}

	bool operator<(const StringId o) const
	{
		if(m_hash != o.m_hash) return m_hash < o.m_hash;

		return m_str < o.m_str;
	}
	
	bool operator==(const StringId& o) const
	{
		if(m_hash != o.m_hash) return false;

		return m_str == o.m_str;
	}
	
	bool operator!=(const StringId& o) const
	{
		if(m_hash != o.m_hash) return true;
		
		return m_str != o.m_str;
	}
	
	bool operator==(const std::string& o) const
	{
		return m_str == o;	
	}
	
	bool operator!=(const std::string& o) const
	{
		return m_str != o;	
	}
	
	size_t hash() const noexcept(true)
	{
		return m_hash;
	}
	
	const std::string& str() const noexcept(true)
	{
		return m_str;
	}

	bool empty() const noexcept(true)
	{
		return m_str.empty();	
	}
	
	//! only for testing purposes
	void setHash_(size_t h) { m_hash = h; }
	
private:
	void updateHash() noexcept(true);
	
	static constexpr size_t SZ_CMPBUF = sizeof(size_t);
	
	std::string m_str;
	size_t m_hash = 0;
};
std::ostream& operator<<(std::ostream& s, const StringId& o);

inline
bool operator==(const std::string& a, const StringId& b)
{
	return b == a;
}

inline
bool operator!=(const std::string& a, const StringId& b)
{
	return b != a;
}

} // end of namespace ht

namespace std
{
	
template<>
struct hash< ::ht::StringId>
{
	size_t operator()(const ::ht::StringId& strid) const noexcept(true)
	{
		return strid.hash();
	}
};

template<>
struct less< ::ht::StringId>
{
	bool operator()(const ::ht::StringId& a, const::ht::StringId& b) const noexcept(true)
	{
		return std::less<std::string>()(a.str(), b.str());
	}
};

};

#endif // HT_FALLBACK_STRINGID

#endif // _ht_stringid_h_
