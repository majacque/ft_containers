#ifndef RB_TREE_ITERATOR_HPP
# define RB_TREE_ITERATOR_HPP

#include "iterator.hpp"

namespace __ft
{
	template < class T , class NodeValue >
	class __rb_tree_iterator
	{
	protected:
		T	_current;

		typedef ft::iterator_traits<NodeValue *>						traits_type;

	public:
		typedef T											iterator_type;
		typedef typename std::bidirectional_iterator_tag	iterator_category;
		typedef typename traits_type::value_type			value_type;
		typedef typename traits_type::difference_type		difference_type;
		typedef typename traits_type::reference				reference;
		typedef typename traits_type::pointer				pointer;

		typedef typename ft::iterator_traits<T>::value_type	node_type;

		__rb_tree_iterator(): _current(iterator_type())
		{
			return;
		}

		explicit __rb_tree_iterator(const iterator_type& it): _current(it)
		{
			return;
		}

		template <typename _T, typename _NodeValue>
		__rb_tree_iterator(__rb_tree_iterator<_T, _NodeValue> const & rhs)
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

		reference	operator*( void ) const
		{
			return _current->val;
		}

		pointer	operator->( void ) const
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
			else if (_current->parent)
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

	template <typename _T, typename _NodeValue>
	bool	operator==( __rb_tree_iterator<_T, _NodeValue> const & lhs, __rb_tree_iterator<_T, _NodeValue> const & rhs )
	{
		return lhs.base() == rhs.base();
	}

	template <typename _TpL, typename _NodeValueL, typename _TpR, typename _NodeValueR>
	bool	operator==( __rb_tree_iterator<_TpL, _NodeValueL> const & lhs, __rb_tree_iterator<_TpR, _NodeValueR> const & rhs )
	{
		return lhs.base() == rhs.base();
	}

	template <typename _T, typename _NodeValue>
	bool	operator!=( __rb_tree_iterator<_T, _NodeValue> const & lhs, __rb_tree_iterator<_T, _NodeValue> const & rhs )
	{
		return lhs.base() != rhs.base();
	}

	template <typename _TpL, typename _NodeValueL, typename _TpR, typename _NodeValueR>
	bool	operator!=( __rb_tree_iterator<_TpL, _NodeValueL> const & lhs, __rb_tree_iterator<_TpR, _NodeValueR> const & rhs )
	{
		return lhs.base() != rhs.base();
	}

}

#endif
