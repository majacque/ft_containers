#ifndef RB_TREE_HPP
# define RB_TREE_HPP

#include "rb_node.hpp"
#include "rb_tree_iterator.hpp"
#include "iterator.hpp"
#include <functional>
#include <memory>

// TODO add a nil element to do a past-the-end
// the root parent point on it
// his left child point on the max
namespace ft
{
	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<rb_node<T> > >
	class rb_tree
	{
	public:
		typedef T														value_type;
		typedef Compare													compare_type;
		typedef Alloc													allocator_type;
		typedef size_t													size_type;

		typedef typename allocator_type::const_pointer					const_pointer;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::reference						reference;

		typedef __ft::__rb_tree_iterator<const_pointer>					const_iterator;
		typedef __ft::__rb_tree_iterator<pointer>						iterator;
		typedef reverse_iterator<const_iterator>						const_reverse_iterator;
		typedef reverse_iterator<iterator>								reverse_iterator;

		typedef typename iterator_traits<iterator>::difference_type		difference_type;

	private:
		pointer			_nil_node;
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
		 */
		rb_tree( void ): _nil_node(), _root(), _min(), _max(), _size(), _alloc() // REMIND see if we can take an argument like vector default constructor
		{
			_nil_node = _alloc.allocate(1LU);
			_alloc.construct(_nil_node, 0);
			return;
		}

		// TODO constructor range of iterator
		// TODO copy constructor

		/**************************************************************************/
		/*                               DESTRUCTOR                               */
		/**************************************************************************/

		/**
		 * @brief Destroy the rb tree object
		 */
		~rb_tree( void )
		{
			this->clear();
			_alloc.destroy(_nil_node);
			_alloc.deallocate(_nil_node, 1LU);
			return;
		}

		/**************************************************************************/
		/*                            MEMBER FUNCTIONS                            */
		/**************************************************************************/

		// Capacity

		/**
		 * @brief Returns whether the rb tree is empty (i.e. whether its size is 0).
		 * 
		 * @return true if the container size is 0, false otherwise.
		 */
		bool	empty( void ) const
		{
			return !_size;
		}

		/**
		 * @brief Returns the number of elements in the rb tree.
		 */
		size_type	size( void ) const
		{
			return _size;
		}

		/**
		 * @brief Returns the maximum number of elements that the rb tree can hold.
		 * This is the maximum potential size the tree can reach due to known system or library implementation limitations,
		 * but the tree is by no means guaranteed to be able to reach that size: it can still fail to allocate storage at any point before that size is reached.
		 */
		size_type	max_size( void ) const
		{
			return _alloc.max_size();
		}

		// Modifiers

		/**
		 * @brief Removes all elements from the rb tree (which are destroyed), leaving the rb tree with a size of 0.
		 */
		void	clear( void )
		{
			rb_tree::__clear(_root);
			_root = NULL;
			_min = NULL;
			_max = NULL;
			_size = 0LU;
			_nil_node.childs[LEFT] = NULL;
		}

	private:

		static void	__clear( pointer node )
		{
			if (!node)
				return;
			rb_tree::__clear(node.childs[RIGHT]);
			node.childs[RIGHT] = NULL;
			rb_tree::__clear(node.childs[LEFT]);
			node.childs[LEFT] = NULL;
			_alloc.destroy(node);
			_alloc.deallocate(node, 1LU);
			return;
		}
	};
}

#endif
