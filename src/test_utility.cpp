#include "tests_define.hpp"
#include "utility.hpp"
#include <typeinfo>
#include <string>
#include <vector>

// DBG
#include <utility>
#include <iostream>

static int				nb = 42;
static char				c = '*';
static std::string		str("Artus");
static std::vector<int>	vec(6, 7);

inline static bool	__pair_default_constructor( void )
{
	std::string									s;
	std::vector<int>							v;
	ft::pair< std::string, std::vector<int> >	pr;

	if (typeid(ft::pair< std::string, std::vector<int> >::first_type) != typeid(s) ||
		typeid(ft::pair< std::string, std::vector<int> >::second_type) != typeid(v))
		return false;
	else if(typeid(pr.first) != typeid(s) || typeid(pr.second) != typeid(v))
		return false;
	else if (pr.first != s || pr.second != v)
		return false;

	return true;
}

inline static bool	__pair_initialization_constructor( void )
{
	ft::pair<int, char>	pr0(nb, c);

	if (typeid(ft::pair<int, char>::first_type) != typeid(nb) ||
		typeid(ft::pair<int, char>::second_type) != typeid(c))
		return false;
	else if(typeid(pr0.first) != typeid(nb) || typeid(pr0.second) != typeid(c))
		return false;
	else if (pr0.first != nb || pr0.second != c)
		return false;

	ft::pair< std::string, std::vector<int> >	pr1(str, vec);

	if (typeid(ft::pair< std::string, std::vector<int> >::first_type) != typeid(str) ||
		typeid(ft::pair< std::string, std::vector<int> >::second_type) != typeid(vec))
		return false;
	else if(typeid(pr1.first) != typeid(str) || typeid(pr1.second) != typeid(vec))
		return false;
	else if (pr1.first != str || pr1.second != vec)
		return false;

	return true;
}

inline static bool	__pair_copy_constructor( void )
{
	ft::pair<int, char>	pr0(nb, c);
	ft::pair<int, char>	pr1(pr0);

	if(typeid(pr0.first) != typeid(pr1.first) || typeid(pr0.second) != typeid(pr1.second))
		return false;
	else if (pr0.first != pr1.first || pr0.second != pr1.second)
		return false;

	ft::pair< std::string, std::vector<int> >	p2(str, vec);
	ft::pair< std::string, std::vector<int> >	p3(p2);

	if(typeid(p2.first) != typeid(p3.first) || typeid(p2.second) != typeid(p3.second))
		return false;
	else if (p2.first != p3.first || p2.second != p3.second)
		return false;

	return true;
}

inline static bool	__pair_assignment_operator( void )
{
	ft::pair<int,char>	pr0(nb,c);
	ft::pair<int,char>	pr1;

	pr1 = pr0;

	if(typeid(pr0.first) != typeid(pr1.first) || typeid(pr0.second) != typeid(pr1.second))
		return false;
	else if (pr0.first != pr1.first || pr0.second != pr1.second)
		return false;

	ft::pair< std::string, std::vector<int> >	p2(str, vec);
	ft::pair< std::string, std::vector<int> >	p3;

	p3 = p2;

	if(typeid(p2.first) != typeid(p3.first) || typeid(p2.second) != typeid(p3.second))
		return false;
	else if (p2.first != p3.first || p2.second != p3.second)
		return false;

	return true;
}

inline static bool	__pair_relational_operators( void )
{
	std::pair<int,char>	std_p0(nb,c);
	std::pair<int,char>	std_p1(nb,c);
	ft::pair<int,char>	ft_p0(nb,c);
	ft::pair<int,char>	ft_p1(nb,c);

	if (std::operator==(std_p0, std_p1) != ft::operator==(ft_p0, ft_p1) ||
		std::operator!=(std_p0, std_p1) != ft::operator!=(ft_p0, ft_p1) ||
		std::operator<(std_p0, std_p1) != ft::operator<(ft_p0, ft_p1) ||
		std::operator<=(std_p0, std_p1) != ft::operator<=(ft_p0, ft_p1) ||
		std::operator>(std_p0, std_p1) != ft::operator>(ft_p0, ft_p1) ||
		std::operator>=(std_p0, std_p1) != ft::operator>=(ft_p0, ft_p1))
		return false;

	std_p0.first += 1;
	std_p0.second += 1;
	ft_p0.first += 1;
	ft_p0.second += 1;

	if (std::operator==(std_p0, std_p1) != ft::operator==(ft_p0, ft_p1) ||
		std::operator!=(std_p0, std_p1) != ft::operator!=(ft_p0, ft_p1) ||
		std::operator<(std_p0, std_p1) != ft::operator<(ft_p0, ft_p1) ||
		std::operator<=(std_p0, std_p1) != ft::operator<=(ft_p0, ft_p1) ||
		std::operator>(std_p0, std_p1) != ft::operator>(ft_p0, ft_p1) ||
		std::operator>=(std_p0, std_p1) != ft::operator>=(ft_p0, ft_p1))
		return false;
	
	std_p1.first += 3;
	std_p1.second += 3;
	ft_p1.first += 3;
	ft_p1.second += 3;

	if (std::operator==(std_p0, std_p1) != ft::operator==(ft_p0, ft_p1) ||
		std::operator!=(std_p0, std_p1) != ft::operator!=(ft_p0, ft_p1) ||
		std::operator<(std_p0, std_p1) != ft::operator<(ft_p0, ft_p1) ||
		std::operator<=(std_p0, std_p1) != ft::operator<=(ft_p0, ft_p1) ||
		std::operator>(std_p0, std_p1) != ft::operator>(ft_p0, ft_p1) ||
		std::operator>=(std_p0, std_p1) != ft::operator>=(ft_p0, ft_p1))
		return false;
	
	return true;
}

void	test_utility( void )
{
	t_sub_test	arr[] = {
		{__pair_default_constructor, "pair default constructor"},
		{__pair_initialization_constructor, "pair init constructor"},
		{__pair_copy_constructor, "pair copy constructor"},
		{__pair_assignment_operator, "pair operator="},
		{__pair_relational_operators, "pair operators ==, !=, <, <=, >, >="},
		{NULL, ""}
	};

	run_sub_tests(arr);
}
