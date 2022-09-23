#ifndef RB_TREE_ITERATOR_HPP
# define RB_TREE_ITERATOR_HPP

#include "iterator.hpp"

namespace __ft
{
	template < class T >
	class __rb_tree_iterator
	{
	protected:
		T	_current;

		typedef ft::iterator_traits<T>					traits_type;

	public:
		typedef T										iterator_type;
		typedef typename traits_type::iterator_category	iterator_category;
		typedef typename traits_type::value_type  		value_type;
		typedef typename traits_type::difference_type 	difference_type;
		typedef typename traits_type::reference 		reference;
		typedef typename traits_type::pointer   		pointer;

		__rb_tree_iterator(): _current(iterator_type())
		{
			return;
		}

		explicit __rb_tree_iterator(const iterator_type& it): _current(it)
		{
			return;
		}

		template <typename _T>
		__rb_tree_iterator(__rb_tree_iterator<_T> const & rhs)
			: _current(rhs.base())
		{
			return;
		}

		const iterator_type&	base( void ) const
		{
			return (_current);
		}
	};
}

#endif
