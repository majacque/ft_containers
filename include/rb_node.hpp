#ifndef RB_NODE_HPP
# define RB_NODE_HPP

#include "rb_node_defs.hpp"

namespace ft {

template < class T >
struct rb_node
{
	typedef T	value_type;

	rb_node*	parent;
	rb_node*	childs[2];
	value_type	val;
	int			color;

	rb_node( value_type const & val = value_type() ): parent(), childs(), val(val), color(REDNODE)
	{
		return;
	}
};

template <typename _Tp>
bool	operator==( rb_node<_Tp> const & lhs, rb_node<_Tp> const & rhs )
{
	return lhs.val == rhs.val;
}

template <typename _TpL, typename _TpR>
bool	operator==( rb_node<_TpL> const & lhs, rb_node<_TpR> const & rhs )
{
	return lhs.val == rhs.val;
}

template <typename _Tp>
bool	operator!=( rb_node<_Tp> const & lhs, rb_node<_Tp> const & rhs )
{
	return lhs.val != rhs.val;
}

template <typename _TpL, typename _TpR>
bool	operator!=( rb_node<_TpL> const & lhs, rb_node<_TpR> const & rhs )
{
	return lhs.val != rhs.val;
}

}

#endif
