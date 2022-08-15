#include <iostream>
#include <iterator>
#include <vector>
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

inline static bool	__derefence_operator( void )
{
	typedef std::string::iterator	it_string;

	std::string	str("abcdef");
	it_string	it_string_begin = str.begin();
	it_string	it_string_middle = str.begin() + 2;
	it_string	it_string_end = str.end();

	std::reverse_iterator<it_string>	std_string_begin(it_string_begin);
	std::reverse_iterator<it_string>	std_string_middle(it_string_middle);
	std::reverse_iterator<it_string>	std_string_end(it_string_end);

	ft::reverse_iterator<it_string>	ft_string_begin(it_string_begin);
	ft::reverse_iterator<it_string>	ft_string_middle(it_string_middle);
	ft::reverse_iterator<it_string>	ft_string_end(it_string_end);

	if (*std_string_begin != *ft_string_begin ||
		*std_string_middle != *ft_string_middle ||
		*std_string_end	!= *ft_string_end)
		return false;

	typedef std::vector<int>::iterator	it_vector;

	std::vector<int>	v;
	for (int i = 0; i < 10; i++)
		v.push_back(i);

	it_vector	it_vector_middle = v.begin() + 4;
	it_vector	it_vector_end = v.end();

	std::reverse_iterator<it_vector>	std_vector_middle(it_vector_middle);
	std::reverse_iterator<it_vector>	std_vector_end(it_vector_end);

	ft::reverse_iterator<it_vector>	ft_vector_middle(it_vector_middle);
	ft::reverse_iterator<it_vector>	ft_vector_end(it_vector_end);

	if (*std_vector_middle != *ft_vector_middle ||
		*std_vector_end	!= *ft_vector_end)
		return false;

	return true;
}

void	test_reverse_iterator( void )
{
	t_sub_test	arr[] = {
		{__default_constructor, "default constructor"},
		{__initialization_constructor, "init constructor"},
		{__copy_constructor, "copy constructor"},
		{__base, "base"},
		{__derefence_operator, "operator*"},
		{NULL, ""}
	};

	run_sub_tests(arr);
}
