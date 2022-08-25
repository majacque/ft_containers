#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "iterator.hpp"
#include "type_traits.hpp"
#include <memory>
#include <cstring>
#include <exception>

namespace ft
{

template < class T, class Alloc = std::allocator<T> >
class vector
{
private:
	template < typename Tp >
	class vector_iterator
	{
	public:
		typedef typename iterator_traits<Tp>::difference_type	difference_type;
		typedef typename iterator_traits<Tp>::value_type		value_type;
		typedef typename iterator_traits<Tp>::pointer			pointer;
		typedef typename iterator_traits<Tp>::reference			reference;
		typedef typename iterator_traits<Tp>::iterator_category	iterator_category;

	private:
		Tp	_current;

	public:

		/**************************************************************************/
		/*                               CONSTRUCTOR                              */
		/**************************************************************************/

		vector_iterator( void ): _current()
		{
			return;
		}

		explicit vector_iterator( Tp const &current ): _current(current)
		{
			return;
		}

		vector_iterator( vector_iterator const &rhs ): _current(rhs._current)
		{
			return;
		}

		/**************************************************************************/
		/*                               DESTRUCTOR                               */
		/**************************************************************************/

		~vector_iterator( void )
		{
			return;
		}

		/**************************************************************************/
		/*                            MEMBER FUNCTIONS                            */
		/**************************************************************************/

		Tp const&	base( void ) const
		{
			return _current;
		}

		/**************************************************************************/
		/*                            MEMBER OPERATORS                            */
		/**************************************************************************/

		vector_iterator&	operator=( vector_iterator const& rhs)
		{
			_current = rhs.base();
			return *this;
		}

		reference	operator*( void ) const
		{
			return *_current;
		}

		pointer	operator->( void ) const
		{
			return &(*_current);
		}

		reference	operator[]( difference_type n ) const
		{
			return _current[n];
		}

		vector_iterator	operator+( difference_type n ) const
		{
			return vector_iterator(_current + n);
		}

		vector_iterator	operator-( difference_type n ) const
		{
			return vector_iterator(_current - n);
		}

		vector_iterator&	operator++( void )
		{
			++_current;
			return *this;
		}

		vector_iterator&	operator++( int )
		{
			vector_iterator	tmp(_current);
			++_current;
			return tmp;
		}

		vector_iterator&	operator--( void )
		{
			--_current;
			return *this;
		}

		vector_iterator&	operator--( int )
		{
			vector_iterator	tmp(_current);
			--_current;
			return tmp;
		}

		vector_iterator&	operator+=( difference_type n )
		{
			_current += n;
			return *this;
		}

		vector_iterator&	operator-=( difference_type n )
		{
			_current -= n;
			return *this;
		}

		difference_type	operator-( vector_iterator const & rhs )
		{
			return _current - rhs._current;
		}

	};

public:
	typedef T													value_type;
	typedef Alloc												allocator_type;
	typedef typename allocator_type::reference					reference;
	typedef typename allocator_type::const_reference			const_reference;
	typedef typename allocator_type::pointer					pointer;
	typedef typename allocator_type::const_pointer				const_pointer;
	typedef vector_iterator<pointer>							iterator;
	typedef vector_iterator<const_pointer>						const_iterator;
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
	 * @brief Constructs a vector with n elements. Each element is a copy of val.
	 * 
	 * @param n Initial container size (i.e., the number of elements in the container at construction).
	 * @param val Value to fill the container with. Each of the n elements in the container will be initialized to a copy of this value.
	 * @param alloc Allocator object.
	 */
	explicit vector( size_type n, value_type const &val = value_type(), allocator_type const & = allocator_type() ):
																					_head(), _tail(), _end_of_storage()
	{
		if (n > this->max_size())
			throw std::length_error("cannot create std::vector larger than max_size()");

		__insert_fill(this->begin(), n, val);
		return;
	}

	/**************************************************************************/
	/*                               DESTRUCTOR                               */
	/**************************************************************************/

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

	// ITERATOR

	iterator	begin( void )
	{
		return iterator(_head);
	}

	const_iterator	begin( void ) const
	{
		return iterator(_head);
	}

	iterator	end( void )
	{
		return iterator(_tail);
	}

	const_iterator	end( void ) const
	{
		return iterator(_tail);
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

	size_type	capacity( void ) const
	{
		return _end_of_storage - _head;
	}

	// MODIFIERS

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

	void	clear( void )
	{
		allocator_type	alloc;

		--_tail;
		for (; _tail != _head; --_tail)
			alloc.destroy(_tail);
		alloc.destroy(_tail);
		return;
	}

	// ELEMENT ACCESS

	reference	operator[]( size_type n )
	{
		return _head[n];
	}

	/**************************************************************************/
	/*                            MEMBER OPERATORS                            */
	/**************************************************************************/

	/**************************************************************************/
	/*                           INTERNAL FUNCTIONS                           */
	/**************************************************************************/

private:

	void __value_move( pointer dst, pointer first, pointer last, true_type)
	{
		memmove(dst, first, (last - first) * sizeof(value_type));
		return;
	}

	void __value_move( pointer dst, pointer first, pointer last, false_type)
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

		size_type const	offset = this->end() - position;
		allocator_type	alloc;

		if (this->size() + n <= this->capacity())
			__value_move(_head + offset + n, _head + offset, _tail, is_trivially_copyable<value_type>());
		else
		{
			size_t	new_capacity = this->size() * 2;
			if (new_capacity < this->size() + n)
				new_capacity = this->size() + n;

			pointer	new_head = alloc.allocate(new_capacity, _head);
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

/* 
 * insert range input iterator
 * {
 * 	récupérer pos -> end dans un tableau à part [save_end]
 * 	copier ce qui passe dans l'espace déjà allouer
 * 	s'il est possible de rajouter save_end return; / sinon:
 * 	loop: tant que first != last
 * 	  alloc size x2
 * 	  copie s'il y a qqch à copier
 * 	une fois que tout est copier:
 * 	  allouer size() + size de save_end
 * 	  copier tout
 * 	  copier save_end
 * }
 * 
 * faire en sorte qu'il soit obligatoire de passer des input iterator
 * 	faire une fonction qui prend un booléen qui vérifie is_integral du type de first & last
 * 	si bool == true -> utiliser l'autre insert
 * 	si bool == false -> utiliser celui ci en lui passant iterator_category de first & last
 * 	insert range ne prend que input_iterator_tag en category
 */

};

template <class T>
bool	operator==( typename vector<T>::iterator const &lhs, typename vector<T>::iterator const &rhs )
{
	return lhs.base() == rhs.base();
}

template <class T, class U>
bool	operator==( typename vector<T>::iterator const &lhs, typename vector<U>::iterator const &rhs )
{
	return lhs.base() == rhs.base();
}

template <class T>
bool	operator!=( typename vector<T>::iterator const &lhs, typename vector<T>::iterator const &rhs )
{
	return lhs.base() != rhs.base();
}

template <class T, class U>
bool	operator!=( typename vector<T>::iterator const &lhs, typename vector<U>::iterator const &rhs )
{
	return lhs.base() != rhs.base();
}

template <class T>
bool	operator<( typename vector<T>::iterator const &lhs, typename vector<T>::iterator const &rhs )
{
	return lhs.base() < rhs.base();
}

template <class T, class U>
bool	operator<( typename vector<T>::iterator const &lhs, typename vector<U>::iterator const &rhs )
{
	return lhs.base() < rhs.base();
}

template <class T>
bool	operator<=( typename vector<T>::iterator const &lhs, typename vector<T>::iterator const &rhs )
{
	return lhs.base() <= rhs.base();
}

template <class T, class U>
bool	operator<=( typename vector<T>::iterator const &lhs, typename vector<U>::iterator const &rhs )
{
	return lhs.base() <= rhs.base();
}

template <class T>
bool	operator>( typename vector<T>::iterator const &lhs, typename vector<T>::iterator const &rhs )
{
	return lhs.base() > rhs.base();
}

template <class T, class U>
bool	operator>( typename vector<T>::iterator const &lhs, typename vector<U>::iterator const &rhs )
{
	return lhs.base() > rhs.base();
}

template <class T>
bool	operator>=( typename vector<T>::iterator const &lhs, typename vector<T>::iterator const &rhs )
{
	return lhs.base() >= rhs.base();
}

template <class T, class U>
bool	operator>=( typename vector<T>::iterator const &lhs, typename vector<U>::iterator const &rhs )
{
	return lhs.base() >= rhs.base();
}

template <class T>
typename vector<T>::iterator	operator+( typename vector<T>::iterator::difference_type n, typename vector<T>::iterator const &it )
{
	return it + n;
}

// template <class T>
// typename vector<T>::iterator::difference_type
// 	operator-( typename vector<T>::iterator const &lhs, typename vector<T>::iterator const &rhs )
// {
// 	return lhs.base() - rhs.base();
// }

// template <class T, class U>
// typename vector<U>::iterator::difference_type
// 	operator-( typename vector<T>::iterator const &lhs, typename vector<U>::iterator const &rhs )
// {
// 	return lhs.base() - rhs.base();
// }

}

#endif
