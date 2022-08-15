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
	else if (std_rit.base() != ft_rit.base())
		return false;

	return true;
}

inline static bool	__initialization_constructor( void )
{
	typedef std::string::iterator	it_type;

	std::string	str("abcdef");
	it_type	it = str.end();

	std::reverse_iterator<it_type>	std_rit(it);
	ft::reverse_iterator<it_type>	ft_rit(it);

	if (sizeof(std_rit) != sizeof(ft_rit)
		|| memcmp(&std_rit, &ft_rit, sizeof(std_rit)))
		return false;
	else if (std_rit.base() != ft_rit.base())
		return false;

	// REMIND compare with operator*
	return true;
}

inline static bool	__copy_constructor( void )
{
	typedef std::string::iterator	it_type;

	std::string	str("abcdef");
	it_type	it = str.end();
	ft::reverse_iterator<it_type>	ft_rit0(it);

	ft::reverse_iterator<it_type>	ft_rit1(ft_rit0);
	if (sizeof(ft_rit0) != sizeof(ft_rit1)
		|| memcmp(&ft_rit0, &ft_rit1, sizeof(ft_rit0)))
		return false;

	// REMIND compare with operator*
	return true;
}

inline static bool	__base( void )
{
	typedef std::string::iterator	it_type;

	std::string	str("abcdef");
	it_type	it = str.end();

	ft::reverse_iterator<it_type>	ft_rit(it);

	it_type	base = ft_rit.base();
	if (sizeof(it) != sizeof(base)
		|| memcmp(&it, &base, sizeof(it)))
		return false;

	// REMIND compare with operator != or ==
	return true;
}

void	test_reverse_iterator( void )
{
	t_sub_test	arr[] = {
		{__default_constructor, "default constructor"},
		{__initialization_constructor, "init constructor"},
		{__copy_constructor, "copy constructor"},
		{__base, "base"},
		{NULL, ""}
	};

	run_sub_tests(arr);
}
