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

inline static bool	__range_constructor( void )
{
	ft::rb_tree<int>	tree;

	tree.insert(10);
	tree.insert(2);
	tree.insert(20);
	tree.insert(1);
	tree.insert(42);
	tree.insert(43);

	ft::rb_tree<int>	treecp(tree.begin(), tree.end());
	if (treecp._validity_check() == false)
		return false;

	ft::rb_tree<int>::iterator	it = tree.begin();
	for (ft::rb_tree<int>::iterator first = treecp.begin(); first != treecp.end(); ++first)
	{
		if (*first != *it)
			return false;
		++it;
	}

	return true;
}

inline static bool	__copy_constructor( void )
{
	ft::rb_tree<int>	tree;

	tree.insert(10);
	tree.insert(2);
	tree.insert(20);
	tree.insert(1);
	tree.insert(42);
	tree.insert(43);

	ft::rb_tree<int>	treecp(tree);
	if (treecp._validity_check() == false || tree.size() != treecp.size())
		return false;

	ft::rb_tree<int>::iterator	it = tree.begin();
	for (ft::rb_tree<int>::iterator first = treecp.begin(); first != treecp.end(); ++first)
	{
		if (*first != *it)
			return false;
		++it;
	}

	return true;
}

inline static bool	__copy_assignement_operator( void )
{
	ft::rb_tree<int>	tree;

	tree.insert(10);
	tree.insert(2);
	tree.insert(20);
	tree.insert(1);
	tree.insert(42);
	tree.insert(43);

	ft::rb_tree<int>	treecp;

	treecp.insert(101);
	treecp.insert(1010);
	treecp.insert(10101);

	treecp = tree;

	ft::rb_tree<int>::iterator	it = tree.begin();
	for (ft::rb_tree<int>::iterator first = treecp.begin(); first != treecp.end(); ++first)
	{
		if (*first != *it)
			return false;
		++it;
	}

	return true;
}

inline static bool	__begin( void )
{
	ft::rb_tree<int>	tree;

	tree.insert(10);
	tree.insert(2);
	tree.insert(20);
	tree.insert(1);
	tree.insert(42);

	ft::rb_tree<int>::iterator	it = tree.begin();
	ft::rb_tree<int>::const_iterator	cit = tree.begin();
	if (*it != 1 || *cit != 1)
		return false;
	return true;
}

inline static bool	__end( void )
{
	ft::rb_tree<int>	tree;

	tree.insert(10);
	tree.insert(2);
	tree.insert(20);
	tree.insert(1);
	tree.insert(42);

	ft::rb_tree<int>::iterator	it = tree.end();
	--it;
	ft::rb_tree<int>::const_iterator	cit(it);
	if (*it != 42 || *cit != 42)
		return false;
	return true;
}

inline static bool	__rbegin( void )
{
	ft::rb_tree<int>	tree;

	tree.insert(10);

	if (tree.rbegin().base().base() != tree.end().base())
		return false;
	return true;
}

inline static bool	__rend( void )
{
	ft::rb_tree<int>	tree;

	tree.insert(10);

	if (tree.rend().base().base() != tree.begin().base())
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
	ret = tree.insert(2);
	if (ret.second == false || *ret.first != 2 || tree._validity_check() == false)
		return false;
	ret = tree.insert(20);
	if (ret.second == false || *ret.first != 20 || tree._validity_check() == false)
		return false;
	ret = tree.insert(1);
	if (ret.second == false || *ret.first != 1 || tree._validity_check() == false)
		return false;
	ret = tree.insert(42);
	if (ret.second == false || *ret.first != 42 || tree._validity_check() == false)
		return false;

	ret = tree.insert(42);
	if (ret.second == true || *ret.first != 42 || tree._validity_check() == false)
		return false;

	ret = tree.insert(43);
	if (ret.second == false || *ret.first != 43 || tree._validity_check() == false)
		return false;

	if (tree.size() != 6 || tree.empty() == true)
		return false;
	return true;
}

inline static bool	__insert_hint( void )
{
	ft::rb_tree<int>	tree;
	ft::rb_tree<int>::iterator	it;
	ft::rb_tree<int>::iterator	ret;

	it = tree.insert(10).first;

	ret = tree.insert(it, 1);
	if (*ret != 1 || tree._validity_check() == false)
		return false;

	it = ret;
	ret = tree.insert(it, 20);
	if (*ret != 20 || tree._validity_check() == false)
		return false;

	it = ret;
	ret = tree.insert(it, 0);
	if (*ret != 0 || tree._validity_check() == false)
		return false;

	it = ret;
	ret = tree.insert(it, 42);
	if (*ret != 42 || tree._validity_check() == false)
		return false;

	it = ret;
	ret = tree.insert(it, 42);
	if (*ret != 42 || tree._validity_check() == false)
		return false;

	it = ret;
	ret = tree.insert(it, 43);
	if (*ret != 43 || tree._validity_check() == false)
		return false;

	return true;
}

void	test_rb_tree( void )
{
	t_sub_test	arr[] = {
		{__default_constructor, "constructor (default)"},
		{__range_constructor, "constructor (range)"},
		{__copy_constructor, "constructor (copy)"},
		{__copy_assignement_operator, "operator="},
		{__begin, "begin"},
		{__end, "end"},
		{__rbegin, "rbegin"},
		{__rend, "rend"},
		{__insert_single_element, "insert (single element)"},
		{__insert_hint, "insert (hint)"},
		{NULL, ""}
	};

	run_sub_tests(arr);
	return;
}
