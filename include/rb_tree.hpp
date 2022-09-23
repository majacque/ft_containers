#ifndef RB_TREE_HPP
# define RB_TREE_HPP

#include "rb_node.hpp"
#include <functional>
#include <memory>

namespace ft
{
	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<rb_node<T> > >
	class rb_tree
	{
	public:
		typedef T											value_type;
		typedef Compare										compare_type;
		typedef Alloc										allocator_type;
		typedef size_t										size_type;

		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;

		// TODO iterators
		// typedef rb_tree_iterator<value_type const, _node_type const>	const_iterator;
		// typedef rb_tree_iterator<value_type, _node_type>				iterator;

		// typedef reverse_iterator<const_iterator>						const_reverse_iterator;
		// typedef reverse_iterator<iterator>								reverse_iterator;

		// typedef typename iterator_traits<iterator>::difference_type		difference_type;
	
	private:
		pointer			_root;
		pointer			_min;
		pointer			_max;
		size_type		_size;
		allocator_type	_alloc;

	public:
		/**************************************************************************/
		/*                               CONSTRUCTOR                              */
		/**************************************************************************/

		/**
		 * @brief Constructs an empty rb tree, with no elements.
		 * 
		 */
		rb_tree( void ): _root(), _min(), _max(), _size(), alloc() // REMIND see if we can take an argument like vector default constructor
		{
			return;
		}

		// TODO constructor range of iterator
		// TODO copy constructor

	/**************************************************************************/
	/*                               DESTRUCTOR                               */
	/**************************************************************************/

		~rb_tree( void )
		{
			// TODO clear()
			return;
		}
	};
}

#endif
