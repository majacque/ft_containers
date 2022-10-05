#include "tests_define.hpp"
#include "utility.hpp"
#include <utility>
#include <typeinfo>
#include <string>
#include <vector>

static int				nb = 42;
static char				c = '*';
static std::string		str("Artus");
static std::vector<int>	vec(6, 7);

inline static bool	__pair_default_constructor( void )
{
	std::string									s;
	std::vector<int>							v;
	NAMESPACE::pair< std::string, std::vector<int> >	pr;

	if (typeid(NAMESPACE::pair< std::string, std::vector<int> >::first_type) != typeid(s) ||
		typeid(NAMESPACE::pair< std::string, std::vector<int> >::second_type) != typeid(v))
		return false;
	else if(typeid(pr.first) != typeid(s) || typeid(pr.second) != typeid(v))
		return false;
	else if (pr.first != s || pr.second != v)
		return false;

	return true;
}

inline static bool	__pair_initialization_constructor( void )
{
	NAMESPACE::pair<int, char>	pr0(nb, c);

	if (typeid(NAMESPACE::pair<int, char>::first_type) != typeid(nb) ||
		typeid(NAMESPACE::pair<int, char>::second_type) != typeid(c))
		return false;
	else if(typeid(pr0.first) != typeid(nb) || typeid(pr0.second) != typeid(c))
		return false;
	else if (pr0.first != nb || pr0.second != c)
		return false;

	NAMESPACE::pair< std::string, std::vector<int> >	pr1(str, vec);

	if (typeid(NAMESPACE::pair< std::string, std::vector<int> >::first_type) != typeid(str) ||
		typeid(NAMESPACE::pair< std::string, std::vector<int> >::second_type) != typeid(vec))
		return false;
	else if(typeid(pr1.first) != typeid(str) || typeid(pr1.second) != typeid(vec))
		return false;
	else if (pr1.first != str || pr1.second != vec)
		return false;

	return true;
}

inline static bool	__pair_copy_constructor( void )
{
	NAMESPACE::pair<int, char>	pr0(nb, c);
	NAMESPACE::pair<int, char>	pr1(pr0);

	if(typeid(pr0.first) != typeid(pr1.first) || typeid(pr0.second) != typeid(pr1.second))
		return false;
	else if (pr0.first != pr1.first || pr0.second != pr1.second)
		return false;

	NAMESPACE::pair< std::string, std::vector<int> >	p2(str, vec);
	NAMESPACE::pair< std::string, std::vector<int> >	p3(p2);

	if(typeid(p2.first) != typeid(p3.first) || typeid(p2.second) != typeid(p3.second))
		return false;
	else if (p2.first != p3.first || p2.second != p3.second)
		return false;

	return true;
}

inline static bool	__pair_assignment_operator( void )
{
	NAMESPACE::pair<int,char>	pr0(nb,c);
	NAMESPACE::pair<int,char>	pr1;

	pr1 = pr0;

	if(typeid(pr0.first) != typeid(pr1.first) || typeid(pr0.second) != typeid(pr1.second))
		return false;
	else if (pr0.first != pr1.first || pr0.second != pr1.second)
		return false;

	NAMESPACE::pair< std::string, std::vector<int> >	p2(str, vec);
	NAMESPACE::pair< std::string, std::vector<int> >	p3;

	p3 = p2;

	if(typeid(p2.first) != typeid(p3.first) || typeid(p2.second) != typeid(p3.second))
		return false;
	else if (p2.first != p3.first || p2.second != p3.second)
		return false;

	return true;
}

inline static bool	__pair_relational_operators( void )
{
	NAMESPACE::pair<int, char>	p0(nb, c);
	NAMESPACE::pair<int, char>	p1(nb, c);

	if ((p0 == p1) != true || (p0 != p1) != false ||
		(p0 <= p1) != true || (p0 < p1) != false ||
		(p0 >= p1) != true || (p0 > p1) != false)
		return false;

	p0.first -= 1;

	if ((p0 == p1) != false || (p0 != p1) != true ||
		(p0 <= p1) != true || (p0 < p1) != true ||
		(p0 >= p1) != false || (p0 > p1) != false)
		return false;

	p0.first += 1;
	p0.second -= 1;

	if ((p0 == p1) != false || (p0 != p1) != true ||
		(p0 <= p1) != true || (p0 < p1) != true ||
		(p0 >= p1) != false || (p0 > p1) != false)
		return false;

	p0.second += 2;

	if ((p0 == p1) != false || (p0 != p1) != true ||
		(p0 <= p1) != false || (p0 < p1) != false ||
		(p0 >= p1) != true || (p0 > p1) != true)
		return false;

	p0.second -= 1;
	p0.first += 1;

	if ((p0 == p1) != false || (p0 != p1) != true ||
		(p0 <= p1) != false || (p0 < p1) != false ||
		(p0 >= p1) != true || (p0 > p1) != true)
		return false;

	return true;
}

inline static bool	__make_pair( void )
{
	// template explicitly declared
	NAMESPACE::pair<int,char>	p0(nb,c);
	NAMESPACE::pair<int,char>	p1 = NAMESPACE::make_pair<int,char>(nb,c);

	if (p0 != p1)
		return false;

	// template implicitly deduced
	NAMESPACE::pair<std::string, std::vector<int> >	p2(str,vec);
	NAMESPACE::pair<std::string, std::vector<int> >	p3 = NAMESPACE::make_pair(str,vec);

	if (p2 != p3)
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
		{__make_pair, "make_pair"},
		{NULL, ""}
	};

	run_sub_tests(arr);
}
