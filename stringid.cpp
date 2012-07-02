#include "honeytypes/stringid.h"

namespace ht
{
	
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
	
} // end of namespace ht

