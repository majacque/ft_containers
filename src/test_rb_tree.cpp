#include "tests_define.hpp"
#include "rb_tree.hpp"
#include <set>

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

inline static bool	__erase_iterator( void )
{
	long double	g_long_double[] = {
		987654321.0,
		98765432.10,
		9876543.210,
		987654.3210,
		98765.43210,
		9876.543210,
		987.6543210,
		98.75643210,
		9.876543210,
		0.9876543210
	};
	size_t g_long_double_size = sizeof(g_long_double) / sizeof(*g_long_double);

	ft::rb_tree<long double>	tree(&g_long_double[0], &g_long_double[g_long_double_size]);
	std::set<long double>		ref(&g_long_double[0], &g_long_double[g_long_double_size]);

	for (size_t idx = 0U ; idx < g_long_double_size ; ++idx)
	{
		if (idx % 2)
		{
			tree.erase(tree.begin());
			ref.erase(ref.begin());
		}
		else
		{
			tree.erase((--tree.end()));
			ref.erase(--ref.end());
		}

		if (tree.size() != ref.size() ||
			tree._validity_check() == false ||
			!std::equal(tree.begin(), tree.end(), ref.begin()))
			return false;
	}
	return true;
}

inline static bool	__erase_value( void )
{
	char	g_char[] = {
		'Q',
		'W',
		'E',
		'R',
		'T',
		'Y',
		'U',
		'I',
		'O',
		'P',
	};
	size_t	g_char_size = sizeof(g_char) / sizeof(*g_char);

	ft::rb_tree<char>	tree(&g_char[0], &g_char[g_char_size]);
	std::set<char>		ref(&g_char[0], &g_char[g_char_size]);
	size_t				ft_ret;
	size_t				std_ret;

	for (size_t idx = 0U ; idx < g_char_size * 2 ; ++idx)
	{
		ft_ret = tree.erase(g_char[idx / 2]);
		std_ret = ref.erase(g_char[idx / 2]);

		if (tree.size() != ref.size() || ft_ret != std_ret ||
			tree._validity_check() == false ||
			!std::equal(tree.begin(), tree.end(), ref.begin()))
			return false;
	}
	return true;
}

inline static bool	__find( void )
{
	ft::rb_tree<int>	tree;

	tree.insert(10);
	tree.insert(2);
	tree.insert(20);
	tree.insert(1);
	tree.insert(42);
	tree.insert(43);

	if (*tree.find(10) != 10 ||
		*tree.find(2) != 2 ||
		*tree.find(20) != 20 ||
		*tree.find(1) != 1 ||
		*tree.find(42) != 42 ||
		*tree.find(43) != 43 ||
		tree.find(321321) != tree.end())
		return false;

	return true;
}

inline static bool	__count( void )
{
	ft::rb_tree<int>	tree;

	tree.insert(10);
	tree.insert(2);
	tree.insert(20);
	tree.insert(1);
	tree.insert(42);
	tree.insert(43);

	if( !tree.count(10) ||
		!tree.count(2) ||
		!tree.count(20) ||
		!tree.count(1) ||
		!tree.count(42) ||
		!tree.count(43) ||
		tree.count(2612))
		return false;
	return true;
}

inline static bool	__lower_bound( void )
{
	ft::rb_tree<int>	tree;

	tree.insert(10);
	tree.insert(2);
	tree.insert(20);
	tree.insert(-1);
	tree.insert(42);
	tree.insert(50);
	tree.insert(45);
	tree.insert(15);

	ft::rb_tree<int>::iterator	it;

	it = tree.lower_bound(-2);
	if (*it != -1)
		return false;

	it = tree.lower_bound(-1);
	if (*it != -1)
		return false;

	it = tree.lower_bound(1);
	if (*it != 2)
		return false;

	it = tree.lower_bound(2);
	if (*it != 2)
		return false;

	it = tree.lower_bound(9);
	if (*it != 10)
		return false;

	it = tree.lower_bound(10);
	if (*it != 10)
		return false;

	it = tree.lower_bound(11);
	if (*it != 15)
		return false;

	it = tree.lower_bound(15);
	if (*it != 15)
		return false;

	it = tree.lower_bound(19);
	if (*it != 20)
		return false;

	it = tree.lower_bound(20);
	if (*it != 20)
		return false;

	it = tree.lower_bound(25);
	if (*it != 42)
		return false;

	it = tree.lower_bound(42);
	if (*it != 42)
		return false;

	it = tree.lower_bound(43);
	if (*it != 45)
		return false;

	it = tree.lower_bound(45);
	if (*it != 45)
		return false;

	it = tree.lower_bound(49);
	if (*it != 50)
		return false;

	it = tree.lower_bound(50);
	if (*it != 50)
		return false;

	it = tree.lower_bound(51);
	if (it != tree.end())
		return false;

	return true;
}

inline static bool	__upper_bound( void )
{
	ft::rb_tree<int>	tree;

	tree.insert(10);
	tree.insert(2);
	tree.insert(20);
	tree.insert(-1);
	tree.insert(42);
	tree.insert(50);
	tree.insert(45);
	tree.insert(15);

	ft::rb_tree<int>::iterator	it;

	it = tree.upper_bound(-2);
	if (it != tree.end())
		return false;

	it = tree.upper_bound(-1);
	if (*it != -1)
		return false;

	it = tree.upper_bound(5);
	if (*it != 2)
		return false;

	it = tree.upper_bound(2);
	if (*it != 2)
		return false;

	it = tree.upper_bound(12);
	if (*it != 10)
		return false;

	it = tree.upper_bound(10);
	if (*it != 10)
		return false;

	it = tree.upper_bound(16);
	if (*it != 15)
		return false;

	it = tree.upper_bound(15);
	if (*it != 15)
		return false;

	it = tree.upper_bound(25);
	if (*it != 20)
		return false;

	it = tree.upper_bound(20);
	if (*it != 20)
		return false;

	it = tree.upper_bound(43);
	if (*it != 42)
		return false;

	it = tree.upper_bound(42);
	if (*it != 42)
		return false;

	it = tree.upper_bound(46);
	if (*it != 45)
		return false;

	it = tree.upper_bound(45);
	if (*it != 45)
		return false;

	it = tree.upper_bound(51);
	if (*it != 50)
		return false;

	it = tree.upper_bound(50);
	if (*it != 50)
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
		{__erase_iterator, "erase (iterator)"},
		{__erase_value, "erase (value)"},
		{__find, "find"},
		{__count, "count"},
		{__lower_bound, "lower bound"},
		{__upper_bound, "upper bound"},
		{NULL, ""}
	};

	run_sub_tests(arr);
	return;
}
