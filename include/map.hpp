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
		explicit map( key_compare const & comp = key_compare(),
					  allocator_type const & alloc = allocator_type() ): _tree(comp, alloc)
		{
			return;
		}

		~map( void )
		{
			return;
		}

	};
}

#endif
