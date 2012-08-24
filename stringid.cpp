#include "honeytypes/stringid.h"

namespace ht
{

std::ostream&
operator<<(std::ostream& s, const StringId& o)
{
	s << o.str();

	return s;
}
	
void
StringId::updateHash() noexcept(true)
{
	if(m_str.size() <= sizeof(m_hash))
	{
		::strncpy(reinterpret_cast<char*>(&m_hash), m_str.data(), sizeof(m_hash));
	}
	else
	{
		std::hash<std::string> h;
		m_hash = h(m_str);
	}
}

bool
StringId::operator<(const StringId& o) const
{
	if(m_hash != o.m_hash) return m_hash < o.m_hash;

	size_t cmplen = std::min(m_str.size(), o.m_str.size());
	int c = ::memcmp(m_str.data(), o.m_str.data(), cmplen);
	if(c != 0) return (c < 0);

	return (m_str.size() < o.m_str.size());
}

} // end of namespace ht

