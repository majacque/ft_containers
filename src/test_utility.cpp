#include "tests_define.hpp"
#include "utility.hpp"
#include <typeinfo>
#include <string>
#include <vector>

// DBG
#include <utility>
#include <iostream>

inline static bool	__pair_default_constructor( void )
{
	std::string									s;
	std::vector<int>							v;
	ft::pair< std::string, std::vector<int> >	p;

	if (typeid(ft::pair< std::string, std::vector<int> >::first_type) != typeid(s) ||
		typeid(ft::pair< std::string, std::vector<int> >::second_type) != typeid(v))
		return false;
	else if(typeid(p.first) != typeid(s) || typeid(p.second) != typeid(v))
		return false;
	else if (p.first != s || p.second != v)
		return false;

	return true;
}

inline static bool	__pair_initialization_constructor( void )
{
	int		i = 42;
	char	c = '*';
	ft::pair<int, char>	p0(i, c);

	if (typeid(ft::pair<int, char>::first_type) != typeid(i) ||
		typeid(ft::pair<int, char>::second_type) != typeid(c))
		return false;
	else if(typeid(p0.first) != typeid(i) || typeid(p0.second) != typeid(c))
		return false;
	else if (p0.first != i || p0.second != c)
		return false;

	std::string									s("Artus");
	std::vector<int>							v(6, 7);
	ft::pair< std::string, std::vector<int> >	p1(s, v);

	if (typeid(ft::pair< std::string, std::vector<int> >::first_type) != typeid(s) ||
		typeid(ft::pair< std::string, std::vector<int> >::second_type) != typeid(v))
		return false;
	else if(typeid(p1.first) != typeid(s) || typeid(p1.second) != typeid(v))
		return false;
	else if (p1.first != s || p1.second != v)
		return false;

	return true;
}

void	test_utility( void )
{
	t_sub_test	arr[] = {
		{__pair_default_constructor, "pair default constructor"},
		{__pair_initialization_constructor, "pair init constructor"},
		{NULL, ""}
	};

	run_sub_tests(arr);
}
