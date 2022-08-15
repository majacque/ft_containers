#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <iterator>

namespace ft
{

template<class Iterator>
class iterator_traits
{
public:
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
};

template<class T>
class iterator_traits<T*>
{
public:
	typedef std::ptrdiff_t					difference_type;
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef std::random_access_iterator_tag	iterator_category;
};

template<class T>
class iterator_traits<const T*>
{
public:
	typedef std::ptrdiff_t					difference_type;
	typedef T								value_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	typedef std::random_access_iterator_tag	iterator_category;
};

// TODO reverse_iterator

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
	 * @param it an iterator
	 */
	explicit reverse_iterator( iterator_type it ): _current(it)
	{
		return;
	}

	/**
	 * @brief Construct a new reverse iterator from some other reverse iterator
	 * 
	 * @param rev_it a reverse iterator
	 */
	reverse_iterator( reverse_iterator const &rev_it): _current(rev_it._current)
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
	iterator_type	base( void )
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
	 * @brief Returns a reverse iterator pointing to the element located n positions away from the element the iterator currently points to
	 * 
	 * @param n Number of elements to offset
	 */
	reverse_iterator operator+(difference_type n) const
	{
		return reverse_iterator(_current - n);
	}

	/**
	 * @brief Returns a reverse iterator pointing to the element located n positions before the element the iterator currently points to
	 * 
	 * @param n Number of elements to offset
	 */
	reverse_iterator operator-(difference_type n) const
	{
		return reverse_iterator(_current + n);
	}

	/**
	 * @brief Advances the reverse_iterator by one position (pre-increment)
	 * 
	 * @return a reference on the instance
	 */
	reverse_iterator& operator++()
	{
		--_current;
		return *this;
	}

	/**
	 * @brief Advances the reverse_iterator by one position (post-increment)
	 * 
	 * @return the value the instance had before the call
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
	 * @return a reference on the instance
	 */
	reverse_iterator& operator--()
	{
		++_current;
		return *this;
	}

	/**
	 * @brief Decreases the reverse_iterator by one position (post-decrement)
	 * 
	 * @return the value the instance had before the call
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
	 * @return a reference on the instance
	 */
	reverse_iterator& operator+= (difference_type n)
	{
		_current -= n;
		return *this;
	}

	/**
	 * @brief Descreases the reverse_iterator by n element positions
	 * 
	 * @param n Number of elements to offset
	 * @return a reference on the instance
	 */
	reverse_iterator& operator-= (difference_type n)
	{
		_current += n;
		return *this;
	}

};

}

#endif
