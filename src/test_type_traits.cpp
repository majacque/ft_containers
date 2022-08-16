#include "tests_define.hpp"
#include "type_traits.hpp"

#include <iostream>

template <typename T>
void	print(typename ft::enable_if<sizeof(T) == sizeof(double), T>::type n)
{
	// std::cout << "double: " << n << "\n";
}

template <typename T>
void	print(typename ft::enable_if<sizeof(T) == sizeof(int), T>::type n)
{
	// std::cout << "int: " << n << "\n";
}

inline static bool	__enable_if( void )
{
	// print<char>("*"); // not compile
	print<int>(42);
	print<double>(42.2);

	return true;
}

void	test_type_traits( void )
{
	t_sub_test	arr[] = {
		{__enable_if, "enable_if"},
		{NULL, ""}
	};

	run_sub_tests(arr);
}
