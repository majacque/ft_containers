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

	 // REMIND test with base()
	return true;
}

inline static bool	__initialization_constructor( void )
{
	typedef std::string::iterator	it_type;

	std::string	str("abcdef");

	it_type	it = str.begin();
	std::reverse_iterator<it_type>	std_rit(it);
	ft::reverse_iterator<it_type>	ft_rit(it);

	if (sizeof(std_rit) != sizeof(ft_rit)
		|| memcmp(&std_rit, &ft_rit, sizeof(std_rit)))
		return false;

	return true;
}

void	test_reverse_iterator( void )
{
	t_sub_test	arr[] = {
		{__default_constructor, "default constructor"},
		{__initialization_constructor, "init constructor"},
		{NULL, ""}
	};

	run_sub_tests(arr);
}
