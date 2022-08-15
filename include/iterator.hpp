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

	/**
	 * @brief Construct a new reverse iterator that points to no object
	 * 
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

};

}

#endif
