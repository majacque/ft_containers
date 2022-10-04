#ifndef MAP_HPP
# define MAP_HPP

#include "utility.hpp"
#include "rb_tree.hpp"
#include <functional>
#include <memory>

namespace ft
{
	template < typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<rb_node<ft::pair<Key const,T> > > >
	class map
	{
	public:
		typedef Key															key_type;
		typedef T															mapped_type;
		typedef ft::pair<Key const, T>										value_type;
		typedef Compare														key_compare;
		typedef Alloc														allocator_type;

		class value_compare: public std::binary_function<value_type, value_type, bool>
		{
		private:
			friend class map<Key, T, Compare, Alloc>;

		protected:
			key_compare	comp;

			value_compare( key_compare c = key_compare() ): comp(c)
			{
				return;
			}

		public:
			bool	operator()( value_type const & lhs, value_type const & rhs ) const
			{
				return comp(lhs.first, rhs.first);
			}
		};

		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::reference							reference;
		typedef typename allocator_type::const_pointer						const_pointer;
		typedef typename allocator_type::pointer							pointer;
		// typedef __ft::__rb_tree_iterator<const_pointer, const value_type>	const_iterator;
		// typedef __ft::__rb_tree_iterator<pointer, value_type>				iterator;
		typedef typename rb_tree<value_type, value_compare, allocator_type>::const_iterator	const_iterator;
		typedef typename rb_tree<value_type, value_compare, allocator_type>::iterator		iterator;
		typedef reverse_iterator<const_iterator>							const_reverse_iterator;
		typedef reverse_iterator<iterator>									reverse_iterator;

		typedef iterator_traits<iterator>									difference_type;
		typedef size_t														size_type;

	private:
		rb_tree<value_type, value_compare, allocator_type>	_tree;

	public:
		/**************************************************************************/
		/*                               CONSTRUCTOR                              */
		/**************************************************************************/

		/**
		 * @brief Constructs an empty map, with no elements.
		 * 
		 * @param comp Comparison function object to use for all comparisons of keys.
		 * @param alloc Allocator to use for all memory allocations of this map.
		 */
		explicit map( key_compare const & comp = key_compare(),
				allocator_type const & alloc = allocator_type() ): _tree(comp, alloc)
		{
			return;
		}

		/**
		 * @brief Constructs a map with the contents of the range [first, last).
		 * If multiple elements in the range have keys that compare equivalent, it is unspecified which element is inserted.
		 * 
		 * @param first An input iterator to the initial position in a range.
		 * @param last An input iterator to the final position in a range.
		 * @param comp Comparison function object to use for all comparisons of keys.
		 * @param alloc Allocator to use for all memory allocations of this map.
		 */
		template <class InputIterator>
		map( InputIterator first, InputIterator last,
			key_compare const & comp = key_compare(),
			allocator_type const & alloc = allocator_type()): _tree(first, last, comp, alloc)
		{
			return;
		}

		/**
		 * @brief Constructs a map with a copy of each of the elements in @a rhs.
		 * 
		 * @param rhs Another map to be used as source to initialize the elements of the map with.
		 */
		map( map const & rhs ): _tree(rhs._tree)
		{
			return;
		}

		/**************************************************************************/
		/*                               DESTRUCTOR                               */
		/**************************************************************************/

		/**
		 * @brief Destroys the map. This destroys all container elements,
		 * and deallocates all the storage capacity allocated by the map container using its allocator.
		 * Note, that if the elements are pointers, the pointed-to objects are not destroyed.
		 */
		~map( void )
		{
			return;
		}

		/**************************************************************************/
		/*                            MEMBER FUNCTIONS                            */
		/**************************************************************************/

		/**
		 * @brief Assigns new contents to the map, replacing its current content.
		 * 
		 * @param rhs A map of the same type.
		 * @return A reference to the instance.
		 */
		map&	operator=( map const & rhs )
		{
			_tree = rhs._tree;
			return *this;
		}

		// Element access

		/**
		 * @brief Returns a reference to the value that is mapped to a key equivalent to @a key,
		 * performing an insertion if such key does not already exist.
		 * 
		 * @param key The key of the element to find.
		 */
		mapped_type&	operator[]( key_type const & key )
		{
			return _tree.insert(ft::make_pair(key, mapped_type())).first->second;
		}

		// Iterators

		/**
		 * @brief Returns an iterator referring to the first element of the map.
		 * If the map is empty returns an iterator equivalent to @a end().
		 */
		iterator	begin( void )
		{
			return _tree.begin();
		}

		/**
		 * @brief Returns a const iterator referring to the first element of the map.
		 * If the map is empty returns a const iterator equivalent to @a end().
		 */
		const_iterator	begin( void ) const
		{
			return _tree.begin();
		}

		/**
		 * @brief Returns an iterator to the element following the last element of the map.
		 * This element acts as a placeholder; attempting to access it results in undefined behavior.
		 */
		iterator	end( void )
		{
			return _tree.end();
		}

		/**
		 * @brief Returns a const iterator to the element following the last element of the map.
		 * This element acts as a placeholder; attempting to access it results in undefined behavior.
		 */
		const_iterator	end( void ) const
		{
			return _tree.end();
		}

		// Capacity

		/**
		 * @brief Returns whether the map is empty (i.e. whether its size is 0).
		 * 
		 * @return true if the container size is 0, false otherwise.
		 */
		bool	empty( void ) const
		{
			return _tree.empty();
		}

		/**
		 * @brief Returns the number of elements in the map.
		 */
		size_type	size( void ) const
		{
			return _tree.size();
		}

		// Modifiers

		/**
		 * @brief Destroy the map object.
		 */
		void	clear( void )
		{
			_tree.clear();
			return;
		}

		/**
		 * @brief Removes the element at @a position. References and iterators to the erased elements are invalidated.
		 * Other references and iterators are not affected. The iterator @a position must be valid and dereferenceable.
		 * Thus the end() iterator (which is valid, but is not dereferenceable) cannot be used as a value for @a position.
		 * 
		 * @param position An iterator to the element to remove.
		 */
		void	erase( iterator position )
		{
			_tree.erase(position);
			return;
		}

		/**
		 * @brief Removes the element (if one exists) with the key equivalent to @a val.
		 * 
		 * @param key Key value of the element to erase.
		 * @return Number of elements removed (0 or 1).
		 */
		size_type	erase( key_type const & key )
		{
			return _tree.erase(value_type(key, mapped_type()));
		}

		/**
		 * @brief Removes the elements in the range [first; last), which must be a valid range in the map.
		 * 
		 * @param first An iterator to the initial position in a range.
		 * @param last An iterator to the final position in a range.
		 */
		void	erase( iterator first, iterator last )
		{
			_tree.erase(first, last);
			return;
		}

		/**
		 * @brief Inserts element(s) into the map, if the map doesn't already contain an element with an equivalent key.
		 * 
		 * @param val Element value to insert.
		 * @return Returns a pair consisting of an iterator to the inserted element (or to the element that prevented the insertion)
		 * and a bool value set to true if the insertion took place.
		 */
		pair<iterator,bool>	insert( value_type const & val )
		{
			return _tree.insert(val);
		}

		/**
		 * @brief Inserts element(s) into the map, if the map doesn't already contain an element with an equivalent key.
		 * Inserts @a val in the position as close as possible to @a hint.
		 * 
		 * @param hint An iterator used as a suggestion as to where to start the search.
		 * @param val Element value to insert.
		 * @return An iterator to the inserted element, or to the element that prevented the insertion.
		 */
		iterator	insert( iterator hint, value_type const & val )
		{
			return _tree.insert(hint, val);
		}

		/**
		 * @brief Inserts elements, from range [first, last),
		 * into the map if the map doesn't contain an element with an equivalent key.
		 * If multiple elements in the range have keys that compare equivalent, it is unspecified which element is inserted.
		 * 
		 * @param first An input iterator to the initial position in a range.
		 * @param last An input iterator to the final position in a range.
		 */
		template <class InputIterator>
		void	insert( InputIterator first, InputIterator last )
		{
			_tree.insert(first, last);
			return;
		}

		// Lookup

		/**
		 * @brief Returns the number of elements with key that compares equivalent to the specified argument,
		 * which is either 1 or 0 since this map does not allow duplicates.
		 * 
		 * @param key The key of the elements to count.
		 * @return Number of elements with key that compares equivalent to @a key, which is either 1 or 0 for (1).
		 */
		size_type	count( key_type const & key )
		{
			return _tree.count(value_type(key, mapped_type()));
		}

		/**
		 * @brief Finds an element with key equivalent to @a key.
		 * 
		 * @param key Key value of the element to search for.
		 * @return An iterator to the element with a key equivalent to @a key.
		 * If no such element is found, an iterator to end() is returned.
		 */
		iterator	find( key_type const & key )
		{
			return _tree.find(value_type(key, mapped_type()));
		}

		/**
		 * @brief Finds an element with key equivalent to @a key.
		 * 
		 * @param key Key value of the element to search for.
		 * @return A const iterator to the element with a key equivalent to @a key.
		 * If no such element is found, an iterator to end() is returned.
		 */
		const_iterator	find( key_type const & key ) const
		{
			return _tree.find(value_type(key, mapped_type()));
		}

	};
}

#endif
