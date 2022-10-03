#include "tests_define.hpp"
#include "map.hpp"
#include <map>

inline static bool	__default_constructor( void )
{
	ft::map<int, int>	m;
	return true;
}

void	test_map( void )
{
	t_sub_test	arr[] = {
		{NULL, ""}
	};

	run_sub_tests(arr);
	return;
}
