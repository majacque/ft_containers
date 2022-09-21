#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "iterator.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"
#include <memory>
#include <cstring>
#include <exception>

namespace ft
{

template < class T, class Alloc = std::allocator<T> >
class vector
{
public:
	typedef T													value_type;
	typedef Alloc												allocator_type;
	typedef typename allocator_type::reference					reference;
	typedef typename allocator_type::const_reference			const_reference;
	typedef typename allocator_type::pointer					pointer;
	typedef typename allocator_type::const_pointer				const_pointer;
	typedef __ft::__normal_iterator<pointer>					iterator;
	typedef __ft::__normal_iterator<const_pointer>				const_iterator;
	typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;
	typedef typename iterator_traits<iterator>::difference_type	difference_type;
	typedef size_t												size_type;

private:
	pointer	_head;
	pointer	_tail;
	pointer	_end_of_storage;

public:
	/**************************************************************************/
	/*                               CONSTRUCTOR                              */
	/**************************************************************************/

	/**
	 * @brief Constructs an empty vector, with no elements.
	 * 
	 * @param alloc Allocator object.
	 */
	explicit vector( allocator_type const & = allocator_type() ):
										_head(pointer()), _tail(_head), _end_of_storage(_head)
	{
		return;
	}

	/**
	 * @brief Constructs a vector with @a n elements. Each element is a copy of @a val.
	 * 
	 * @param n Initial container size (i.e., the number of elements in the container at construction).
	 * @param val Value to fill the container with. Each of the n elements in the container will be initialized to a copy of this value.
	 * @param alloc Allocator object.
	 */
	explicit vector( size_type n, value_type const &val = value_type(), allocator_type const & = allocator_type() ):
																					_head(), _tail(), _end_of_storage()
	{
		if (n > this->max_size())
			throw std::length_error("cannot create ft::vector larger than max_size()");

		__insert_fill(this->begin(), n, val);
		return;
	}

	/**
	 * @brief Constructs a container with as many elements as the range [first,last),
	 * with each element constructed from its corresponding element in that range, in the same order.
	 * 
	 * @par The range used is [first,last), which includes all the elements between @a first and @a last,
	 * including the element pointed by @a first but not the element pointed by @a last.
	 * 
	 * @param first An input iterator to the initial position in a range.
	 * @param last An input iterator to the final position in a range.
	 */
	template <class InputIterator>
	vector( InputIterator first, InputIterator last, allocator_type const & = allocator_type() ):
																_head(), _tail(), _end_of_storage()
	{
		__insert_dispatch(iterator(_head), first, last, is_integral<InputIterator>());
		return;
	}

	/**
	 * @brief Constructs a container with a copy of each of the elements in @a rhs, in the same order.
	 * 
	 * @param rhs Another vector object of the same type (with the same class template arguments T and Alloc),
	 * whose contents are either copied or acquired.
	 */
	vector( vector const &rhs ): _head(), _tail(), _end_of_storage()
	{
		__insert_dispatch(iterator(_head), rhs.begin(), rhs.end(), is_integral<iterator>());
		return;
	}

	/**************************************************************************/
	/*                               DESTRUCTOR                               */
	/**************************************************************************/

	/**
	 * @brief Destroys the container object.
	 */
	~vector( void )
	{
		if (_head)
		{
			this->clear();
			allocator_type().deallocate(_head, this->capacity());
		}
		return;
	}

	/**************************************************************************/
	/*                            MEMBER FUNCTIONS                            */
	/**************************************************************************/

	vector&	operator=( vector const &rhs )
	{
		assign(rhs.begin(), rhs.end());
		return *this;
	}

	// ITERATOR

	iterator	begin( void )
	{
		return iterator(_head);
	}

	const_iterator	begin( void ) const
	{
		return const_iterator(_head);
	}

	iterator	end( void )
	{
		return iterator(_tail);
	}

	const_iterator	end( void ) const
	{
		return const_iterator(_tail);
	}

	reverse_iterator	rbegin( void )
	{
		return reverse_iterator(this->end());
	}

	const_reverse_iterator	rbegin( void ) const
	{
		return const_reverse_iterator(this->end());
	}

	reverse_iterator	rend( void )
	{
		return reverse_iterator(this->begin());
	}

	const_reverse_iterator	rend( void ) const
	{
		return const_reverse_iterator(this->begin());
	}

	// CAPACITY

	size_type	size( void ) const
	{
		return _tail - _head;
	}

	size_type	max_size( void ) const
	{
		return allocator_type().max_size();
	}

	void	resize( size_type n, value_type const val = value_type() )
	{
		if (n < this->size())
			this->erase(iterator(_head + n), this->end());
		else if (n > this->size())
			__insert_fill(this->end(), n - this->size(), val);
	}

	size_type	capacity( void ) const
	{
		return _end_of_storage - _head;
	}

	bool	empty( void ) const
	{
		return _head == _tail;
	}

	void	reserve( size_type n )
	{
		allocator_type	alloc;

		if (n <= this->capacity())
			return ;
		else if (n > alloc.max_size())
			throw std::length_error("vector::reserve");

		pointer			newHead = alloc.allocate(n, _head);
		pointer			newTail = newHead + this->size();

		__value_move(newHead, _head, _tail, is_trivially_copyable<value_type>());
		alloc.deallocate(_head, this->capacity());
		_head = newHead;
		_tail = newTail;
		_end_of_storage = _head + n;
	}

	// ELEMENT ACCESS

	reference	operator[]( size_type n )
	{
		return _head[n];
	}

	const_reference	operator[]( size_type n ) const
	{
		return _head[n];
	}

	reference	at( size_type n )
	{
		if (n > this->size())
			throw std::out_of_range("vector::at");
		return _head[n];
	}

	const_reference	at( size_type n ) const
	{
		if (n > this->size())
			throw std::out_of_range("vector::at");
		return _head[n];
	}

	reference	front( void )
	{
		return *_head;
	}

	const_reference	front( void ) const
	{
		return *_head;
	}

	reference	back( void )
	{
		return *(_tail - 1);
	}

	const_reference	back( void ) const
	{
		return *(_tail - 1);
	}

	// MODIFIERS

	template <class InputIterator>
	void	assign( InputIterator first, InputIterator last )
	{
		this->clear();
		__insert_dispatch(this->begin(), first, last, is_integral<InputIterator>());
		return;
	}

	void	assign( size_type n, value_type const &val )
	{
		this->clear();
		__insert_fill(this->begin(), n, val);
		return;
	}

	void	push_back( value_type const &val )
	{
		__insert_fill(this->end(), 1, val);
		return;
	}

	void	pop_back( void )
	{
		if (_tail && _tail != _head)
		{
			--_tail;
			allocator_type().destroy(_tail);
		}
		return;
	}

	iterator	insert( iterator position, value_type const &val )
	{
		size_type const	offset = position - this->begin();
		__insert_fill(position, 1, val);
		return this->begin() + offset;
	}

	void	insert( iterator position, size_type n, value_type const &val )
	{
		__insert_fill(position, n, val);
		return;
	}

	template <class InputIterator>
	void	insert( iterator position, InputIterator first, InputIterator last )
	{
		this->__insert_dispatch(position, first, last, is_integral<InputIterator>());
		return;
	}

	iterator	erase( iterator pos )
	{
		return this->erase(pos, pos + 1);
	}

	iterator	erase( iterator first, iterator last )
	{
		allocator_type	alloc;

		for (iterator it = first ; it != last ; ++it)
			alloc.destroy(it.base());
		__value_move(first.base(), last.base(), _tail, is_trivially_copyable<value_type>());
		_tail -= last - first;
		return first;
	}

	void	swap( vector &x )
	{
		pointer	tmp_head = x._head;
		pointer	tmp_tail = x._tail;
		pointer	tmp_end_of_storage = x._end_of_storage;

		x._head = _head;
		x._tail = _tail;
		x._end_of_storage = _end_of_storage;

		_head = tmp_head;
		_tail = tmp_tail;
		_end_of_storage = tmp_end_of_storage;
		return;
	}

	void	clear( void )
	{
		if (_head == _tail)
			return;

		allocator_type	alloc;

		--_tail;
		for (; _tail != _head; --_tail)
			alloc.destroy(_tail);
		alloc.destroy(_tail);
		return;
	}

	// ALLOCATOR

	allocator_type	get_allocator( void ) const
	{
		return allocator_type();
	}

	/**************************************************************************/
	/*                            MEMBER OPERATORS                            */
	/**************************************************************************/

	/**************************************************************************/
	/*                           INTERNAL FUNCTIONS                           */
	/**************************************************************************/

private:

	inline void __value_move( pointer dst, pointer first, pointer last, true_type)
	{
		memmove(dst, first, (last - first) * sizeof(value_type));
		return;
	}

	inline void __value_move( pointer dst, pointer first, pointer last, false_type)
	{
		allocator_type	alloc;

		if (dst < first)
		{
			for ( ; first != last ; ++first, ++dst)
			{
				alloc.construct(dst, *first);
				alloc.destroy(first);
			}
		}
		else if (dst > first)
		{
			dst += (last - first - 1);
			--first;
			--last;
			for (; first != last; --last, --dst)
			{
				alloc.construct(dst, *last);
				alloc.destroy(last);
			}
		}
		return;
	}

	void __insert_fill( iterator position, size_type n, value_type const &val )
	{
		if (!n)
			return;

		size_type const	offset = position - this->begin();
		allocator_type	alloc;

		if (this->size() + n <= this->capacity())
		{
			__value_move(_head + offset + n, _head + offset, _tail, is_trivially_copyable<value_type>());
			_tail += n;
		}
		else
		{
			size_t	new_capacity = this->size() * 2;
			if (new_capacity < this->size() + n)
				new_capacity = this->size() + n;

			pointer	new_head = alloc.allocate(new_capacity/* , _head */);
			pointer	new_tail = new_head + this->size() + n;
			if (_head)
			{
				__value_move(new_head, _head, _head + offset, is_trivially_copyable<value_type>());
				__value_move(new_head + offset + n, _head + offset, _tail, is_trivially_copyable<value_type>());
				alloc.deallocate(_head, this->capacity());
			}
			_head = new_head;
			_tail = new_tail;
			_end_of_storage = _head + new_capacity;
		}

		pointer end = _head + offset + n;
		for (pointer begin = _head + offset; begin != end; ++begin)
			alloc.construct(begin, val);

		return;
	}

	template <class InputIterator>
	void	__insert_range( iterator position, InputIterator first, InputIterator last )
	{
		allocator_type	alloc;
		size_t const	end_size = this->end() - position;
		pointer const	end_save = alloc.allocate(end_size, _head);

		__value_move(end_save, position.base(), _tail, is_trivially_copyable<value_type>()); // déplace la fin dans une sauvegarde
		_tail = position.base();

		for (; this->size() < this->capacity() && first != last; ++first) // copie ce qui passe dans l'espace déjà allouer
		{
			alloc.construct(_tail, *first);
			++_tail;
		}

		size_t	new_capacity;
		pointer	new_head;
		pointer	new_tail;
		size_t	i = 0;
		while (first != last) // alloue le double de la size et copie jusqu'à ce qu'il n'y ai plus rien à copier
		{
			new_capacity = this->size() * 2;
			if (new_capacity == 0)
				++new_capacity;
			new_head = alloc.allocate(new_capacity, _head);
			new_tail = new_head + this->size();
			__value_move(new_head, _head, _tail, is_trivially_copyable<value_type>());
			alloc.deallocate(_head, this->capacity());
			_head = new_head;
			_tail = new_tail;
			_end_of_storage = _head + new_capacity;
			for(; this->size() < this->capacity() && first != last; ++first)
			{
				alloc.construct(_tail, *first);
				++_tail;
			}
			++i;
		}

		// met ce qu'il y a dans _head + dans end_save --> un espace pile de la bonne taille
		if (i > 1 || (this->size() + end_size) > this->capacity())
		{
			new_capacity = this->size() + end_size;
			new_head = alloc.allocate(new_capacity, _head);
			__value_move(new_head, _head, _tail, is_trivially_copyable<value_type>());
			__value_move(new_head + this->size(), end_save, end_save + end_size, is_trivially_copyable<value_type>());
			alloc.deallocate(_head, this->capacity());
			_head = new_head;
			_tail = _head + new_capacity;
			_end_of_storage = _tail;
		}
		else
		{
			__value_move(_head + this->size(), end_save, end_save + end_size, is_trivially_copyable<value_type>());
			_tail += end_size;
		}

		alloc.deallocate(end_save, end_size);

		return;
	}

	template<typename U>
	inline void	__insert_dispatch(iterator position, U param1, U param2, true_type const)
	{
		this->__insert_fill(position, param1, param2);
		return;
	}

	template<typename U>
	inline void	__insert_dispatch(iterator position, U param1, U param2, false_type const)
	{
		this->__insert_range(position, param1, param2);
		return;
	}

};

template <class T, class Alloc>
bool	operator==( vector<T,Alloc> const &lhs, vector<T,Alloc> const &rhs )
{
	if (lhs.size() != rhs.size())
		return false;

	size_t	size = lhs.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (lhs[i] != rhs[i])
			return false;
	}

	return true;
}

template <class T, class Alloc>
bool	operator!=( vector<T,Alloc> const &lhs, vector<T,Alloc> const &rhs )
{
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool	operator<( vector<T,Alloc> const &lhs, vector<T,Alloc> const &rhs )
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Alloc>
bool	operator<=( vector<T,Alloc> const &lhs, vector<T,Alloc> const &rhs )
{
	return !(rhs<lhs);
}

template <class T, class Alloc>
bool	operator>( vector<T,Alloc> const &lhs, vector<T,Alloc> const &rhs )
{
	return rhs<lhs;
}

template <class T, class Alloc>
bool	operator>=( vector<T,Alloc> const &lhs, vector<T,Alloc> const &rhs )
{
	return !(lhs<rhs);
}

template <class T, class Alloc>
void	swap( vector<T, Alloc> &x, vector<T, Alloc> &y )
{
	x.swap(y);
	return;
}

}

#endif
