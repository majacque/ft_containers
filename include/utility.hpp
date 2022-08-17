#ifndef UTILITY_HPP
# define UTILITY_HPP

// DBG
#include <iostream>

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

	/**************************************************************************/
	/*                               CONSTRUCTOR                              */
	/**************************************************************************/

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
	pair( const first_type& a, const second_type& b ): first(a), second(b)
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
	pair( pair<U,V> const &pr ): first(pr.first), second(pr.second)
	{
		return;
	}

	/**************************************************************************/
	/*                               DESTRUCTOR                               */
	/**************************************************************************/

	/**
	 * @brief Destroy the pair object
	 */
	~pair( void )
	{
		return;
	}

	/**************************************************************************/
	/*                            MEMBER FUNCTIONS                            */
	/**************************************************************************/

	/**************************************************************************/
	/*                            MEMBER OPERATORS                            */
	/**************************************************************************/

	/**
	 * @brief Assigns @a pr as the new content for the pair object.
	 * 
	 * @par Member first is assigned pr.first, and member second is assigned pr.second
	 * 
	 * @param pr Another pair object.
	 * This may be an object of the same type or of a pair type whose elements' types are implicitly convertible.
	 * @return A reference on the instance
	 */
	pair& operator=( const pair& pr )
	{
		first = pr.first;
		second = pr.second;
		return *this;
	}
};

/**
 * @brief Performs the appropriate comparison operation between the pair objects lhs and rhs
 * 
 * @par Two pair objects compare equal to each other if both their first members compare equal to each other
 * and both their second members compare also equal to each other (in both cases using operator== for the comparison).
 * Similarly, operators <, >, <= and >= perform a lexicographical comparison on the sequence formed by members first and second
 * (in all cases using operator< reflexively for the comparisons).
 * 
 * @param lhs A pair object
 * @param rhs A pair object
 * @return true if the condition holds, and false otherwise
 */

template <class T1, class T2>
bool operator==( pair<T1,T2> const &lhs, pair<T1,T2> const &rhs )
{
	return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <class T1, class T2>
bool operator!=( pair<T1,T2> const &lhs, pair<T1,T2> const &rhs )
{
	return !(lhs == rhs);
}

template <class T1, class T2>
bool operator<( pair<T1,T2> const &lhs, pair<T1,T2> const &rhs )
{
	return lhs.first < rhs.first ||(!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template <class T1, class T2>
bool operator<=( pair<T1,T2> const &lhs, pair<T1,T2> const &rhs )
{
	return !(rhs < lhs);
}

template <class T1, class T2>
bool operator>( pair<T1,T2> const &lhs, pair<T1,T2> const &rhs )
{
	return rhs < lhs;
}

template <class T1, class T2>
bool operator>=( pair<T1,T2> const &lhs, pair<T1,T2> const &rhs )
{
	return !(lhs < rhs);
}

// TODO make_pair

}

#endif
