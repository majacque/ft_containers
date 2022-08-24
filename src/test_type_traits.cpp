#include "tests_define.hpp"
#include "type_traits.hpp"

// #include <iostream>

template <typename T>
void	print(typename ft::enable_if<sizeof(T) == sizeof(double), T>::type )
{
	// std::cout << "double: " << n << "\n";
}

template <typename T>
void	print(typename ft::enable_if<sizeof(T) == sizeof(int), T>::type )
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

inline static bool	__is_integral_( void )
{
	if (ft::is_integral<bool>::value != true ||
		ft::is_integral<char>::value != true ||
		ft::is_integral<wchar_t>::value != true ||
		ft::is_integral<signed char>::value != true ||
		ft::is_integral<short int>::value != true ||
		ft::is_integral<int>::value != true ||
		ft::is_integral<long int>::value != true ||
		ft::is_integral<unsigned char>::value != true ||
		ft::is_integral<unsigned short int>::value != true ||
		ft::is_integral<unsigned int>::value != true ||
		ft::is_integral<unsigned long int>::value != true)
		return false;

	return true;
}

void	test_type_traits( void )
{
	t_sub_test	arr[] = {
		{__enable_if, "enable_if"},
		{__is_integral_, "is_integral"},
		{NULL, ""}
	};

	run_sub_tests(arr);
}
