#ifndef _ht_as_h_
#define _ht_as_h_

namespace ht
{
	
template<typename T>
struct as
{
	template<typename V>
	T operator()(const V& v);
};

template<>
struct as<int>
{
	template<typename V>
	int operator()(const V& v)
	{
		return v.to_int();
	}
};

template<>
struct as<std::string>
{
	template<typename V>
	std::string operator()(const V& v)
	{
		return v.to_str();	
	};
};
	
} // end of namespace ht

#endif // _ht_as_h_
