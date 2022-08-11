#include <iostream>
#include <iterator>
#include <string>
#include <cstring>
#include "iterator.hpp"
#include "tests_define.hpp"

inline static bool	__default_constructor( void )
{
	std::reverse_iterator<std::string::iterator>	std_rit;
	ft::reverse_iterator<std::string::iterator>		ft_rit;

	if (sizeof(std_rit) != sizeof(ft_rit)
		|| memcmp(&std_rit, &ft_rit, sizeof(std_rit)))
		return false;

	return true;
}

void	test_reverse_iterator( void )
{
	t_sub_test	arr[] = {
		{__default_constructor, "default constructor"},
		{NULL, ""}
	};

	run_sub_tests(arr);
}
