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

	/**
	 * @brief Copies all the elements from @a rhs into the container.
	 * 
	 * @par The container preserves its current allocator, which is used to allocate storage in case of reallocation.
	 * Any elements held in the container before the call are either assigned to or destroyed.
	 * 
	 * @param rhs A vector object of the same type (i.e., with the same template parameters, T and Alloc).
	 * @return A reference to the instance.
	 */
	vector&	operator=( vector const &rhs )
	{
		assign(rhs.begin(), rhs.end());
		return *this;
	}

	// ITERATOR

	/**
	 * @brief Returns an iterator pointing to the first element in the vector.
	 * If the container is empty, the returned iterator value shall not be dereferenced.
	 * 
	 * @return An iterator to the beginning of the sequence container.
	 */
	iterator	begin( void )
	{
		return iterator(_head);
	}

	/**
	 * @brief Returns a const iterator pointing to the first element in the vector.
	 * If the container is empty, the returned const iterator value shall not be dereferenced.
	 * 
	 * @return A const iterator to the beginning of the sequence container.
	 */
	const_iterator	begin( void ) const
	{
		return const_iterator(_head);
	}

	/**
	 * @brief Returns an iterator referring to the @a past-the-end element in the vector container.
	 * 
	 * @par The @a past-the-end element is the theoretical element that would follow the last element in the vector.
	 * It does not point to any element, and thus shall not be dereferenced.
	 * 
	 * @return An iterator to the element past the end of the sequence.
	 */
	iterator	end( void )
	{
		return iterator(_tail);
	}

	/**
	 * @brief Returns a const iterator referring to the @a past-the-end element in the vector container.
	 * 
	 * @par The @a past-the-end element is the theoretical element that would follow the last element in the vector.
	 * It does not point to any element, and thus shall not be dereferenced.
	 * 
	 * @return A const iterator to the element past the end of the sequence.
	 */
	const_iterator	end( void ) const
	{
		return const_iterator(_tail);
	}

	/**
	 * @brief Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
	 * Points to the element right before the one that would be pointed to by member @a end.
	 * 
	 * @return A reverse iterator to the reverse beginning of the sequence container.
	 */
	reverse_iterator	rbegin( void )
	{
		return reverse_iterator(this->end());
	}


	/**
	 * @brief Returns a const reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
	 * Points to the element right before the one that would be pointed to by member @a end.
	 * 
	 * @return A const reverse iterator to the reverse beginning of the sequence container.
	 */
	const_reverse_iterator	rbegin( void ) const
	{
		return const_reverse_iterator(this->end());
	}

	/**
	 * @brief Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector
	 * (which is considered its reverse end).
	 * 
	 * @return A reverse iterator to the reverse end of the sequence container.
	 */
	reverse_iterator	rend( void )
	{
		return reverse_iterator(this->begin());
	}

	/**
	 * @brief Returns a const reverse iterator pointing to the theoretical element preceding the first element in the vector
	 * (which is considered its reverse end).
	 * 
	 * @return A const reverse iterator to the reverse end of the sequence container.
	 */
	const_reverse_iterator	rend( void ) const
	{
		return const_reverse_iterator(this->begin());
	}

	// CAPACITY

	/**
	 * @brief Returns the number of elements in the vector.
	 * This is the number of actual objects held in the vector, which is not necessarily equal to its storage capacity.
	 */
	size_type	size( void ) const
	{
		return _tail - _head;
	}

	/**
	 * @brief Returns the maximum number of elements that the vector can hold.
	 * 
	 * @par This is the maximum potential size the container can reach due to known system or library implementation limitations,
	 * but the container is by no means guaranteed to be able to reach that size:
	 * it can still fail to allocate storage at any point before that size is reached.
	 */
	size_type	max_size( void ) const
	{
		return allocator_type().max_size();
	}

	/**
	 * @brief Resizes the container so that it contains @a n elements.
	 * 
	 * @par If @a n is smaller than the current container size, the content is reduced to its first @a n elements, removing those beyond (and destroying them).
	 * If @a n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of @a n.
	 * If @a val is specified, the new elements are initialized as copies of @a val, otherwise, they are value-initialized.
	 * If @a n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
	 * 
	 * @param n New container size, expressed in number of elements.
	 * @param val Object whose content is copied to the added elements in case that n is greater than the current container size.
	 * If not specified, the default constructor is used instead.
	 */
	void	resize( size_type n, value_type const val = value_type() )
	{
		if (n < this->size())
			this->erase(iterator(_head + n), this->end());
		else if (n > this->size())
			__insert_fill(this->end(), n - this->size(), val);
	}

	/**
	 * @brief Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
	 * This @a capacity is not necessarily equal to the vector size.
	 * It can be equal or greater, with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.
	 */
	size_type	capacity( void ) const
	{
		return _end_of_storage - _head;
	}

	/**
	 * @brief Returns whether the vector is empty (i.e. whether its size is 0).
	 * 
	 * @return true if the container size is 0, false otherwise.
	 */
	bool	empty( void ) const
	{
		return _head == _tail;
	}

	/**
	 * @brief Requests that the vector capacity be at least enough to contain @a n elements.
	 * 
	 * @par If n is greater than the current vector capacity,
	 * the function causes the container to reallocate its storage increasing its capacity to n (or greater).
	 * In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.
	 * 
	 * @param n Minimum capacity for the vector.
	 */
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

	/**
	 * @brief Returns a reference to the element at position @a n in the vector container.
	 * 
	 * @param n Position of an element in the container.
	 */
	reference	operator[]( size_type n )
	{
		return _head[n];
	}

	/**
	 * @brief Returns a const reference to the element at position @a n in the vector container.
	 * 
	 * @param n Position of an element in the container.
	 */
	const_reference	operator[]( size_type n ) const
	{
		return _head[n];
	}

	/**
	 * @brief Returns a reference to the element at position @a n in the vector.
	 * The function automatically checks whether @a n is within the bounds of valid elements in the vector,
	 * throwing an out_of_range exception if it is not (i.e., if @a n is greater than, or equal to, its size).
	 * 
	 * @param n Position of an element in the container.
	 */
	reference	at( size_type n )
	{
		if (n > this->size())
			throw std::out_of_range("vector::at");
		return _head[n];
	}

	/**
	 * @brief Returns a const reference to the element at position @a n in the vector.
	 * The function automatically checks whether @a n is within the bounds of valid elements in the vector,
	 * throwing an out_of_range exception if it is not (i.e., if @a n is greater than, or equal to, its size).
	 * 
	 * @param n Position of an element in the container.
	 */
	const_reference	at( size_type n ) const
	{
		if (n > this->size())
			throw std::out_of_range("vector::at");
		return _head[n];
	}

	/**
	 * @brief Returns a reference to the first element in the vector.
	 */
	reference	front( void )
	{
		return *_head;
	}

	/**
	 * @brief Returns a const reference to the first element in the vector.
	 */
	const_reference	front( void ) const
	{
		return *_head;
	}

	/**
	 * @brief Returns a reference to the last element in the vector.
	 */
	reference	back( void )
	{
		return *(_tail - 1);
	}

	/**
	 * @brief Returns a const reference to the last element in the vector.
	 */
	const_reference	back( void ) const
	{
		return *(_tail - 1);
	}

	// MODIFIERS

	/**
	 * @brief Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
	 * The new contents are elements constructed from each of the elements in the range between @a first and @a last, in the same order.
	 * The range used is [first,last), which includes all the elements between @a first and @a last,
	 * including the element pointed by first but not the element pointed by @a last.
	 * 
	 * @par Any elements held in the container before the call are destroyed and replaced by newly constructed elements
	 * (no assignments of elements take place). This causes an automatic reallocation of the allocated storage space if
	 * -and only if- the new vector size surpasses the current vector capacity.
	 * 
	 * @param first An input iterator to the initial position in a sequence.
	 * @param last An input iterator to the final position in a sequence.
	 */
	template <class InputIterator>
	void	assign( InputIterator first, InputIterator last )
	{
		this->clear();
		__insert_dispatch(this->begin(), first, last, is_integral<InputIterator>());
		return;
	}

	/**
	 * @brief Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
	 * The new contents are @a n elements, each initialized to a copy of @a val.
	 * 
	 * @param n New size for the container.
	 * @param val Value to fill the container with. Each of the @a n elements in the container will be initialized to a copy of this value.
	 */
	void	assign( size_type n, value_type const &val )
	{
		this->clear();
		__insert_fill(this->begin(), n, val);
		return;
	}

	/**
	 * @brief Adds a new element at the end of the vector, after its current last element. The content of @a val is copied (or moved) to the new element.
	 * 
	 * @param val Value to be copied (or moved) to the new element.
	 */
	void	push_back( value_type const &val )
	{
		__insert_fill(this->end(), 1, val);
		return;
	}

	/**
	 * @brief Removes the last element in the vector, effectively reducing the container size by one.
	 */
	void	pop_back( void )
	{
		if (_tail && _tail != _head)
		{
			--_tail;
			allocator_type().destroy(_tail);
		}
		return;
	}

	/**
	 * @brief The vector is extended by inserting new elements before the element at the specified position,
	 * effectively increasing the container size by the number of elements inserted.
	 * This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
	 * 
	 * @param position Position in the vector where the new elements are inserted.
	 * @param val Value to be copied (or moved) to the inserted elements.
	 * @return An iterator that points to the first of the newly inserted elements.
	 */
	iterator	insert( iterator position, value_type const &val )
	{
		size_type const	offset = position - this->begin();
		__insert_fill(position, 1, val);
		return this->begin() + offset;
	}

	/**
	 * @brief The vector is extended by inserting new elements before the element at the specified position,
	 * effectively increasing the container size by the number of elements inserted.
	 * This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
	 * 
	 * @param position Position in the vector where the new elements are inserted.
	 * @param n Number of elements to insert. Each element is initialized to a copy of val.
	 * @param val Value to be copied (or moved) to the inserted elements.
	 */
	void	insert( iterator position, size_type n, value_type const &val )
	{
		__insert_fill(position, n, val);
		return;
	}

	/**
	 * @brief The vector is extended by inserting new elements before the element at the specified position,
	 * effectively increasing the container size by the number of elements inserted.
	 * This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
	 * 
	 * @par @a first and @a last specifies a range of elements.
	 * Copies of the elements in the range [first,last) are inserted at @a position (in the same order).
	 * Notice that the range includes all the elements between @a first and @a last,
	 * including the element pointed by @a first but not the one pointed by @a last.
	 * 
	 * @param position Position in the vector where the new elements are inserted.
	 * @param first An input iterator to the initial position in a sequence.
	 * @param last An input iterator to the final position in a sequence.
	 */
	template <class InputIterator>
	void	insert( iterator position, InputIterator first, InputIterator last )
	{
		this->__insert_dispatch(position, first, last, is_integral<InputIterator>());
		return;
	}

	/**
	 * @brief Removes from the vector a single element which is destroyed. This effectively reduces the container size.
	 * 
	 * @param pos An iterator pointing to a single element to be removed from the vector.
	 * @return An iterator pointing to the new location of the element that followed the element erased by the function call.
	 * This is the container @a end if the operation erased the last element in the sequence.
	 */
	iterator	erase( iterator pos )
	{
		return this->erase(pos, pos + 1);
	}

	/**
	 * @brief Removes from the vector a range of elements ([first,last)).
	 * This effectively reduces the container size by the number of elements removed, which are destroyed.
	 * 
	 * @par Iterators specifying a range within the vector to be removed: [first,last).
	 * i.e., the range includes all the elements between @a first and @a last, including the element pointed by @a first but not the one pointed by @a last.
	 * 
	 * @param first An input iterator to the initial position in a sequence.
	 * @param last An input iterator to the final position in a sequence.
	 * @return An iterator pointing to the new location of the element that followed the last element erased by the function call.
	 * This is the container @a end if the operation erased the last element in the sequence.
	 */
	iterator	erase( iterator first, iterator last )
	{
		allocator_type	alloc;

		for (iterator it = first ; it != last ; ++it)
			alloc.destroy(it.base());
		__value_move(first.base(), last.base(), _tail, is_trivially_copyable<value_type>());
		_tail -= last - first;
		return first;
	}

	/**
	 * @brief Exchanges the content of the container by the content of @a x, which is another vector object of the same type. Sizes may differ.
	 * All iterators, references and pointers remain valid for the swapped objects.
	 * 
	 * @param x Another vector container of the same type (i.e., instantiated with the same template parameters, T and Alloc)
	 * whose content is swapped with that of this container.
	 */
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

	/**
	 * @brief Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
	 * A reallocation is not guaranteed to happen, and the vector capacity is not guaranteed to change due to calling this function.
	 */
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

	/**
	 * @brief Returns a copy of the allocator object associated with the vector.
	 */
	allocator_type	get_allocator( void ) const
	{
		return allocator_type();
	}

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

/**
 * @brief Performs the appropriate comparison operation between the vector containers @a lhs and @a rhs.
 * 
 * @par The equality comparison (operator==) is performed by first comparing sizes, and if they match,
 * the elements are compared sequentially using operator==, stopping at the first mismatch (as if using algorithm equal).
 * The less-than comparison (operator<) behaves as if using algorithm lexicographical_compare,
 * which compares the elements sequentially using operator< in a reciprocal manner (i.e., checking both a<b and b<a) and stopping at the first occurrence.
 * The other operations also use the operators == and < internally to compare the elements.
 * 
 * @param lhs A vector container having the same template parameters than @a rhs.
 * @param rhs A vector container having the same template parameters than @a lhs.
 * @return true if the condition holds, and false otherwise.
 */

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

/**
 * @brief The contents of container @a x are exchanged with those of @a y.
 * Both container objects must be of the same type (same template parameters), although sizes may differ.
 * 
 * @param x A vector containers of the same type as @a y.
 * @param y A vector containers of the same type as @a x.
 */
template <class T, class Alloc>
void	swap( vector<T, Alloc> &x, vector<T, Alloc> &y )
{
	x.swap(y);
	return;
}

}

#endif
