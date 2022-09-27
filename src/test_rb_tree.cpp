#include "tests_define.hpp"
#include "rb_tree.hpp"

inline static bool	__default_constructor( void )
{
	ft::rb_tree<int>	tree;

	if (tree.size() || !tree.empty())
		return false;

	tree.clear();
	return true;
}

inline static bool	__begin( void )
{
	ft::rb_tree<int>	tree;

	tree.insert(10);
	tree.insert(1);
	tree.insert(20);
	tree.insert(0);
	tree.insert(42);

	ft::rb_tree<int>::iterator	it = tree.begin();
	ft::rb_tree<int>::const_iterator	cit = tree.begin();
	if (*it != 0 || *cit != 0)
		return false;
	return true;
}

inline static bool	__end( void )
{
	ft::rb_tree<int>	tree;

	tree.insert(10);
	tree.insert(1);
	tree.insert(20);
	tree.insert(0);
	tree.insert(42);

	ft::rb_tree<int>::iterator	it = tree.end();
	--it;
	ft::rb_tree<int>::const_iterator	cit(it);
	if (*it != 42 || *cit != 42)
		return false;
	return true;
}

inline static bool	__insert_single_element( void )
{
	ft::rb_tree<int>	tree;
	ft::pair<ft::rb_tree<int>::iterator, bool>	ret;

	ret = tree.insert(10);
	if (ret.second == false || *ret.first != 10 || tree._validity_check() == false)
		return false;
	ret = tree.insert(1);
	if (ret.second == false || *ret.first != 1 || tree._validity_check() == false)
		return false;
	ret = tree.insert(20);
	if (ret.second == false || *ret.first != 20 || tree._validity_check() == false)
		return false;
	ret = tree.insert(0);
	if (ret.second == false || *ret.first != 0 || tree._validity_check() == false)
		return false;
	ret = tree.insert(42);
	if (ret.second == false || *ret.first != 42 || tree._validity_check() == false)
		return false;

	ret = tree.insert(42);
	if (ret.second == true || *ret.first != 42 || tree._validity_check() == false)
		return false;

	if (tree.size() != 5 || tree.empty() == true)
		return false;
	return true;
}

void	test_rb_tree( void )
{
	t_sub_test	arr[] = {
		{__default_constructor, "constructor (default)"},
		{__begin, "begin"},
		{__end, "end"},
		{__insert_single_element, "insert (single element)"},
		{NULL, ""}
	};

	run_sub_tests(arr);
	return;
}
