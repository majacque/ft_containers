#ifndef MAP_HPP
# define MAP_HPP

namespace ft
{
	template <  typename Key,												// map::key_type
				typename T,													// map::mapped_type
				typename Compare = std::less<Key>,							// map::key_compare
				typename Alloc = std::allocator<std::pair<const Key,T> >	// map::allocator_type
	> class map;
}

#endif
