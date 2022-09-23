#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	protected:

		Container	_c;

	public:

		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;

		/**
		 * @brief Constructs a stack container adaptor object.
		 * 
		 * @param ctnr A container object.
		 */
		explicit stack (const container_type& ctnr = container_type()): _c(ctnr)
		{
			return;
		}

		/**
		 * @brief Returns whether the stack is empty: i.e. whether its size is zero.
		 * 
		 * @return true if the underlying container's size is 0, false otherwise.
		 */
		bool	empty( void ) const
		{
			return _c.empty();
		}

		/**
		 * @brief Returns the number of elements in the stack.
		 */
		size_type	size( void ) const
		{
			return _c.size();
		}

		/**
		 * @brief Returns a reference to the top element in the stack.
		 * Since stacks are last-in first-out containers, the top element is the last element inserted into the stack.
		 * This member function effectively calls member back of the underlying container object.
		 */
		value_type&	top( void )
		{
			return _c.back();
		}

		/**
		 * @brief Returns a const reference to the top element in the stack.
		 * Since stacks are last-in first-out containers, the top element is the last element inserted into the stack.
		 * This member function effectively calls member back of the underlying container object.
		 */
		value_type const &	top( void ) const
		{
			return _c.back();
		}

		/**
		 * @brief Inserts a new element at the top of the stack, above its current top element.
		 * The content of this new element is initialized to a copy of @a val.
		 * This member function effectively calls the member function push_back of the underlying container object.
		 * 
		 * @param val Value to which the inserted element is initialized.
		 */
		void	push(value_type const & val)
		{
			_c.push_back(val);
		}

		/**
		 * @brief Removes the element on top of the stack, effectively reducing its size by one.
		 * The element removed is the latest element inserted into the stack, whose value can be retrieved by calling member stack::top.
		 * This calls the removed element's destructor.
		 * This member function effectively calls the member function pop_back of the underlying container object.
		 */
		void	pop( void )
		{
			_c.pop_back();
		}

		template <class T, class Container>
		friend bool	operator==(stack<T, Container> const &lhs, stack<T, Container> const &rhs);

		template <class T, class Container>
		friend bool	operator!=(stack<T, Container> const &lhs, stack<T, Container> const &rhs);
		
		template <class T, class Container>
		friend bool	operator<(stack<T, Container> const &lhs, stack<T, Container> const &rhs);
		
		template <class T, class Container>
		friend bool	operator<=(stack<T, Container> const &lhs, stack<T, Container> const &rhs);
		
		template <class T, class Container>
		friend bool	operator>(stack<T, Container> const &lhs, stack<T, Container> const &rhs);
		
		template <class T, class Container>
		friend bool	operator>=(stack<T, Container> const &lhs, stack<T, Container> const &rhs);

	};

	/**
	 * @brief Performs the appropriate comparison operation between @a lhs and @a rhs.
	 * Each of these operator overloads calls the same operator on the underlying container objects.
	 * 
	 * @param lhs A stack object with the same type and container as @a rhs.
	 * @param rhs A stack object with the same type and container as @a lhs.
	 * @return true if the condition holds, and false otherwise.
	 */

	template <class T, class Container>
	bool	operator==(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
	{
		return lhs._c == rhs._c;
	}

	template <class T, class Container>
	bool	operator!=(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
	{
		return lhs._c != rhs._c;
	}
	
	template <class T, class Container>
	bool	operator<(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
	{
		return lhs._c < rhs._c;
	}
	
	template <class T, class Container>
	bool	operator<=(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
	{
		return lhs._c <= rhs._c;
	}
	
	template <class T, class Container>
	bool	operator>(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
	{
		return lhs._c > rhs._c;
	}
	
	template <class T, class Container>
	bool	operator>=(stack<T, Container> const &lhs, stack<T, Container> const &rhs)
	{
		return lhs._c >= rhs._c;
	}
	
}

#endif
