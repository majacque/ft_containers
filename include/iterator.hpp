#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <iterator>
// #include "type_traits.hpp"

namespace ft
{

template <class Iterator>
class iterator_traits
{
public:
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
};

template <class T>
class iterator_traits<T*>
{
public:
	typedef std::ptrdiff_t					difference_type;
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef std::random_access_iterator_tag	iterator_category;
};

template <class T>
class iterator_traits<const T*>
{
public:
	typedef std::ptrdiff_t					difference_type;
	typedef T								value_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	typedef std::random_access_iterator_tag	iterator_category;
};

template <class Iterator>
class reverse_iterator
{
protected:
	Iterator	_current;

public:
	typedef Iterator												iterator_type;
	typedef typename iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename iterator_traits<Iterator>::value_type			value_type;
	typedef typename iterator_traits<Iterator>::pointer				pointer;
	typedef typename iterator_traits<Iterator>::reference			reference;
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;

	/**************************************************************************/
	/*                               CONSTRUCTOR                              */
	/**************************************************************************/

	/**
	 * @brief Construct a new reverse iterator that points to no object
	 */
	reverse_iterator( void ): _current()
	{
		return;
	}
	
	/**
	 * @brief Construct a new reverse iterator from some original iterator it
	 * 
	 * @param it An iterator
	 */
	explicit reverse_iterator( iterator_type it ): _current(it)
	{
		return;
	}

	/**
	 * @brief Construct a new reverse iterator from some other reverse iterator
	 * 
	 * @param rev_it A reverse iterator
	 */
	template <typename _Tp>
	reverse_iterator( reverse_iterator<_Tp> const &rev_it): _current(rev_it.base())
	{
		return;
	}

	/**************************************************************************/
	/*                               DESTRUCTOR                               */
	/**************************************************************************/

	/**
	 * @brief Destroy the reverse iterator
	 */
	~reverse_iterator( void )
	{
		return;
	}

	/**************************************************************************/
	/*                            MEMBER FUNCTIONS                            */
	/**************************************************************************/

	/**
	 * @brief Returns a copy of the base iterator
	 */
	iterator_type	base( void ) const
	{
		return _current;
	}

	/**************************************************************************/
	/*                            MEMBER OPERATORS                            */
	/**************************************************************************/

	/**
	 * @brief Returns a reference to the element pointed to by the iterator
	 */
	reference operator*( void ) const
	{
		iterator_type	it(_current);
		--it;
		return *it;
	}

	/**
	 * @brief Returns a pointer to the element pointed to by the iterator (in order to access one of its members)
	 */
	pointer operator->() const
	{
		iterator_type	it(_current);
		--it;
		return it.operator->();
	}

	/**
	 * @brief Returns a reverse iterator pointing to the element located n positions away from the element the iterator currently points to
	 * 
	 * @param n Number of elements to offset
	 */
	reverse_iterator operator+( difference_type n ) const
	{
		return reverse_iterator(_current - n);
	}

	/**
	 * @brief Returns a reverse iterator pointing to the element located n positions before the element the iterator currently points to
	 * 
	 * @param n Number of elements to offset
	 */
	reverse_iterator operator-( difference_type n ) const
	{
		return reverse_iterator(_current + n);
	}

	/**
	 * @brief Advances the reverse_iterator by one position (pre-increment)
	 * 
	 * @return A reference on the instance
	 */
	reverse_iterator& operator++()
	{
		--_current;
		return *this;
	}

	/**
	 * @brief Advances the reverse_iterator by one position (post-increment)
	 * 
	 * @return The value the instance had before the call
	 */
	reverse_iterator operator++(int)
	{
		reverse_iterator	tmp(_current);
		--_current;
		return tmp;
	}

	/**
	 * @brief Decreases the reverse_iterator by one position (pre-decrement)
	 * 
	 * @return A reference on the instance
	 */
	reverse_iterator& operator--()
	{
		++_current;
		return *this;
	}

	/**
	 * @brief Decreases the reverse_iterator by one position (post-decrement)
	 * 
	 * @return The value the instance had before the call
	 */
	reverse_iterator operator--(int)
	{
		reverse_iterator	tmp(_current);
		++_current;
		return tmp;
	}

	/**
	 * @brief Advances the reverse_iterator by n element positions
	 * 
	 * @param n Number of elements to offset
	 * @return A reference on the instance
	 */
	reverse_iterator& operator+= ( difference_type n )
	{
		_current -= n;
		return *this;
	}

	/**
	 * @brief Descreases the reverse_iterator by n element positions
	 * 
	 * @param n Number of elements to offset
	 * @return A reference on the instance
	 */
	reverse_iterator& operator-= ( difference_type n )
	{
		_current += n;
		return *this;
	}

	/**
	 * @brief Accesses the element located n positions away from the element currently pointed to by the iterator.
	 * If such an element does not exist, it causes undefined behavior
	 * @param n Number of elements to offset
	 * @return A reference to the element n positions away from the element currently pointed by the iterator
	 */
	reference operator[] ( difference_type n ) const
	{
		return _current[-n-1];
	}

};

/**
 * @brief Performs the appropriate comparison operation between the reverse_iterator objects lhs and rhs
 * 
 * @param lhs A reverse iterator
 * @param rhs A reverse iterator
 * @return true if the comparison is true
 * @return false if the comparison is false
 */

template <class Iterator>
bool operator== ( reverse_iterator<Iterator> const &lhs, reverse_iterator<Iterator> const &rhs )
{
	return lhs.base() == rhs.base();
}

template <class IteratorL, class IteratorR>
bool operator==( reverse_iterator<IteratorL> const &lhs, reverse_iterator<IteratorR> const &rhs )
{
	return lhs.base() == rhs.base();
}

template <class Iterator>
bool operator!= ( reverse_iterator<Iterator> const &lhs, reverse_iterator<Iterator> const &rhs )
{
	return !(lhs == rhs);
}

template <class IteratorL, class IteratorR>
bool operator!= ( reverse_iterator<IteratorL> const &lhs, reverse_iterator<IteratorR> const &rhs )
{
	return !(lhs == rhs);
}

template <class Iterator>
bool operator< ( reverse_iterator<Iterator> const &lhs, reverse_iterator<Iterator> const &rhs )
{
	return lhs.base() > rhs.base();
}

template <class IteratorL, class IteratorR>
bool operator< ( reverse_iterator<IteratorL> const &lhs, reverse_iterator<IteratorR> const &rhs )
{
	return lhs.base() > rhs.base();
}

template <class Iterator>
bool operator<= ( reverse_iterator<Iterator> const &lhs, reverse_iterator<Iterator> const &rhs )
{
	return lhs.base() >= rhs.base();
}

template <class IteratorL, class IteratorR>
bool operator<= ( reverse_iterator<IteratorL> const &lhs, reverse_iterator<IteratorR> const &rhs )
{
	return lhs.base() >= rhs.base();
}

template <class Iterator>
bool operator> ( reverse_iterator<Iterator> const &lhs, reverse_iterator<Iterator> const &rhs )
{
	return !(lhs <= rhs);
}

template <class IteratorL, class IteratorR>
bool operator> ( reverse_iterator<IteratorL> const &lhs, reverse_iterator<IteratorR> const &rhs )
{
	return !(lhs <= rhs);
}

template <class Iterator>
bool operator>= ( reverse_iterator<Iterator> const &lhs, reverse_iterator<Iterator> const &rhs )
{
	return !(lhs < rhs);
}

template <class IteratorL, class IteratorR>
bool operator>= ( reverse_iterator<IteratorL> const &lhs, reverse_iterator<IteratorR> const &rhs )
{
	return !(lhs < rhs);
}

/**
 * @brief Returns a reverse iterator pointing to the element located n positions away from the element pointed to by rev_it
 * 
 * @param n Number of elements to offset
 * @param rev_it A reverse iterator
 */
template <class Iterator>
reverse_iterator<Iterator> operator+ ( typename reverse_iterator<Iterator>::difference_type n,
										reverse_iterator<Iterator> const &rev_it )
{
	return rev_it + n;
}

/**
 * @brief Returns the distance between lhs and rhs
 * 
 * @param lhs A reverse iterator
 * @param rhs A reverse iterator
 */
template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator- ( reverse_iterator<Iterator> const &lhs,
																 reverse_iterator<Iterator> const &rhs)
{
	return rhs.base() - lhs.base();
}

template <class IteratorL, class IteratorR>
typename reverse_iterator<IteratorL>::difference_type operator- ( reverse_iterator<IteratorL> const &lhs,
																 reverse_iterator<IteratorR> const &rhs)
{
	return rhs.base() - lhs.base();
}

}

namespace __ft
{

template <typename T>
class __normal_iterator
{
protected:
	T _current;

	typedef ft::iterator_traits<T>					traits_type;

public:
	typedef T										iterator_type;
	typedef typename traits_type::iterator_category	iterator_category;
	typedef typename traits_type::value_type		value_type;
	typedef typename traits_type::difference_type	difference_type;
	typedef typename traits_type::reference			reference;
	typedef typename traits_type::pointer			pointer;

	/**************************************************************************/
	/*                               CONSTRUCTOR                              */
	/**************************************************************************/

	__normal_iterator(): _current(iterator_type())
	{
		return;
	}

	explicit __normal_iterator(const iterator_type& it): _current(it)
	{
		return;
	}

	template <typename _T>
	__normal_iterator(__normal_iterator<_T> const & rhs)
		: _current(rhs.base())
	{
		return;
	}

	/**************************************************************************/
	/*                            MEMBER OPERATOR                             */
	/**************************************************************************/

	reference	operator*( void ) const
	{
		return *_current;
	}

	pointer	operator->( void ) const
	{
		return &(*_current);
	}

	__normal_iterator&	operator++( void )
	{
		++_current;
		return *this;
	}

	__normal_iterator	operator++( int )
	{
		__normal_iterator	tmp(_current);
		++_current;
		return tmp;
	}

	__normal_iterator&	operator--( void )
	{
		--_current;
		return *this;
	}

	__normal_iterator	operator--( int )
	{
		__normal_iterator	tmp(_current);
		--_current;
		return tmp;
	}

	reference	operator[]( difference_type n ) const
	{
		return _current[n];
	}

	__normal_iterator&	operator+=( difference_type n )
	{
		_current += n;
		return *this;
	}

	__normal_iterator	operator+( difference_type n ) const
	{
		return __normal_iterator(_current + n);
	}

	__normal_iterator&	operator-=( difference_type n )
	{
		_current -= n;
		return *this;
	}

	__normal_iterator	operator-( difference_type n ) const
	{
		return __normal_iterator(_current - n);
	}

	const iterator_type&	base( void ) const
	{
		return _current;
	}
};

/**************************************************************************/
/*                          NON-MEMBER OPERATOR                           */
/**************************************************************************/

template <typename _TpL, typename _TpR>
bool	operator==( __normal_iterator<_TpL> const & lhs, __normal_iterator<_TpR> const & rhs )
{
	return lhs.base() == rhs.base();
}

template <typename _Tp>
bool	operator==( __normal_iterator<_Tp> const & lhs, __normal_iterator<_Tp> const & rhs )
{
	return lhs.base() == rhs.base();
}

template <typename _TpL, typename _TpR>
bool	operator!=( __normal_iterator<_TpL> const & lhs, __normal_iterator<_TpR> const & rhs )
{
	return lhs.base() != rhs.base();
}

template <typename _Tp>
bool	operator!=( __normal_iterator<_Tp> const & lhs, __normal_iterator<_Tp> const & rhs )
{
	return lhs.base() != rhs.base();
}

template <typename _TpL, typename _TpR>
bool	operator<( __normal_iterator<_TpL> const & lhs, __normal_iterator<_TpR> const & rhs )
{
	return lhs.base() < rhs.base();
}

template <typename _Tp>
bool	operator<( __normal_iterator<_Tp> const & lhs, __normal_iterator<_Tp> const & rhs )
{
	return lhs.base() < rhs.base();
}

template <typename _TpL, typename _TpR>
bool	operator>( __normal_iterator<_TpL> const & lhs, __normal_iterator<_TpR> const & rhs )
{
	return lhs.base() > rhs.base();
}

template <typename _Tp>
bool	operator>( __normal_iterator<_Tp> const & lhs, __normal_iterator<_Tp> const & rhs )
{
	return lhs.base() > rhs.base();
}

template <typename _TpL, typename _TpR>
bool	operator<=( __normal_iterator<_TpL> const & lhs, __normal_iterator<_TpR> const & rhs )
{
	return lhs.base() <= rhs.base();
}

template <typename _Tp>
bool	operator<=( __normal_iterator<_Tp> const & lhs, __normal_iterator<_Tp> const & rhs )
{
	return lhs.base() <= rhs.base();
}

template <typename _TpL, typename _TpR>
bool	operator>=( __normal_iterator<_TpL> const & lhs, __normal_iterator<_TpR> const & rhs )
{
	return lhs.base() >= rhs.base();
}

template <typename _Tp>
bool	operator>=( __normal_iterator<_Tp> const & lhs, __normal_iterator<_Tp> const & rhs )
{
	return lhs.base() >= rhs.base();
}

template <typename _TpL, typename _TpR>
typename __normal_iterator<_TpL>::difference_type
	operator-( __normal_iterator<_TpL> const & lhs,
			__normal_iterator<_TpR> const & rhs )
{
	return lhs.base() - rhs.base();
}

template <typename _Tp>
typename __normal_iterator<_Tp>::difference_type
	operator-( __normal_iterator<_Tp> const & lhs,
			__normal_iterator<_Tp> const & rhs )
{
	return lhs.base() - rhs.base();
}

template <typename _Tp>
__normal_iterator<_Tp>
	operator+( typename __normal_iterator<_Tp>::difference_type n,
			__normal_iterator<_Tp> const & it )
{
	return __normal_iterator<_Tp>(it.base() + n);
}

}

#endif
