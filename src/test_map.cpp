#include "tests_define.hpp"
#include "map.hpp"
#include <map>
#include <string>

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
		{__clear, "clear"},
		{__erase, "erase"},
		{__count, "count"},
		{NULL, ""}
	};

	run_sub_tests(arr);
	return;
}
