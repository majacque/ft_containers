#ifndef RB_TREE_ITERATOR_HPP
# define RB_TREE_ITERATOR_HPP

#include "iterator.hpp"

namespace __ft
{
	template < class T >
	class __rb_tree_iterator
	{
	protected:
		T	_current;

		typedef ft::iterator_traits<T>					traits_type;

	public:
		typedef T										iterator_type;
		typedef typename traits_type::iterator_category	iterator_category;
		typedef typename traits_type::value_type		node_type;
		typedef typename traits_type::difference_type	difference_type;
		typedef typename traits_type::reference			reference;
		typedef typename traits_type::pointer			pointer;


		__rb_tree_iterator(): _current(iterator_type())
		{
			return;
		}

		explicit __rb_tree_iterator(const iterator_type& it): _current(it)
		{
			return;
		}

		template <typename _T>
		__rb_tree_iterator(__rb_tree_iterator<_T> const & rhs)
			: _current(rhs.base())
		{
			return;
		}

		/**************************************************************************/
		/*                            MEMBER FUNCTIONS                            */
		/**************************************************************************/

		const iterator_type&	base( void ) const
		{
			return _current;
		}

		/**************************************************************************/
		/*                            MEMBER OPERATOR                             */
		/**************************************************************************/

		node_type&	operator=( node_type const & rhs )
		{
			_current = rhs._current;
			return *this;
		}

		typename node_type::value_type&	operator*( void ) const
		{
			return _current->val;
		}

		typename node_type::value_type*	operator->( void ) const
		{
			return &_current->val;
		}

		__rb_tree_iterator&	operator++( void )
		{
			if (_current->color == PTENODE)
				return --*this;

			if (_current->childs[RIGHT])
			{
				_current = _current->childs[RIGHT];
				while (_current->childs[LEFT])
					_current = _current->childs[LEFT];
			}
			else
			{
				while (_current->parent && _current == _current->parent->childs[RIGHT])
					_current = _current->parent;
				if (_current->parent)
					_current = _current->parent;
			}
			return *this;
		}

		__rb_tree_iterator	operator++( int )
		{
			__rb_tree_iterator	tmp(_current);

			++*this;
			return tmp;
		}

		__rb_tree_iterator&	operator--( void )
		{
			if (_current->childs[LEFT])
			{
				_current = _current->childs[LEFT];
				while (_current->childs[RIGHT])
					_current = _current->childs[RIGHT];
			}
			else if (_current->parent && _current->parent->color != PTENODE && _current->childs[RIGHT])
			{
				while (_current->parent && _current == _current->parent->childs[LEFT])
					_current = _current->parent;
				if (_current->parent)
					_current = _current->parent;
			}
			return *this;
		}

		__rb_tree_iterator	operator--( int )
		{
			__rb_tree_iterator	tmp(_current);

			--*this;
			return tmp;
		}

	};

	/**************************************************************************/
	/*                          NON-MEMBER OPERATOR                           */
	/**************************************************************************/

	template <typename _T>
	bool	operator==( __rb_tree_iterator<_T> const & lhs, __rb_tree_iterator<_T> const & rhs )
	{
		return lhs.base() == rhs.base();
	}

	template <typename _TpL, typename _TpR>
	bool	operator==( __rb_tree_iterator<_TpL> const & lhs, __rb_tree_iterator<_TpR> const & rhs )
	{
		return lhs.base() == rhs.base();
	}

	template <typename _T>
	bool	operator!=( __rb_tree_iterator<_T> const & lhs, __rb_tree_iterator<_T> const & rhs )
	{
		return lhs.base() != rhs.base();
	}

	template <typename _TpL, typename _TpR>
	bool	operator!=( __rb_tree_iterator<_TpL> const & lhs, __rb_tree_iterator<_TpR> const & rhs )
	{
		return lhs.base() != rhs.base();
	}

}

#endif
