#include <string>
#include <vector>
#include <iostream>
#include "iterator.hpp"
#include "tests_define.hpp"

bool	__iterator( void )
{
	char	c = 0;
	ft::iterator_traits<std::string::iterator>::difference_type		str_d;
	ft::iterator_traits<std::string::iterator>::value_type			str_v;
	ft::iterator_traits<std::string::iterator>::pointer				str_p;
	ft::iterator_traits<std::string::iterator>::reference			str_r = c;
	ft::iterator_traits<std::string::iterator>::iterator_category	str_i;

	ft::iterator_traits<std::vector<char>::iterator>::difference_type	vec_d;
	ft::iterator_traits<std::vector<char>::iterator>::value_type		vec_v;
	ft::iterator_traits<std::vector<char>::iterator>::pointer			vec_p;
	ft::iterator_traits<std::vector<char>::iterator>::reference			vec_r = c;
	ft::iterator_traits<std::vector<char>::iterator>::iterator_category	vec_i;
	return true;
}

bool	__pointer( void )
{
	char	c = 0;
	ft::iterator_traits<char *>::difference_type	c_d;
	ft::iterator_traits<char *>::value_type			c_v;
	ft::iterator_traits<char *>::pointer			c_p;
	ft::iterator_traits<char *>::reference			c_r = c;
	ft::iterator_traits<char *>::iterator_category	c_i;

	int	i = 0;
	ft::iterator_traits<int *>::difference_type		i_d;
	ft::iterator_traits<int *>::value_type			i_v;
	ft::iterator_traits<int *>::pointer				i_p;
	ft::iterator_traits<int *>::reference			i_r = i;
	ft::iterator_traits<int *>::iterator_category	i_i;
	return true;
}

bool	__pointer_const_value( void )
{
	char const	c = 0;
	ft::iterator_traits<char const *>::difference_type		c_d;
	ft::iterator_traits<char const *>::value_type			c_v;
	ft::iterator_traits<char const *>::pointer				c_p;
	ft::iterator_traits<char const *>::reference			c_r = c;
	ft::iterator_traits<char const *>::iterator_category	c_i;

	int const	i = 0;
	ft::iterator_traits<int const *>::difference_type		i_d;
	ft::iterator_traits<int const *>::value_type			i_v;
	ft::iterator_traits<int const *>::pointer				i_p;
	ft::iterator_traits<int const *>::reference				i_r = i;
	ft::iterator_traits<int const *>::iterator_category		i_i;
	return true;
}

void	test_iterator_traits( void )
{
	t_sub_test	arr[] = {
		{__iterator, "template iterator"},
		{__pointer, "template pointer"},
		{__pointer_const_value, "template pointer on constant value"},
		{NULL, ""}
	};

	run_sub_tests(arr);
}
