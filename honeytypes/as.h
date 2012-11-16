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
struct as<float>
{
	template<typename V>
	float operator()(const V& v)
	{
		return v.to_double();
	}
};

template<>
struct as<double>
{
	template<typename V>
	double operator()(const V& v)
	{
		return v.to_double();	
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

//! similar to std::less for Var types
template<typename T>
struct less_as
{
	template<typename V>
	bool operator()(const V& a, const V& b)
	{
		return as<T>()(a) < as<T>()(b);	
	}
};

//! similar to std::greater for Var types
template<typename T>
struct greater_as
{
	template<typename V>
	bool operator()(const V& a, const V& b)
	{
		return as<T>()(a) > as<T>()(b);
	}
};
	
} // end of namespace ht

#endif // _ht_as_h_
