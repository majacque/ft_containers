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

	/**
	 * @brief The object is initialized with the contents of the pr pair object.
	 * The corresponding member of pr is passed to the constructor of each of its members.
	 * 
	 * @param pr Another pair object.
	 * This may be an object of the same type as the object being constructed
	 * or of a pair type whose element's types are implicitly convertible to those in the pair being constructed.
	 */
	template<class U, class V>
	pair (pair<U,V> const &pr): first(pr.first), second(pr.second)
	{
		return;
	}
};

// TODO make_pair

}

#endif
