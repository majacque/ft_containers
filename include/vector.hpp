#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "iterator.hpp"
#include <memory>
#include <iostream>

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
	typedef typename ft::vector_iterator<pointer>				iterator;
	typedef typename ft::vector_iterator<const_pointer>			const_iterator;
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
		// _insert_fill()
		return;
	}

	/**************************************************************************/
	/*                               DESTRUCTOR                               */
	/**************************************************************************/

	// TODO begin()
	// TODO end()
	// TODO size()
	// TODO capacity()
	// TODO operator[]

	/**************************************************************************/
	/*                            MEMBER FUNCTIONS                            */
	/**************************************************************************/

	iterator insert (iterator position, value_type const &val)
	{
		size_type const	offset = position - this->begin();
		_insert_fill(position, 1, val);
		return this->begin() + offset;
	}

	void insert (iterator position, size_type n, value_type const &val)
	{
		_insert_fill(position, n, val);
		return;
	}

	/**************************************************************************/
	/*                            MEMBER OPERATORS                            */
	/**************************************************************************/

private:
	// TODO _insert_fill()
	void _insert_fill (iterator position, size_type n, value_type const &val)
	{
		if (!n)
			return;

		size_type const	offset = this->end() - position;

		if (this->size() + n <= this->capacity())
		{
			// déplace [offset, end()] -> offset + n
		}
		else
		{
			allocator_type	alloc;
			size_t	new_capacity = this->size() * 2;
			if (new_capacity < this->size() + n)
				new_capacity = this->size() + n;

			pointer	new_head = alloc.allocate(new_capacity, _head);
			pointer	new_tail = new_head + this->size() + n;
			if (_head)
			{
				// copie _head -> new_head jusqu'à offset - 1
				// copie [_head + offset, end()] -> new_head + offset + n
				alloc.deallocate(_head, this->capacity());
			}
			_head = new_head;
			_tail = new_tail;
			_end_of_storage = _head + new_capacity;
		}

		// _head + offset -> _head + offset + n - 1 = val

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

	template <class Tp>
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

		vector_iterator( vector_iterator const &rhs ): _current(rhs._current);
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

	};

	template <class Tp>
	bool	operator==( vector_iterator<Tp> const &lhs, vector_iterator<Tp> const &rhs )
	{
		return lsh.base() == rhs.base();
	}

	template <class Tp>
	bool	operator!=( vector_iterator<Tp> const &lhs, vector_iterator<Tp> const &rhs )
	{
		return lsh.base() != rhs.base();
	}

	template <class Tp>
	bool	operator<( vector_iterator<Tp> const &lhs, vector_iterator<Tp> const &rhs )
	{
		return lsh.base() < rhs.base();
	}

	template <class Tp>
	bool	operator<=( vector_iterator<Tp> const &lhs, vector_iterator<Tp> const &rhs )
	{
		return lsh.base() <= rhs.base();
	}

	template <class Tp>
	bool	operator>( vector_iterator<Tp> const &lhs, vector_iterator<Tp> const &rhs )
	{
		return lsh.base() > rhs.base();
	}

	template <class Tp>
	bool	operator>=( vector_iterator<Tp> const &lhs, vector_iterator<Tp> const &rhs )
	{
		return lsh.base() >= rhs.base();
	}

	template <class Tp>
	vector_iterator<Tp>	operator+( typename vector_iterator<Tp>::difference_type n, vector_iterator<Tp> const &it )
	{
		return it + n;
	}

	template <class Tp>
	typename vector_iterator<Tp>::difference_type	operator-( vector_iterator<Tp> const &lhs, vector_iterator<Tp> const &rhs)
	{
		return lhs.base() - rhs.base();
	}

};

}

#endif
