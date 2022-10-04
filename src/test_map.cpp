#include "tests_define.hpp"
#include "map.hpp"
#include <map>
#include <string>
#include <typeinfo>
#include <algorithm>

inline static bool	__default_constructor( void )
{
	ft::map<char, int>	m;
	ft::map<char, int, std::greater<char> >	m1;

	if (m.size() != 0 ||
		m.empty() != true)
		return false;

	if (m1.size() != 0 ||
		m1.empty() != true)
		return false;

	return true;
}

inline static bool	__range_constructor( void )
{
	ft::map<char, int>	m;
	ft::map<char, int>	mtest(m.begin(), m.end());

	if (mtest.size() != 0 ||
		mtest.end() != mtest.begin())
		return false;

	m.insert(ft::pair<char, int>('b', 10));
	m.insert(ft::pair<char, int>('c', 20));
	m.insert(ft::pair<char, int>('a', 30));

	ft::map<char, int>	mcopy(m.begin(), m.end());

	ft::map<char, int>::iterator	itcopy = mcopy.begin();
	for (ft::map<char, int>::iterator	it = m.begin() ; it != m.end(); ++it)
	{
		if (it->first != itcopy->first)
			return false;
		++itcopy;
	}

	return true;
}

inline static bool	__copy_constructor( void )
{
	ft::map<char, int>	m;
	ft::map<char, int>	mtest(m);

	if (mtest.size() != 0 ||
		mtest.end() != mtest.begin())
		return false;

	m.insert(ft::pair<char, int>('b', 10));
	m.insert(ft::pair<char, int>('c', 20));
	m.insert(ft::pair<char, int>('a', 30));

	ft::map<char, int>	mcopy(m);

	ft::map<char, int>::iterator	itcopy = mcopy.begin();
	for (ft::map<char, int>::iterator	it = m.begin() ; it != m.end(); ++it)
	{
		if (it->first != itcopy->first)
			return false;
		++itcopy;
	}

	return true;
}

inline static bool	__copy_assignement_operator( void )
{
	ft::map<char, int>	m1;
	ft::map<char, int>	m2;

	m1['a'] = 200;
	m1['c'] = 100;
	m1['b'] = 300;

	m2 = m1;
	m1 = ft::map<char, int>();

	if (m1.begin() != m1.end())
		return false;

	if (m1.size() != 0 || m2.size() != 3)
		return false;
	if (m2['a'] != 200 ||
		m2['b'] != 300 ||
		m2['c'] != 100)
		return false;
	return true;
}

inline static bool	__subscript_operator( void )
{
	ft::map<char, std::string>	m;

	m['a'] = "one";
	m['b'] = "two";
	m['c'] = m['b'];

	if (m['a'] != "one" ||
		m['b'] != "two" ||
		m['c'] != m['b'])
		return false;

	return true;
}

inline static bool	__begin( void )
{
	ft::map<char, int>	m;

	if (m.begin() != m.end())
		return false;

	m['a'] = 200;
	m['c'] = 100;
	m['b'] = 300;

	ft::map<char, int>::iterator	it = m.begin();
	ft::map<char, int>::const_iterator	cit = it;

	if (it == m.end() ||
		cit->first != 'a' ||
		cit->second != 200)
		return false;

	cit++;
	++cit;
	cit--;
	--cit;

	if (it == m.end() ||
		cit->first != 'a' ||
		cit->second != 200)
		return false;

	--cit;

	if (cit != m.end())
		return false;

	return true;
}

inline static bool	__end( void )
{
	ft::map<char, int>	m;

	if (m.begin() != m.end())
		return false;

	m['a'] = 200;
	m['c'] = 100;
	m['b'] = 300;

	ft::map<char, int>::iterator	it = m.end();
	ft::map<char, int>::const_iterator	cit = it;
	--cit;

	if (cit->first != 'c' ||
		cit->second != 100)
		return false;

	cit--;
	--cit;
	cit++;
	++cit;

	if (cit->first != 'c' ||
		cit->second != 100)
		return false;

	++cit;
	++cit;

	if (cit->first != 'c' ||
		cit->second != 100)
		return false;

	++cit;

	if (cit != m.end())
		return false;

	return true;
}

inline static bool	__empty( void )
{
	ft::map<char, int>	m;

	if (m.empty() == false)
		return false;

	m['a'] = 100;
	if (m.empty() == true)
		return false;

	m.clear();
	if (m.empty() == false)
		return false;

	return true;
}

inline static bool	__size( void )
{
	ft::map<char, int>	m;

	if (m.size() != 0)
		return false;

	m['a'] = 200;
	m['c'] = 100;
	m['b'] = 300;

	if (m.size() != 3)
		return false;

	return true;
}

inline static bool	__max_size( void )
{
	ft::map<char, int>	m;

	if (m.max_size() != std::allocator<ft::rb_node<ft::pair<char, int> > >().max_size())
		return false;
	return true;
}

inline static bool	__clear( void )
{
	ft::map<char, int>	m;

	m.clear();
	if (m.size() != 0)
		return false;

	m['a'] = 100;
	m.clear();
	if (m.size() != 0)
		return false;

	return true;
}

inline static bool	__erase( void )
{
	ft::map<char, int>	m;

	m.insert(ft::pair<char, int>('b', 100));
	m.insert(ft::pair<char, int>('c', 200));
	m.insert(ft::pair<char, int>('a', 300));

	ft::map<char, int>::iterator	it = m.begin();
	m.erase(it);

	if (m.size() != 2 ||
		m.find('a') != m.end())
		return false;

	m.erase('b');

	if (m.size() != 1 ||
		m.find('b') != m.end())
		return false;

	m.insert(ft::pair<char, int>('b', 100));
	m.insert(ft::pair<char, int>('a', 300));
	m.erase(m.begin(), m.end());

	if (m.size() != 0 ||
		m.find('c') != m.end())
		return false;

	return true;
}

inline static bool	__insert( void )
{
	ft::map<char,int> m;

	m.insert(ft::pair<char,int>('a', 100));
	m.insert(ft::pair<char,int>('z', 200));

	ft::pair<ft::map<char,int>::iterator,bool> ret;
	ret = m.insert(ft::pair<char,int>('z', 500));
	if (ret.first->first != 'z' ||
		ret.second != false)
		return false;

	ft::map<char,int>::iterator it = m.begin();
	m.insert (it, ft::pair<char,int>('b', 300));
	m.insert (it, ft::pair<char,int>('c', 400));

	if (m.size() != 4)
		return false;

	ft::map<char,int> anothermap;
	anothermap.insert(m.begin(), m.find('c'));

	ft::map<char, int>::iterator	itm = m.begin();
	for (ft::map<char, int>::iterator it = anothermap.begin(); it != anothermap.end(); ++it)
	{
		if (it->first != itm->first ||
			it->second != itm->second)
			return false;
		++itm;
	}

	return true;
}

inline static bool	__swap( void )
{
	ft::map<char, int>	m1;
	ft::map<char, int>	m2;

	m1['a'] = 200;
	m1['c'] = 100;
	m1['b'] = 300;

	m2['y'] = 200;
	m2['x'] = 100;
	m2['z'] = 300;

	m1.swap(m2);

	if (m1.find('a') != m1.end() ||
		m1.find('z') == m1.end())
		return false;

	if (m2.find('a') == m2.end() ||
		m2.find('z') != m2.end())
		return false;

	return true;
}

inline static bool	__count( void )
{
	ft::map<char, int>	m;

	if (m.count('a') != 0)
		return false;

	m['a'] = 100;
	if (m.count('a') != 1)
		return false;

	m.clear();
	if (m.count('a') != 0)
		return false;

	return true;
}

inline static bool	__lower_bound( void )
{
	ft::map<char, int>	m;

	m['a'] = 20;
	m['b'] = 40;
	m['c'] = 60;
	m['d'] = 80;
	m['f'] = 100;

	if (m.lower_bound('b')->first != 'b' ||
		m.lower_bound('e')->first != 'f' ||
		m.lower_bound('z') != m.end())
		return false;

	return true;
}

inline static bool	__upper_bound( void )
{
	ft::map<char, int>	m;

	m['a'] = 20;
	m['b'] = 40;
	m['c'] = 60;
	m['d'] = 80;
	m['f'] = 100;

	if (m.upper_bound('b')->first != 'c' ||
		m.upper_bound('e')->first != 'f' ||
		m.upper_bound('z') != m.end())
		return false;

	return true;
}

inline static bool	__key_comp( void )
{
	ft::map<char, int, std::less<char> >	mless;
	ft::map<char, int, std::greater<char> >	mgreater;

	ft::map<char, int, std::less<char> >::key_compare	comp_less = mless.key_comp();
	ft::map<char, int, std::greater<char> >::key_compare	comp_greater = mgreater.key_comp();

	std::less<char>	less;
	std::greater<char>	greater;

	if (comp_less('a', 'b') != less('a', 'b') ||
		comp_less('b', 'b') != less('b', 'b') ||
		comp_less('b', 'a') != less('b', 'a'))
		return false;

	if (comp_greater('a', 'b') != greater('a', 'b') ||
		comp_greater('b', 'b') != greater('b', 'b') ||
		comp_greater('b', 'a') != greater('b', 'a'))
		return false;
	return true;
}

inline static bool	__value_comp( void )
{
	ft::map<char, int, std::less<char> >	mless;
	ft::map<char, int, std::greater<char> >	mgreater;

	ft::map<char, int, std::less<char> >::value_compare	comp_less = mless.value_comp();
	ft::map<char, int, std::greater<char> >::value_compare	comp_greater = mgreater.value_comp();

	std::less<char>	less;
	std::greater<char>	greater;

	ft::pair<char, int>	a('a', 10);
	ft::pair<char, int>	b('b', 10);

	if (comp_less(a, b) != less('a', 'b') ||
		comp_less(b, b) != less('b', 'b') ||
		comp_less(b, a) != less('b', 'a'))
		return false;

	if (comp_greater(a, b) != greater('a', 'b') ||
		comp_greater(b, b) != greater('b', 'b') ||
		comp_greater(b, a) != greater('b', 'a'))
		return false;
	return true;
}

inline static bool	__get_allocator( void )
{
	if (typeid(ft::map<char, int>::allocator_type) != typeid(std::allocator<ft::rb_node<ft::pair<char const, int> > >))
		return false;
	return true;
}

inline static bool	__relational_operators( void )
{
	ft::map<char, int>	m1;

	m1['b'] = 100;
	m1['d'] = 200;
	m1['e'] = 101;
	m1['a'] = 300;
	m1['z'] = 400;

	ft::map<char, int>	m2(m1);

	if ((m1 == m2) == false || (m1 != m2) == true ||
		(m1 <= m2) == false ||
		(m1 >= m2) == false)
		return false;

	m2.erase('d');
	if ((m1 == m2) == true || (m1 != m2) == false ||
		(m1 <= m2) == false ||
		(m1 >= m2) == true)
		return false;

	m1.erase('d');
	m1.erase('e');
	if ((m1 == m2) == true || (m1 != m2) == false)
		return false;

	m1.insert(ft::pair<char, int>('f', 100));
	if ((m2 < m1) == false ||
		(m2 <= m1) == false ||
		(m1 > m2) == false ||
		(m1 >= m2) == false)
		return false;

	return true;
}

inline static bool	__swap_nm( void )
{
	char	tab1[] = {
		'c',
		'd',
		'a',
		'z',
		'h',
		't',
		'n',
		'b',
	};

	char	tab2[] = {
		'w',
		'u',
		'h',
		'k',
		'l',
	};

	ft::map<char, int>	m1;
	ft::map<char, int>	m2;

	m1['c'] = 100;
	m1['d'] = 1100;
	m1['a'] = 200;
	m1['z'] = 2200;
	m1['h'] = 300;
	m1['t'] = 3300;
	m1['n'] = 400;
	m1['b'] = 4400;

	m2['w'] = 100;
	m2['u'] = 1100;
	m2['h'] = 200;
	m2['k'] = 2200;
	m2['l'] = 600;

	ft::map<char, int>::iterator	it1_begin = m1.begin();
	ft::map<char, int>::iterator	it2_begin = m2.begin();

	std::sort(&tab1[0], &tab1[8]);
	std::sort(&tab2[0], &tab2[5]);

	ft::swap(m1, m2);

	if (m1.begin() != it2_begin ||
		m2.begin() != it1_begin)
		return false;

	for (size_t i = 0; i < 8; ++i)
	{
		if (it1_begin->first != tab1[i])
			return false;
		++it1_begin;
	}

	return true;
}

void	test_map( void )
{
	t_sub_test	arr[] = {
		{__default_constructor, "constructor (default)"},
		{__range_constructor, "constructor (range)"},
		{__copy_constructor, "constructor (copy)"},
		{__copy_assignement_operator, "operator="},
		{__subscript_operator, "operator[]"},
		{__begin, "begin"},
		{__end, "end"},
		{__empty, "empty"},
		{__size, "size"},
		{__max_size, "max size"},
		{__clear, "clear"},
		{__erase, "erase"},
		{__insert, "insert"},
		{__swap, "swap"},
		{__count, "count"},
		{__lower_bound, "lower bound (>=)"},
		{__upper_bound, "upper bound (>)"},
		{__key_comp, "key comp"},
		{__value_comp, "value comp"},
		{__get_allocator, "get allocator"},
		{__relational_operators, "relational operators (==, !=, <, <=, >, >=)"},
		{__swap_nm, "swap (non-member)"},
		{NULL, ""}
	};

	run_sub_tests(arr);
	return;
}
