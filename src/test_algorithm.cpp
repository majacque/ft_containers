#include "tests_define.hpp"
#include "algorithm.hpp"
#include <vector>
#include <algorithm>
#include <cctype> // std::tolower
#include <string>

inline static bool	__mypredicate(int i, int j)
{
	return i == j;
}

inline static bool	__equal( void )
{
	int 				myints[] = {20,40,60,80,100};	//   myints: 20 40 60 80 100
	std::vector<int>	myvector(myints,myints+5);		// myvector: 20 40 60 80 100

	// using default comparison:
	if (NAMESPACE::equal(myvector.begin(), myvector.end(), myints) != true)
		return false;

	// using predicate comparison:
	if (NAMESPACE::equal(myvector.begin(), myvector.end(), myints, __mypredicate) != true)
		return false;

	myvector[3] = 81;									// myvector: 20 40 60 81 100

	// using default comparison:
	if (NAMESPACE::equal(myvector.begin(), myvector.end(), myints) != false)
		return false;

	// using predicate comparison:
	if (NAMESPACE::equal(myvector.begin(), myvector.end(), myints, __mypredicate) != false)
		return false;

	myvector[3] = 80;									// myvector: 20 40 60 80 100
	myvector.pop_back();								// myvector: 20 40 60 80

	// using default comparison:
	if (NAMESPACE::equal(myvector.begin(), myvector.end(), myints) != true)
		return false;

	// using predicate comparison:
	if (NAMESPACE::equal(myvector.begin(), myvector.end(), myints, __mypredicate) != true)
		return false;

	return true;
}

// a case-insensitive comparison function
inline static bool __mycomp(char c1, char c2)
{
	return std::tolower(c1) < std::tolower(c2);
}

#include <iostream>

inline static bool	__lexicographical_compare( void )
{
	std::string	foo("Apple");
	std::string	bar("apartment");

	if (NAMESPACE::lexicographical_compare(foo.begin(), foo.end(), bar.begin(), bar.end()) != true)
		return false;
	else if (NAMESPACE::lexicographical_compare(foo.begin(), foo.end(), bar.begin(), bar.end(), __mycomp) != false)
		return false;

	bar = foo;

	if (NAMESPACE::lexicographical_compare(foo.begin(), foo.end(), bar.begin(), bar.end()) != false)
		return false;
	else if (NAMESPACE::lexicographical_compare(foo.begin(), foo.end(), bar.begin(), bar.end(), __mycomp) != false)
		return false;

	return true;
}

void	test_algorithm( void )
{
	t_sub_test	arr[] = {
		{__equal, "equal"},
		{__lexicographical_compare, "lexicographical_compare"},
		{NULL, ""}
	};

	run_sub_tests(arr);
}
