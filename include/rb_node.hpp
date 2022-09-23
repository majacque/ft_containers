#ifndef RB_NODE_HPP
# define RB_NODE_HPP

#include "rb_node_defs.hpp"

namespace ft {

template < class T >
struct rb_node
{
	typedef T	value_type;

	value_type	val;
	bool		color;
	rb_node*	parent;
	rb_node*	childs[2];

	rb_node( value_type const & val = value_type() ): val(val), color(RED), parent(), childs()
	{
		return;
	}
};
}

#endif
