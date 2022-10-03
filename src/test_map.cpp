#include "tests_define.hpp"
#include "map.hpp"
#include <map>
#include <string>

inline static bool	__default_constructor( void )
{
	ft::map<char, int>	m;
	ft::map<char, int, std::greater<char> >	m1;
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
		{__copy_assignement_operator, "operator="},
		{__subscript_operator, "operator[]"},
		{__begin, "begin"},
		{__end, "end"},
		{__empty, "empty"},
		{__size, "size"},
		{__clear, "clear"},
		{__count, "count"},
		{NULL, ""}
	};

	run_sub_tests(arr);
	return;
}
