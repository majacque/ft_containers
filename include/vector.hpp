#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "iterator.hpp"
#include <memory>

namespace ft
{
template < class T, class Alloc = std::allocator<T> >
class vector
{
public:
	typedef T														value_type;
	typedef Alloc													allocator_type;
	typedef typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference				const_reference;
	typedef typename allocator_type::pointer						pointer;
	typedef typename allocator_type::const_pointer					const_pointer;
	// TODO vector_iterator
	// typedef typename ft::vector_iterator<pointer>				iterator;
	// typedef typename ft::vector_iterator<const_pointer>			const_iterator;
	// typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
	// typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;
	// typedef typename iterator_traits<iterator>::difference_type	difference_type;
	typedef size_t													size_type;

private:
	pointer	_head;
	pointer	_tail;
	pointer	_end_of_storage;

public:

	/**
	 * @brief Constructs an empty vector, with no elements.
	 * 
	 * @param alloc Allocator object.
	 */
	explicit vector (allocator_type const &alloc __attribute__((unused)) = allocator_type()):
										_head(pointer()), _tail(_head), _end_of_storage(_head)
	{
		return;
	}

	/**
	 * @brief Constructs a vector with n elements. Each element is a copy of val.
	 * 
	 * @param n Initial container size (i.e., the number of elements in the container at construction).
	 * @param val Value to fill the container with. Each of the n elements in the container will be initialized to a copy of this value.
	 * @param alloc Allocator object.
	 */
	explicit vector (size_type n, value_type const &val = value_type(), allocator_type const &alloc = allocator_type()):
																					_head(), _tail(), _end_of_storage()
	{
		// TODO insert() (fill) or __insert_fill()
		return;
	}

	// TODO size()
	// TODO operator[]

};

}

#endif
