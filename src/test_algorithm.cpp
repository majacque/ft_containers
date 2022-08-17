#include "tests_define.hpp"
#include "algorithm.hpp"
#include <vector>
#include <algorithm>

inline static bool	__mypredicate(int i, int j)
{
	return (i == j);
}

inline static bool	__equal( void )
{
	int 				myints[] = {20,40,60,80,100};	//   myints: 20 40 60 80 100
	std::vector<int>	myvector(myints,myints+5);		// myvector: 20 40 60 80 100

	// using default comparison:
	if (std::equal(myvector.begin(), myvector.end(), myints) != ft::equal(myvector.begin(), myvector.end(), myints))
		return false;
	// using predicate comparison:
	if (std::equal(myvector.begin(), myvector.end(), myints, __mypredicate) != ft::equal(myvector.begin(), myvector.end(), myints, __mypredicate))
		return false;

	myvector[3]=81;										// myvector: 20 40 60 81 100

	if (std::equal(myvector.begin(), myvector.end(), myints) != ft::equal(myvector.begin(), myvector.end(), myints))
		return false;
	if (std::equal(myvector.begin(), myvector.end(), myints, __mypredicate) != ft::equal(myvector.begin(), myvector.end(), myints, __mypredicate))
		return false;

	myvector[3]=80;										// myvector: 20 40 60 80 100
	myvector.pop_back();								// myvector: 20 40 60 80

	if (std::equal(myvector.begin(), myvector.end(), myints) != ft::equal(myvector.begin(), myvector.end(), myints))
		return false;
	if (std::equal(myvector.begin(), myvector.end(), myints, __mypredicate) != ft::equal(myvector.begin(), myvector.end(), myints, __mypredicate))
		return false;

	return true;
}

void	test_algorithm( void )
{
	t_sub_test	arr[] = {
		{__equal, "equal"},
		{NULL, ""}
	};

	run_sub_tests(arr);
}
