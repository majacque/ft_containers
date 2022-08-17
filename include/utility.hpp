#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft
{

// TODO pair

template <class T1, class T2> 
struct pair
{
	typedef T1	first_type;
	typedef T2	second_type;

	T1	first;
	T2	second;

	/**
	 * @brief Constructs a pair object with its elements value-initialized
	 */
	pair( void ): first(T1()), second(T2())
	{
		return;
	}

	/**
	 * @brief Member first is constructed with a and member second with b
	 * 
	 * @param a An object of the type of first, or some other type implicitly convertible to it
	 * @param b An object of the type of second, or some other type implicitly convertible to it
	 */
	pair (const first_type& a, const second_type& b): first(a), second(b)
	{
		return;
	}
};

// TODO make_pair

}

#endif
