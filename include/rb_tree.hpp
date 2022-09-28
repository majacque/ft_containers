#ifndef RB_TREE_HPP
# define RB_TREE_HPP

#include "rb_node.hpp"
#include "rb_tree_iterator.hpp"
#include "iterator.hpp"
#include "utility.hpp"
#include "algorithm.hpp"
#include <functional>
#include <memory>
#include <list> // _validity_check()
#include <cstdlib> // _validity_check()

namespace ft
{
	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<rb_node<T> > >
	class rb_tree
	{
	public:
		typedef T															value_type;
		typedef Compare														compare_type;
		typedef Alloc														allocator_type;
		typedef size_t														size_type;

		typedef typename allocator_type::const_pointer						const_pointer;
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::reference							reference;

		typedef __ft::__rb_tree_iterator<const_pointer, const value_type>	const_iterator;
		typedef __ft::__rb_tree_iterator<pointer, value_type>				iterator;
		typedef reverse_iterator<const_iterator>							const_reverse_iterator;
		typedef reverse_iterator<iterator>									reverse_iterator;

		typedef typename iterator_traits<iterator>::difference_type			difference_type;

	private:
		/* 
		* _nil_node rules:
		* 	- the root parent point on it
		* 	- his left child point on the max
		*/
		pointer			_nil_node;
		pointer			_root;
		pointer			_min;
		pointer			_max;
		size_type		_size;
		allocator_type	_alloc;
		compare_type	_cmp;

	public:
		bool	_validity_check( void )
		{
			if (__integrityCheck(_root))
				return false;

			if (__propertiesCheck(_root, compare_type()))
				return false;

			return true;
		}

		/**************************************************************************/
		/*                               CONSTRUCTOR                              */
		/**************************************************************************/

		/**
		 * @brief Constructs an empty rb tree, with no elements.
		 */
		rb_tree( void ): _nil_node(), _root(), _min(), _max(), _size(), _alloc(), _cmp() // REMIND see if we can take an argument like vector default constructor
		{
			_nil_node = _alloc.allocate(1LU);
			_alloc.construct(_nil_node, rb_node<T>());
			_nil_node->color = PTENODE;
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

		// TODO operator=()

		// Iterators

		/**
		 * @brief Returns an iterator referring to the first element of the rb tree.
		 * If the tree is empty returns an iterator equivalent to @a end().
		 */
		iterator	begin( void )
		{
			return iterator(_min);
		}

		/**
		 * @brief Returns a const iterator referring to the first element of the rb tree.
		 * If the tree is empty returns a const iterator equivalent to @a end().
		 */
		const_iterator	begin( void ) const
		{
			return const_iterator(_min);
		}

		/**
		 * @brief Returns an iterator to the element following the last element of the rb tree.
		 * This element acts as a placeholder; attempting to access it results in undefined behavior.
		 */
		iterator	end( void )
		{
			return iterator(_nil_node);
		}

		/**
		 * @brief Returns a const iterator to the element following the last element of the rb tree.
		 * This element acts as a placeholder; attempting to access it results in undefined behavior.
		 */
		const_iterator	end( void ) const
		{
			return const_iterator(_nil_node);
		}

		/**
		 * @brief Returns a reverse iterator to the first element of the reversed rb tree.
		 * It corresponds to the last element of the non-reversed rb tree. If the tree is empty, the returned iterator is equal to rend().
		 */
		reverse_iterator	rbegin( void )
		{
			return reverse_iterator(this->end());
		}

		/**
		 * @brief Returns a const reverse iterator to the first element of the reversed rb tree.
		 * It corresponds to the last element of the non-reversed rb tree. If the tree is empty, the returned iterator is equal to rend().
		 */
		const_reverse_iterator	rbegin( void ) const
		{
			return const_reverse_iterator(this->end());
		}

		/**
		 * @brief Returns a reverse iterator to the element following the last element of the reversed rb tree.
		 * It corresponds to the element preceding the first element of the non-reversed rb tree.
		 * This element acts as a placeholder, attempting to access it results in undefined behavior.
		 */
		reverse_iterator	rend( void )
		{
			return reverse_iterator(this->begin());
		}

		/**
		 * @brief Returns a const reverse iterator to the element following the last element of the reversed rb tree.
		 * It corresponds to the element preceding the first element of the non-reversed rb tree.
		 * This element acts as a placeholder, attempting to access it results in undefined behavior.
		 */
		const_reverse_iterator	rend( void ) const
		{
			return const_reverse_iterator(this->begin());
		}

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
			this->__clear(_root);
			_root = NULL;
			_min = NULL;
			_max = NULL;
			_size = 0LU;
			_nil_node->childs[LEFT] = NULL;
		}

		/**
		 * @brief Inserts element(s) into the rb tree, if the rb tree doesn't already contain an element with an equivalent key.
		 * 
		 * @param val Element value to insert.
		 * @return Returns a pair consisting of an iterator to the inserted element (or to the element that prevented the insertion)
		 * and a bool value set to true if the insertion took place.
		 */
		pair<iterator, bool>	insert( value_type const & val )
		{
			if (!_root)
			{
				_root = _alloc.allocate(1LU);
				_alloc.construct(_root, rb_node<T>(val));
				_root->color = BLACKNODE;
				_root->parent = _nil_node;
				_min = _root;
				_nil_node->childs[LEFT] = _max = _root;
				++_size;

				return pair<iterator, bool>(iterator(_root), true);
			}

			pointer	position = _root;
			pointer	parent;
			while (position)
			{
				parent = position;

				if (_cmp(val, position->val))
					position = position->childs[LEFT];
				else if (_cmp(position->val, val))
					position = position->childs[RIGHT];
				else
					return pair<iterator, bool>(iterator(position), false);
			}

			pointer new_node = _alloc.allocate(1LU);
			_alloc.construct(new_node, rb_node<T>(val));
			new_node->parent = parent;
			if (_cmp(val, parent->val))
			{
				parent->childs[LEFT] = new_node;
				if (parent == _min)
					_min = new_node;
			}
			else if (_cmp(parent->val, val))
			{
				parent->childs[RIGHT] = new_node;
				if (parent == _max)
					_nil_node->childs[LEFT] = _max = new_node;
			}
			++_size;
			rb_tree::_balance_insert(new_node);

			return pair<iterator, bool>(iterator(new_node), true);
		}

		/**
		 * @brief Inserts element(s) into the rb tree, if the rb tree doesn't already contain an element with an equivalent key.
		 * Inserts @a val in the position as close as possible to @a hint.
		 * 
		 * @param hint An iterator used as a suggestion as to where to start the search.
		 * @param val Element value to insert.
		 * @return An iterator to the inserted element, or to the element that prevented the insertion.
		 */
		iterator	insert( iterator hint, value_type const & val )
		{
			pointer	node = hint.base();

			int	direction;
			if (_cmp(val, node->val))
				direction = LEFT;
			else if (_cmp(node->val, val))
				direction = RIGHT;
			else
				return iterator(hint);

			pointer	parent = node->parent;
			while (parent->color != PTENODE && node == parent->childs[direction])
			{
				node = parent;
				parent = node->parent;
			}
			if (parent->color != PTENODE && direction == LEFT && _cmp(val, parent->val))
				return this->insert(val).first;
			else if (parent->color != PTENODE && direction == RIGHT && _cmp(parent->val, val))
				return this->insert(val).first;

			parent = hint.base();
			if (parent->childs[direction])
			{
				node = parent->childs[direction];
				while (node)
				{
					if (_cmp(val, node->val))
					{
						parent = node;
						node = node->childs[direction];
					}
					else if (_cmp(node->val, val))
					{
						parent = node;
						node = node->childs[!direction];
					}
					else
						return iterator(node);
				}
			}

			node = _alloc.allocate(1LU);
			_alloc.construct(node, rb_node<T>(val));
			node->parent = parent;
			if (_cmp(val, parent->val))
			{
				parent->childs[LEFT] = node;
				if (parent == _min)
					_min = node;
			}
			else if (_cmp(parent->val, val))
			{
				parent->childs[RIGHT] = node;
				if (parent == _max)
					_nil_node->childs[LEFT] = _max = node;
			}
			++_size;
			rb_tree::_balance_insert(node);

			return iterator(node);
		}

		/**
		 * @brief Inserts elements, from range [first, last),
		 * into the rb tree if the rb tree doesn't contain an element with an equivalent key.
		 * If multiple elements in the range have keys that compare equivalent, it is unspecified which element is inserted.
		 * 
		 * @param first An input iterator to the initial position in a range.
		 * @param last An input iterator to the final position in a range.
		 */
		template <class InputIterator>
		void	insert( InputIterator first, InputIterator last )
		{
			for ( ; first != last; ++first)
				this->insert(first->val);

			return;
		}

		// TODO erase (iterator) Removes the element at pos.
		iterator	erase( iterator pos );

		// TODO erase (key) Removes the element (if one exists) with the key equivalent to key.
		size_type	erase( value_type const & val );

		/**
		 * @brief Exchanges the contents of the rb tree with those of @a rhs.
		 * Does not invoke any move, copy, or swap operations on individual elements.
		 * All iterators and references remain valid. The past-the-end iterator is invalidated.
		 * 
		 * @param rhs An other rb tree with same template parameters.
		 */
		void	swap( rb_tree& rhs )
		{
			ft::swap<pointer>(_root, rhs._root);
			ft::swap<pointer>(_max, rhs._max);
			ft::swap<pointer>(_min, rhs._min);
			ft::swap<size_type>(_size, rhs._size);

			ft::swap<pointer>(_nil_node, rhs._nil_node);
			// _root->parent = _nil_node; // REMIND see if we invalidate iterators on end()
			// _nil_node->childs[LEFT] = _max;
			// rhs._root->parent = rhs._nil_node;
			// rhs._nil_node->childs[LEFT] = rhs._max;
		}

	private:
		static void	_rotate( pointer src, pointer dst, int direction )
		{
			pointer	parent = dst->parent;

			if (parent->color != PTENODE)
			{
				if (dst == parent->childs[LEFT])
					parent->childs[LEFT] = src;
				else
					parent->childs[RIGHT] = src;
			}
			src->parent = parent;

			pointer	tmp = src->childs[direction];

			src->childs[direction] = dst;
			dst->parent = src;
			dst->childs[!direction] = tmp;
			if (tmp)
				tmp->parent = dst;

			return;
		}

		static void	_balance_insert( pointer node )
		{
			pointer	parent = node->parent;
			if (parent->color == BLACKNODE)
				return;
			else if (parent->color == PTENODE)
			{
				node->color = BLACKNODE;
				return;
			}

			pointer grandparent = parent->parent;
			if (grandparent->color == PTENODE)
			{
				parent->color = BLACKNODE;
				return;
			}

			int	direction = RIGHT;
			if (parent == grandparent->childs[LEFT])
				direction = LEFT;

			pointer uncle = grandparent->childs[!direction];
			if (!uncle || uncle->color == BLACKNODE)
			{
				if (node == parent->childs[!direction])
				{
					rb_tree::_rotate(node, parent, direction);
					ft::swap<pointer>(node, parent);
				}

				rb_tree::_rotate(parent, grandparent, !direction);
				parent->color = BLACKNODE;
				grandparent->color = REDNODE;
			}
			else
			{
				parent->color = BLACKNODE;
				uncle->color = BLACKNODE;
				grandparent->color = REDNODE;
				rb_tree::_balance_insert(grandparent);
				// REMIND try with a goto with a label 'begin'
			}

			return;
		}

		void	__clear( pointer node )
		{
			if (!node)
				return;
			this->__clear(node->childs[RIGHT]);
			node->childs[RIGHT] = NULL;
			this->__clear(node->childs[LEFT]);
			node->childs[LEFT] = NULL;
			_alloc.destroy(node);
			_alloc.deallocate(node, 1LU);
			return;
		}
	};

template <typename T>
inline static void    __blackSteps(ft::rb_node<T> const *const node, std::list<int> &lst, int const steps)
{
    if (!node)
        return lst.push_back(steps);
    __blackSteps(node->childs[LEFT], lst, steps + (node->color == BLACKNODE));
    __blackSteps(node->childs[RIGHT], lst, steps + (node->color == BLACKNODE));
}

template <typename T, typename Compare>
inline static int    __propertiesCheck(ft::rb_node<T> const *const node, Compare const cmp)
{
    std::list<int>                    lst;
    std::list<int>::const_iterator    it;

    if (!node)
        return EXIT_SUCCESS;
    // Color check
    {
        if (node->color != REDNODE && node->color != BLACKNODE)
            return EXIT_FAILURE;
    }
    // Order check
    {
        if ((node->childs[LEFT] && !cmp(node->childs[LEFT]->val, node->val)) ||
            (node->childs[RIGHT] && !cmp(node->val, node->childs[RIGHT]->val)))
            return EXIT_FAILURE;
    }
    // Red violation check
    {
        if (node->color == REDNODE &&
            ((node->childs[LEFT] && node->childs[LEFT]->color == REDNODE) ||
            (node->childs[RIGHT] && node->childs[RIGHT]->color == REDNODE)))
            return EXIT_FAILURE;
    }
    // Black violation check
    {
        __blackSteps(node, lst, 0U);
        for (it = lst.begin() ; it != lst.end() ; ++it)
            if (*it != *lst.begin())
                return EXIT_FAILURE;
    }
    return __propertiesCheck(node->childs[LEFT], cmp) || __propertiesCheck(node->childs[RIGHT], cmp);
}

template <typename T>
inline static int    __integrityCheck(ft::rb_node<T> const *const node)
{
    if (!node)
        return EXIT_SUCCESS;
    if (node->childs[LEFT] && node->childs[LEFT]->parent != node)
        return EXIT_FAILURE;
    if (node->childs[RIGHT] && node->childs[RIGHT]->parent != node)
        return EXIT_FAILURE;
    return __integrityCheck(node->childs[LEFT]) || __integrityCheck(node->childs[RIGHT]);
}

}

#endif
