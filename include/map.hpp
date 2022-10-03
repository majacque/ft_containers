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
		 * @brief Construct an empty map.
		 */
		explicit map( key_compare const & comp = key_compare(),
				allocator_type const & alloc = allocator_type() ): _tree(comp, alloc)
		{
			return;
		}

		// TODO range constructor
		/* template <class InputIterator>
		map( InputIterator first, InputIterator last,
			key_compare const & comp = key_compare(),
			allocator_type const & alloc = allocator_type()): _tree(first, last, comp, alloc)
		{
			return;
		} */

		// TODO copy constructor
		/* map( map const & rhs ): _tree(rhs._tree)
		{
			return;
		} */

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
		 * @brief Returns the number of elements in the map.
		 */
		size_type	size( void ) const
		{
			return _tree.size();
		}

		// Modifiers

		// TODO clear
		// void	clear( void );

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

		// TODO insert (hint)
		// iterator	insert( iterator hint, value_type const & x );

		// TODO insert (range)
		/* template <class InputIterator>
		void	insert( InputIterator first, InputIterator last ); */

	};
}

#endif
