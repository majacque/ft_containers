#include "tests_define.hpp"
#include "map.hpp"
#include <map>

inline static bool	__default_constructor( void )
{
	ft::map<int, int>	m;
	ft::map<int, int, std::greater<int> >	m1;
	return true;
}

void	test_map( void )
{
	t_sub_test	arr[] = {
		{__default_constructor, "constructor (default)"},
		{NULL, ""}
	};

	run_sub_tests(arr);
	return;
}
