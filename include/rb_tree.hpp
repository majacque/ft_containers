#ifndef RB_TREE_HPP
# define RB_TREE_HPP

#include "rb_node.hpp"
#include "rb_tree_iterator.hpp"
#include "iterator.hpp"
#include "utility.hpp"
#include "algorithm.hpp"
#include <functional>
#include <memory>

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
		compare_type	_cmp;
		allocator_type	_alloc;

	public:

		/**************************************************************************/
		/*                               CONSTRUCTOR                              */
		/**************************************************************************/

		/**
		 * @brief Constructs an empty rb tree, with no elements.
		 * 
		 * @param cmp Comparison function object to use for all comparisons of keys.
		 * @param alloc Allocator to use for all memory allocations of this rb tree.
		 */
		explicit rb_tree( compare_type const & cmp = compare_type(), allocator_type const & alloc = allocator_type() ):
				_nil_node(), _root(), _min(), _max(), _size(), _cmp(cmp), _alloc(alloc)
		{
			_nil_node = _alloc.allocate(1LU);
			_alloc.construct(_nil_node, rb_node<T>());
			_nil_node->color = PTENODE;
			_min = _nil_node;
			return;
		}

		/**
		 * @brief Constructs the rb tree with the contents of the range [first, last).
		 * If multiple elements in the range have keys that compare equivalent, it is unspecified which element is inserted.
		 * 
		 * @param first An input iterator to the initial position in a range.
		 * @param last An input iterator to the final position in a range.
		 * @param cmp Comparison function object to use for all comparisons of keys.
		 * @param alloc Allocator to use for all memory allocations of this rb tree.
		 */
		template <class InputIterator>
		rb_tree( InputIterator first, InputIterator last, compare_type const & cmp = compare_type(), allocator_type const & alloc = allocator_type() ):
				_nil_node(), _root(), _min(), _max(), _size(), _cmp(cmp), _alloc(alloc)
		{
			_nil_node = _alloc.allocate(1LU);
			_alloc.construct(_nil_node, rb_node<T>());
			_nil_node->color = PTENODE;
			_min = _nil_node;

			for ( ; first != last; ++first)
				this->insert(*first);

			return;
		}

		/**
		 * @brief Constructs a rb tree with a copy of each of the elements in @a rhs.
		 * 
		 * @param rhs Another rb tree to be used as source to initialize the elements of the rb tree with.
		 */
		rb_tree( rb_tree const & rhs): _nil_node(), _root(), _min(), _max(), _size(rhs._size), _cmp(rhs._cmp), _alloc(rhs._alloc)
		{
			_nil_node = _alloc.allocate(1LU);
			_alloc.construct(_nil_node, rb_node<T>());
			_nil_node->color = PTENODE;
			_min = _nil_node;
			_root = this->_dup(rhs._root, _nil_node);
			if (_root)
			{
				for ( _min = _root; _min->childs[LEFT]; _min = _min->childs[LEFT] );
				for ( _max = _root; _max->childs[RIGHT]; _max = _max->childs[RIGHT] );
			}
			_nil_node->childs[LEFT] = _max;

			return;
		}

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

		/**
		 * @brief Assigns new contents to the rb tree, replacing its current content.
		 * 
		 * @param rhs A rb tree of the same type.
		 * @return A reference to the instance.
		 */
		rb_tree&	operator=( rb_tree const & rhs )
		{
			this->clear();
			_root = this->_dup(rhs._root, _nil_node);
			if (_root)
			{
				for ( _min = _root; _min->childs[LEFT]; _min = _min->childs[LEFT] );
				for ( _max = _root; _max->childs[RIGHT]; _max = _max->childs[RIGHT] );
			}
			_nil_node->childs[LEFT] = _max;
			_size = rhs._size;

			return *this;
		}

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
			_min = _nil_node;
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
				if (_cmp(val, position->val))
				{
					parent = position;
					position = position->childs[LEFT];
				}
				else if (_cmp(position->val, val))
				{
					parent = position;
					position = position->childs[RIGHT];
				}
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
			this->_balance_insert(new_node);

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
			if (!_root)
			{
				_root = _alloc.allocate(1LU);
				_alloc.construct(_root, rb_node<T>(val));
				_root->color = BLACKNODE;
				_root->parent = _nil_node;
				_min = _root;
				_nil_node->childs[LEFT] = _max = _root;
				++_size;

				return iterator(_root);
			}

			if (hint.base() == _nil_node)
				return this->insert(val).first;

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
			if (parent->color != PTENODE)
			{
				if (direction == LEFT && _cmp(val, parent->val))
					return this->insert(val).first;
				else if (direction == RIGHT && _cmp(parent->val, val))
					return this->insert(val).first;
				else if (!_cmp(val, parent->val) && !_cmp(parent->val, val))
					return iterator(parent);
			}

			parent = hint.base();
			if (parent->childs[direction])
			{
				node = parent->childs[direction];
				while (node)
				{
					if (_cmp(val, node->val))
					{
						parent = node;
						node = node->childs[LEFT];
					}
					else if (_cmp(node->val, val))
					{
						parent = node;
						node = node->childs[RIGHT];
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
			this->_balance_insert(node);

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
				this->insert(*first);

			return;
		}

		/**
		 * @brief Removes the element at @a pos. References and iterators to the erased elements are invalidated.
		 * Other references and iterators are not affected. The iterator @a pos must be valid and dereferenceable.
		 * Thus the end() iterator (which is valid, but is not dereferenceable) cannot be used as a value for @a pos.
		 * 
		 * @param pos An iterator to the element to remove.
		 */
		void	erase( iterator pos )
		{
			pointer	node = pos.base();

			if (_size == 1LU)
			{
				this->clear();
				return;
			}

			if (node->childs[LEFT] && node->childs[RIGHT])
			{
				pointer successor = node->childs[RIGHT];
				for ( ; successor->childs[LEFT]; successor = successor->childs[LEFT] );
				rb_tree::_swap_value_node(node, successor);
				if (_root == node)
					_root = successor;
			}

			if (node->childs[LEFT] || node->childs[RIGHT])
			{
				int	direction = RIGHT;
				if (node->childs[LEFT])
					direction = LEFT;

				if (node->parent->color != PTENODE)
				node->parent->childs[rb_tree::_child_direction(node)] = node->childs[direction];
				node->childs[direction]->parent = node->parent;
				node->childs[direction]->color = BLACKNODE;
				if (_root == node)
					_root = node->childs[direction];
				if (_min == node)
					_min = node->childs[direction];
				if (_max == node)
					_nil_node->childs[LEFT] = _max = node->childs[direction];
			}
			else if (node->color == REDNODE)
			{
				node->parent->childs[rb_tree::_child_direction(node)] = NULL;
				if (_min == node)
					_min = node->parent;
				if (_max == node)
					_nil_node->childs[LEFT] = _max = node->parent;
			}
			else
			{
				if (_min == node)
					_min = node->parent;
				if (_max == node)
					_nil_node->childs[LEFT] = _max = node->parent;
				int	direction = rb_tree::_child_direction(node);
				node->parent->childs[direction] = NULL;
				this->_balance_erase(node, direction);
			}

			_alloc.destroy(node);
			_alloc.deallocate(node, 1LU);
			--_size;

			return;
		}

		/**
		 * @brief Removes the element (if one exists) with the key equivalent to @a val.
		 * 
		 * @param val Key value of the element to erase.
		 * @return Number of elements removed (0 or 1).
		 */
		size_type	erase( value_type const & val )
		{
			iterator	it = this->find(val);
			if (it.base() == _nil_node)
				return 0LU;
			this->erase(it);
			return 1LU;
		}

		/**
		 * @brief Removes the elements in the range [first; last), which must be a valid range in the rb tree.
		 * 
		 * @param first An iterator to the initial position in a range.
		 * @param last An iterator to the final position in a range.
		 */
		void	erase( iterator first, iterator last )
		{
			while (first != last)
				this->erase(first++);
		}

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

		// Lookup

		/**
		 * @brief Finds an element with key equivalent to @a val.
		 * 
		 * @param val Key value of the element to search for.
		 * @return An iterator to the element with a key equivalent to @a val.
		 * If no such element is found, an iterator to end() is returned.
		 */
		iterator	find( value_type const & val )
		{
			pointer	node = _root;
			while (node)
			{
				if (_cmp(val, node->val))
					node = node->childs[LEFT];
				else if (_cmp(node->val, val))
					node = node->childs[RIGHT];
				else
					return iterator(node);
			}

			return iterator(_nil_node);
		}

		/**
		 * @brief Finds an element with key equivalent to @a val.
		 * 
		 * @param val Key value of the element to search for.
		 * @return A const iterator to the element with a key equivalent to @a val.
		 * If no such element is found, a const iterator to end() is returned.
		 */
		const_iterator	find( value_type const & val ) const
		{
			pointer	node = _root;
			while (node)
			{
				if (_cmp(val, node->val))
					node = node->childs[LEFT];
				else if (_cmp(node->val, val))
					node = node->childs[RIGHT];
				else
					return const_iterator(node);
			}

			return const_iterator(_nil_node);
		}

		/**
		 * @brief Returns the number of elements with key that compares equivalent to the specified argument,
		 * which is either 1 or 0 since this rb tree does not allow duplicates.
		 * 
		 * @param val Key value of the elements to count.
		 * @return Number of elements with key that compares equivalent to @a val, which is either 1 or 0 for (1).
		 */
		size_type	count( value_type const & val ) const
		{
			if (this->find(val).base() != _nil_node)
				return 1LU;
			return 0LU;
		}

		/**
		 * @brief Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) @a val.
		 * 
		 * @param val Key value to compare the elements to.
		 * @return An iterator pointing to the first element that is not less than @a val.
		 * If no such element is found, end() is returned.
		 */
		iterator	lower_bound( value_type const & val )
		{
			if (!_root || _cmp(_max->val, val))
				return iterator(_nil_node);

			pointer	node = _root;
			pointer	lower_high = _max;
			while (node)
			{
				if (_cmp(val, node->val))
				{
					if (_cmp(node->val, lower_high->val))
						lower_high = node;
					node = node->childs[LEFT];
				}
				else if (_cmp(node->val, val))
				{
					node = node->childs[RIGHT];
				}
				else
					return iterator(node);
			}

			return iterator(lower_high);
		}

		/**
		 * @brief Returns a const iterator pointing to the first element that is not less than (i.e. greater or equal to) @a val.
		 * 
		 * @param val Key value to compare the elements to.
		 * @return A const iterator pointing to the first element that is not less than @a val.
		 * If no such element is found, end() is returned.
		 */
		const_iterator	lower_bound( value_type const & val ) const
		{
			if (!_root || _cmp(_max->val, val))
				return const_iterator(_nil_node);

			pointer	node = _root;
			pointer	lower_high = _max;
			while (node)
			{
				if (_cmp(val, node->val))
				{
					if (_cmp(node->val, lower_high->val))
						lower_high = node;
					node = node->childs[LEFT];
				}
				else if (_cmp(node->val, val))
				{
					node = node->childs[RIGHT];
				}
				else
					return const_iterator(node);
			}

			return const_iterator(lower_high);
		}

		/**
		 * @brief Returns an iterator pointing to the first element that is strictly greater than @a val.
		 * 
		 * @param val Key value to compare the elements to.
		 * @return An iterator pointing to the first element that is strictly greater than @a val.
		 * If no such element is found, end() is returned.
		 */
		iterator	upper_bound( value_type const & val )
		{
			if (!_root || !_cmp(val, _max->val))
				return iterator(_nil_node);

			pointer	node = _root;
			pointer	lower_high = _max;
			while (node)
			{
				if (_cmp(val, node->val))
				{
					if (_cmp(node->val, lower_high->val))
						lower_high = node;
					node = node->childs[LEFT];
				}
				else
				{
					if (_cmp(lower_high->val, node->val))
						lower_high = node;
					node = node->childs[RIGHT];
				}
			}

			return iterator(lower_high);
		}

		/**
		 * @brief Returns a const iterator pointing to the first element that is strictly greater than @a val.
		 * 
		 * @param val Key value to compare the elements to.
		 * @return A const iterator pointing to the first element that is strictly greater than @a val.
		 * If no such element is found, end() is returned.
		 */
		const_iterator	upper_bound( value_type const & val ) const
		{
			if (!_root || !_cmp(val, _max->val))
				return const_iterator(_nil_node);

			pointer	node = _root;
			pointer	lower_high = _max;
			while (node)
			{
				if (_cmp(val, node->val))
				{
					if (_cmp(node->val, lower_high->val))
						lower_high = node;
					node = node->childs[LEFT];
				}
				else
				{
					if (_cmp(lower_high->val, node->val))
						lower_high = node;
					node = node->childs[RIGHT];
				}
			}

			return const_iterator(lower_high);
		}

		/**
		 * @brief Returns a range containing all elements with the given @a val in the rb tree.
		 * The range is defined by two iterators, one pointing to the first element that is not less than @a val and
		 * another pointing to the first element greater than @a val.
		 * Alternatively, the first iterator may be obtained with lower_bound(), and the second with upper_bound().
		 * 
		 * @param val A val value to compare the elements to.
		 * @return A ft::pair containing a pair of iterators defining the wanted range:
		 * The first pointing to the first element that is not less than @a val and the second pointing to the first element greater than @a val.
		 * If there are no elements not less than @a val, end() is returned as the first element.
		 * Similarly if there are no elements greater than @a val, end() is returned as the second element.
		 */
		pair<iterator, iterator>	equal_range( value_type const & val )
		{
			iterator	lower_b = this->lower_bound(val);
			iterator	upper_b = this->upper_bound(val);

			return pair<iterator, iterator>(lower_b, upper_b);
		}

		/**
		 * @brief Returns a range containing all elements with the given @a val in the rb tree.
		 * The range is defined by two const iterators, one pointing to the first element that is not less than @a val and
		 * another pointing to the first element greater than @a val.
		 * Alternatively, the first iterator may be obtained with lower_bound(), and the second with upper_bound().
		 * 
		 * @param val A val value to compare the elements to.
		 * @return A ft::pair containing a pair of const iterators defining the wanted range:
		 * The first pointing to the first element that is not less than @a val and the second pointing to the first element greater than @a val.
		 * If there are no elements not less than @a val, end() is returned as the first element.
		 * Similarly if there are no elements greater than @a val, end() is returned as the second element.
		 */
		pair<const_iterator, const_iterator>	equal_range( value_type const & val ) const
		{
			const_iterator	lower_b = this->lower_bound(val);
			const_iterator	upper_b = this->upper_bound(val);

			return pair<const_iterator, const_iterator>(lower_b, upper_b);
		}

	private:
		static int	_child_direction( pointer node )
		{
			if (node->parent->childs[LEFT] == node)
				return LEFT;
			return RIGHT;
		}

		void	_rotate( pointer src, pointer dst, int direction )
		{
			pointer	parent = dst->parent;

			if (parent->color != PTENODE)
			{
				if (dst == parent->childs[LEFT])
					parent->childs[LEFT] = src;
				else
					parent->childs[RIGHT] = src;
			}
			else
				_root = src;
			src->parent = parent;

			pointer	tmp = src->childs[direction];

			src->childs[direction] = dst;
			dst->parent = src;
			dst->childs[!direction] = tmp;
			if (tmp)
				tmp->parent = dst;

			return;
		}

		void	_balance_erase( pointer node, int direction)
		{
			pointer	parent = node->parent;
			pointer	sibling = parent->childs[!direction];
			if (sibling->color == REDNODE)
			{
				this->_rotate(sibling, parent, direction);
				parent->color = REDNODE;
				sibling->color = BLACKNODE;
				this->_balance_erase(node, direction);
				return;
			}

			pointer	close_nephew = sibling->childs[direction];
			if (close_nephew && close_nephew->color == REDNODE)
			{
				this->_rotate(close_nephew, sibling, !direction);
				ft::swap<pointer>(close_nephew, sibling);
				sibling->color = BLACKNODE;
				sibling->childs[!direction]->color = REDNODE;
			}

			pointer	distant_nephew = sibling->childs[!direction];
			if (distant_nephew && distant_nephew->color == REDNODE)
			{
				this->_rotate(sibling, parent, direction);
				sibling->color = parent->color;
				parent->color = BLACKNODE;
				distant_nephew->color = BLACKNODE;
				return;
			}

			if (parent->color == REDNODE)
			{
				sibling->color = REDNODE;
				parent->color = BLACKNODE;
				return;
			}

			sibling->color = REDNODE;
			if (parent->parent->color != PTENODE)
				this->_balance_erase(parent, rb_tree::_child_direction(parent));

			return;
		}

		void	_balance_insert( pointer node )
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

			int	direction = rb_tree::_child_direction(parent);
			pointer uncle = grandparent->childs[!direction];
			if (!uncle || uncle->color == BLACKNODE)
			{
				if (node == parent->childs[!direction])
				{
					this->_rotate(node, parent, direction);
					ft::swap<pointer>(node, parent);
				}

				this->_rotate(parent, grandparent, !direction);
				parent->color = BLACKNODE;
				grandparent->color = REDNODE;
			}
			else
			{
				parent->color = BLACKNODE;
				uncle->color = BLACKNODE;
				grandparent->color = REDNODE;
				this->_balance_insert(grandparent);
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

		pointer	_dup( const_pointer const src, pointer const parent )
		{
			if (!src)
				return NULL;

			pointer	dst = _alloc.allocate(1LU);
			_alloc.construct(dst, *src);
			dst->parent = parent;
			dst->childs[LEFT] = this->_dup(src->childs[LEFT], dst);
			dst->childs[RIGHT] = this->_dup(src->childs[RIGHT], dst);

			return dst;
		}

		static void	_swap_value_node_parent( pointer parent, pointer child )
		{
			int	direction = rb_tree::_child_direction(child);

			if (parent->parent->color != PTENODE)
				parent->parent->childs[rb_tree::_child_direction(parent)] = child;
			if (parent->childs[!direction])
				parent->childs[!direction]->parent = child;
			if (child->childs[LEFT])
				child->childs[LEFT]->parent = parent;
			if (child->childs[RIGHT])
				child->childs[RIGHT]->parent = parent;

			child->parent = parent->parent;
			parent->parent = child;
			parent->childs[direction] = child->childs[direction];
			child->childs[direction] = parent;
			ft::swap<pointer>(parent->childs[!direction], child->childs[!direction]);

			ft::swap<int>(parent->color, child->color);

			return;
		}

		static void	_relink_before_swap( pointer src, pointer dst )
		{
			if (src->parent->color != PTENODE)
				src->parent->childs[rb_tree::_child_direction(src)] = dst;
			if (src->childs[LEFT])
				src->childs[LEFT]->parent = dst;
			if (src->childs[RIGHT])
				src->childs[RIGHT]->parent = dst;
			
			return;
		}

		static void	_swap_value_node( pointer nodeL, pointer nodeR )
		{
			if (nodeL->parent == nodeR)
				rb_tree::_swap_value_node_parent(nodeR, nodeL);
			else if (nodeR->parent == nodeL)
				rb_tree::_swap_value_node_parent(nodeL, nodeR);
			else
			{
				rb_tree::_relink_before_swap(nodeL, nodeR);
				rb_tree::_relink_before_swap(nodeR, nodeL);
				ft::swap<pointer>(nodeL->parent, nodeR->parent);
				ft::swap<pointer>(nodeL->childs[LEFT], nodeR->childs[LEFT]);
				ft::swap<pointer>(nodeL->childs[RIGHT], nodeR->childs[RIGHT]);
				ft::swap<int>(nodeL->color, nodeR->color);
			}
			return;
		}
	};

/**
 * @brief Checks if the contents of @a lhs and @a rhs are equal, that is,
 * they have the same number of elements and each element in @a lhs compares equal with the element in @a rhs at the same position.
 */
template <class _T, class _Compare, class _Alloc>
bool	operator==( rb_tree<_T, _Compare, _Alloc> const & lhs, rb_tree<_T, _Compare, _Alloc> const & rhs )
{
	if (lhs.size() != rhs.size())
		return false;

	return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class _T, class _Compare, class _Alloc>
bool	operator!=( rb_tree<_T, _Compare, _Alloc> const & lhs, rb_tree<_T, _Compare, _Alloc> const & rhs )
{
	return !(lhs == rhs);
}

/**
 * @brief Compares the contents of @a lhs and @a rhs lexicographically.
 * The comparison is performed by a function equivalent to ft::lexicographical_compare.
 * This comparison ignores the rb tree's ordering Compare (compare_type).
 */
template <class _T, class _Compare, class _Alloc>
bool	operator<( rb_tree<_T, _Compare, _Alloc> const & lhs, rb_tree<_T, _Compare, _Alloc> const & rhs )
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class _T, class _Compare, class _Alloc>
bool	operator<=( rb_tree<_T, _Compare, _Alloc> const & lhs, rb_tree<_T, _Compare, _Alloc> const & rhs )
{
	return !(rhs < lhs);
}

template <class _T, class _Compare, class _Alloc>
bool	operator>( rb_tree<_T, _Compare, _Alloc> const & lhs, rb_tree<_T, _Compare, _Alloc> const & rhs )
{
	return rhs < lhs;
}

template <class _T, class _Compare, class _Alloc>
bool	operator>=( rb_tree<_T, _Compare, _Alloc> const & lhs, rb_tree<_T, _Compare, _Alloc> const & rhs )
{
	return !(lhs < rhs);
}

/**
 * @brief Specializes the ft::swap algorithm for ft::rb_tree. Swaps the contents of @a lhs and @a rhs. Calls lhs.swap(rhs).
 */
template <class _T, class _Compare, class _Alloc>
void	swap( rb_tree<_T, _Compare, _Alloc> &lhs, rb_tree<_T, _Compare, _Alloc> &rhs )
{
	lhs.swap(rhs);
	return;
}

}

#endif
