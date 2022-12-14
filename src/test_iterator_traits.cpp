#include <string>
#include <vector>
#include <iostream>
#include "iterator.hpp"
#include "tests_define.hpp"

inline static bool	__iterator( void )
{
	char	c = 0;
	NAMESPACE::iterator_traits<std::string::iterator>::difference_type		str_d;
	NAMESPACE::iterator_traits<std::string::iterator>::value_type			str_v;
	NAMESPACE::iterator_traits<std::string::iterator>::pointer				str_p;
	NAMESPACE::iterator_traits<std::string::iterator>::reference			str_r = c;
	NAMESPACE::iterator_traits<std::string::iterator>::iterator_category	str_i;

	NAMESPACE::iterator_traits<std::vector<char>::iterator>::difference_type	vec_d;
	NAMESPACE::iterator_traits<std::vector<char>::iterator>::value_type			vec_v;
	NAMESPACE::iterator_traits<std::vector<char>::iterator>::pointer			vec_p;
	NAMESPACE::iterator_traits<std::vector<char>::iterator>::reference			vec_r = c;
	NAMESPACE::iterator_traits<std::vector<char>::iterator>::iterator_category	vec_i;
	return true;
}

inline static bool	__pointer( void )
{
	char	c = 0;
	NAMESPACE::iterator_traits<char *>::difference_type		c_d;
	NAMESPACE::iterator_traits<char *>::value_type			c_v;
	NAMESPACE::iterator_traits<char *>::pointer				c_p;
	NAMESPACE::iterator_traits<char *>::reference			c_r = c;
	NAMESPACE::iterator_traits<char *>::iterator_category	c_i;

	int	i = 0;
	NAMESPACE::iterator_traits<int *>::difference_type		i_d;
	NAMESPACE::iterator_traits<int *>::value_type			i_v;
	NAMESPACE::iterator_traits<int *>::pointer				i_p;
	NAMESPACE::iterator_traits<int *>::reference			i_r = i;
	NAMESPACE::iterator_traits<int *>::iterator_category	i_i;
	return true;
}

inline static bool	__pointer_const_value( void )
{
	char const	c = 0;
	NAMESPACE::iterator_traits<char const *>::difference_type	c_d;
	NAMESPACE::iterator_traits<char const *>::value_type		c_v;
	NAMESPACE::iterator_traits<char const *>::pointer			c_p;
	NAMESPACE::iterator_traits<char const *>::reference			c_r = c;
	NAMESPACE::iterator_traits<char const *>::iterator_category	c_i;

	int const	i = 0;
	NAMESPACE::iterator_traits<int const *>::difference_type	i_d;
	NAMESPACE::iterator_traits<int const *>::value_type			i_v;
	NAMESPACE::iterator_traits<int const *>::pointer			i_p;
	NAMESPACE::iterator_traits<int const *>::reference			i_r = i;
	NAMESPACE::iterator_traits<int const *>::iterator_category	i_i;
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
