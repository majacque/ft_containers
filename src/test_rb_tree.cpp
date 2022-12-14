#include "tests_define.hpp"
#include "rb_tree.hpp"
#include <set>
#include <algorithm>
#include <list> // _validity_check()
#include <cstdlib> // _validity_check()

template <typename T>
inline static void	__blackSteps(ft::rb_node<T> const *const node, std::list<int> &lst, int const steps)
{
	if (!node)
		return lst.push_back(steps);
	__blackSteps(node->childs[LEFT], lst, steps + (node->color == BLACKNODE));
	__blackSteps(node->childs[RIGHT], lst, steps + (node->color == BLACKNODE));
}

template <typename T, typename Compare>
inline static int	__propertiesCheck(ft::rb_node<T> const *const node, Compare const cmp)
{
	std::list<int>					lst;
	std::list<int>::const_iterator	it;

	if (!node)
		return EXIT_SUCCESS;
	// Color check
	{
		if (node->color != REDNODE && node->color != BLACKNODE)
			return EXIT_FAILURE;
	}
	// Order check
	{
		if ((node->childs[LEFT] && !cmp(node->childs[LEFT]->val, node->val)) ||
			(node->childs[RIGHT] && !cmp(node->val, node->childs[RIGHT]->val)))
			return EXIT_FAILURE;
	}
	// Red violation check
	{
		if (node->color == REDNODE &&
			((node->childs[LEFT] && node->childs[LEFT]->color == REDNODE) ||
			(node->childs[RIGHT] && node->childs[RIGHT]->color == REDNODE)))
			return EXIT_FAILURE;
	}
	// Black violation check
	{
		__blackSteps(node, lst, 0U);
		for (it = lst.begin() ; it != lst.end() ; ++it)
			if (*it != *lst.begin())
				return EXIT_FAILURE;
	}
	return __propertiesCheck(node->childs[LEFT], cmp) || __propertiesCheck(node->childs[RIGHT], cmp);
}

template <typename T>
inline static int	__integrityCheck(ft::rb_node<T> const *const node)
{
	if (!node)
		return EXIT_SUCCESS;
	if (node->childs[LEFT] && node->childs[LEFT]->parent != node)
		return EXIT_FAILURE;
	if (node->childs[RIGHT] && node->childs[RIGHT]->parent != node)
		return EXIT_FAILURE;
	return __integrityCheck(node->childs[LEFT]) || __integrityCheck(node->childs[RIGHT]);
}

template <typename T>
inline static bool	__validity_check( ft::rb_node<T> const * const node )
{
	ft::rb_node<T> const *	root = node;
	if (root->color == PTENODE)
		return true;

	while (root->parent->color != PTENODE)
		root = root->parent;

	if (__integrityCheck(root))
		return false;

	if (__propertiesCheck(root, typename ft::rb_tree<T>::compare_type()))
		return false;

	return true;
}

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
	if (__validity_check(tree.begin().base()) == false)
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
	if (__validity_check(treecp.begin().base()) == false || tree.size() != treecp.size())
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
	if (ret.second == false || *ret.first != 10 || __validity_check(tree.begin().base()) == false)
		return false;
	ret = tree.insert(2);
	if (ret.second == false || *ret.first != 2 || __validity_check(tree.begin().base()) == false)
		return false;
	ret = tree.insert(20);
	if (ret.second == false || *ret.first != 20 || __validity_check(tree.begin().base()) == false)
		return false;
	ret = tree.insert(1);
	if (ret.second == false || *ret.first != 1 || __validity_check(tree.begin().base()) == false)
		return false;
	ret = tree.insert(42);
	if (ret.second == false || *ret.first != 42 || __validity_check(tree.begin().base()) == false)
		return false;

	ret = tree.insert(42);
	if (ret.second == true || *ret.first != 42 || __validity_check(tree.begin().base()) == false)
		return false;

	ret = tree.insert(43);
	if (ret.second == false || *ret.first != 43 || __validity_check(tree.begin().base()) == false)
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
	if (*ret != 1|| __validity_check(tree.begin().base()) == false)
		return false;

	it = ret;
	ret = tree.insert(it, 20);
	if (*ret != 20|| __validity_check(tree.begin().base()) == false)
		return false;

	it = ret;
	ret = tree.insert(it, 0);
	if (*ret != 0|| __validity_check(tree.begin().base()) == false)
		return false;

	it = ret;
	ret = tree.insert(it, 42);
	if (*ret != 42|| __validity_check(tree.begin().base()) == false)
		return false;

	it = ret;
	ret = tree.insert(it, 42);
	if (*ret != 42|| __validity_check(tree.begin().base()) == false)
		return false;

	it = ret;
	ret = tree.insert(it, 43);
	if (*ret != 43|| __validity_check(tree.begin().base()) == false)
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
			__validity_check(tree.begin().base()) == false ||
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
			__validity_check(tree.begin().base()) == false ||
			!std::equal(tree.begin(), tree.end(), ref.begin()))
			return false;
	}
	return true;
}

inline static bool	__swap( void )
{
	int	tab1[] = {10, 2, 20, -1, 42, 50, 45, 15};
	int	tab2[] = {5, 2, 3, 1, 4, 6};

	ft::rb_tree<int>	tree1(&tab1[0], &tab1[8]);
	ft::rb_tree<int>	tree2(&tab2[0], &tab2[6]);

	ft::rb_tree<int>::iterator	it1_begin = tree1.begin();
	ft::rb_tree<int>::iterator	it2_begin = tree2.begin();

	std::sort(&tab1[0], &tab1[8]);
	std::sort(&tab2[0], &tab2[6]);

	tree1.swap(tree2);

	if (tree1.begin() != it2_begin ||
		tree2.begin() != it1_begin)
		return false;

	for (size_t i = 0; i < 8; ++i)
	{
		if (*it1_begin != tab1[i])
			return false;
		++it1_begin;
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
	if (*it != -1)
		return false;

	it = tree.upper_bound(-1);
	if (*it != 2)
		return false;

	it = tree.upper_bound(1);
	if (*it != 2)
		return false;

	it = tree.upper_bound(2);
	if (*it != 10)
		return false;

	it = tree.upper_bound(9);
	if (*it != 10)
		return false;

	it = tree.upper_bound(10);
	if (*it != 15)
		return false;

	it = tree.upper_bound(14);
	if (*it != 15)
		return false;

	it = tree.upper_bound(15);
	if (*it != 20)
		return false;

	it = tree.upper_bound(19);
	if (*it != 20)
		return false;

	it = tree.upper_bound(20);
	if (*it != 42)
		return false;

	it = tree.upper_bound(25);
	if (*it != 42)
		return false;

	it = tree.upper_bound(42);
	if (*it != 45)
		return false;

	it = tree.upper_bound(43);
	if (*it != 45)
		return false;

	it = tree.upper_bound(45);
	if (*it != 50)
		return false;

	it = tree.upper_bound(49);
	if (*it != 50)
		return false;

	it = tree.upper_bound(50);
	if (it != tree.end())
		return false;

	it = tree.upper_bound(51);
	if (it != tree.end())
		return false;

	return true;
}

inline static bool	__relational_operators( void )
{
	int	tab1[] = {10, 2, 20, -1, 42, 50, 45, 15};
	int	tab2[] = {5, 2, 3, 1, 4, 6};

	ft::rb_tree<int>	tree1(&tab1[0], &tab1[8]);
	ft::rb_tree<int>	tree2(tree1);

	if ((tree1 == tree2) == false || (tree1 != tree2) == true ||
		(tree1 <= tree2) == false ||
		(tree1 >= tree2) == false)
		return false;

	tree2.erase(20);
	if ((tree1 == tree2) == true || (tree1 != tree2) == false ||
		(tree1 <= tree2) == false ||
		(tree1 >= tree2) == true)
		return false;

	tree1.erase(20);
	tree1.erase(42);
	if ((tree1 == tree2) == true || (tree1 != tree2) == false)
		return false;

	tree1.insert(43);
	if ((tree2 < tree1) == false ||
		(tree2 <= tree1) == false ||
		(tree1 > tree2) == false ||
		(tree1 >= tree2) == false)
		return false;

	return true;
}

inline static bool	__swap_nm( void )
{
	int	tab1[] = {10, 2, 20, -1, 42, 50, 45, 15};
	int	tab2[] = {5, 2, 3, 1, 4, 6};

	ft::rb_tree<int>	tree1(&tab1[0], &tab1[8]);
	ft::rb_tree<int>	tree2(&tab2[0], &tab2[6]);

	ft::rb_tree<int>::iterator	it1_begin = tree1.begin();
	ft::rb_tree<int>::iterator	it2_begin = tree2.begin();

	std::sort(&tab1[0], &tab1[8]);
	std::sort(&tab2[0], &tab2[6]);

	ft::swap(tree1, tree2);

	if (tree1.begin() != it2_begin ||
		tree2.begin() != it1_begin)
		return false;

	for (size_t i = 0; i < 8; ++i)
	{
		if (*it1_begin != tab1[i])
			return false;
		++it1_begin;
	}

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
		{__swap, "swap (member)"},
		{__find, "find"},
		{__count, "count"},
		{__lower_bound, "lower bound"},
		{__upper_bound, "upper bound"},
		{__relational_operators, "relational operators"},
		{__swap_nm, "swap (non-member)"},
		{NULL, ""}
	};

	run_sub_tests(arr);
	return;
}
