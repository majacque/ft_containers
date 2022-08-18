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
	explicit vector (allocator_type const &alloc = allocator_type()): _head(pointer()), _tail(_head), _end_of_storage(_head)
	{
		return;
	}

};

}

#endif
