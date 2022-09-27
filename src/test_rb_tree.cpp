#include "tests_define.hpp"
#include "rb_tree.hpp"

inline static bool	__default_constructor( void )
{
	ft::rb_tree<int>	tree;

	if (tree.size() || !tree.empty())
		return false;

	return true;
}

void	test_rb_tree( void )
{
	t_sub_test	arr[] = {
		{__default_constructor, "constructor (default)"},
		{NULL, ""}
	};

	run_sub_tests(arr);
	return;
}
