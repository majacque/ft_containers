#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <cstring>
#include "iterator.hpp"
#include "tests_define.hpp"

typedef std::string::iterator		it_string_type;
typedef std::vector<int>::iterator	it_vector_type;

static std::string 		str("abcdef");
static int 				arr[] = {0,1,2,3,4,5,6,7,8,9,10};
static std::vector<int> v(arr, arr + sizeof(arr) / sizeof(int));

inline static bool	__default_constructor( void )
{
	std::reverse_iterator<std::string::iterator>	std_rit;
	ft::reverse_iterator<std::string::iterator>		ft_rit;

	if (sizeof(std_rit) != sizeof(ft_rit)
		|| memcmp(&std_rit, &ft_rit, sizeof(std_rit)))
		return false;
	else if (std_rit.base() != ft_rit.base())
		return false;

	return true;
}

inline static bool	__initialization_constructor( void )
{
	it_string_type	it = str.end();

	std::reverse_iterator<it_string_type>	std_rit(it);
	ft::reverse_iterator<it_string_type>	ft_rit(it);

	if (sizeof(std_rit) != sizeof(ft_rit)
		|| memcmp(&std_rit, &ft_rit, sizeof(std_rit)))
		return false;
	else if (std_rit.base() != ft_rit.base())
		return false;
	else if (*std_rit != *ft_rit)
		return false;

	return true;
}

inline static bool	__copy_constructor( void )
{
	it_string_type	it = str.end();
	ft::reverse_iterator<it_string_type>	ft_rit0(it);

	ft::reverse_iterator<it_string_type>	ft_rit1(ft_rit0);
	if (sizeof(ft_rit0) != sizeof(ft_rit1)
		|| memcmp(&ft_rit0, &ft_rit1, sizeof(ft_rit0)))
		return false;
	else if (*ft_rit0 != *ft_rit1)
		return false;

	return true;
}

inline static bool	__base( void )
{
	it_string_type	it = str.end();

	ft::reverse_iterator<it_string_type>	ft_rit(it);

	it_string_type	base = ft_rit.base();
	if (sizeof(it) != sizeof(base)
		|| memcmp(&it, &base, sizeof(it)))
		return false;
	else if (ft_rit.base() != it)
		return false;

	return true;
}

/****************************PUBLIC MEMBER OPERATORS****************************/

inline static bool	__derefence_operator( void )
{
	it_string_type	it_string_begin = str.begin();
	it_string_type	it_string_middle = str.begin() + 2;
	it_string_type	it_string_end = str.end();

	std::reverse_iterator<it_string_type>	std_string_begin(it_string_begin);
	std::reverse_iterator<it_string_type>	std_string_middle(it_string_middle);
	std::reverse_iterator<it_string_type>	std_string_end(it_string_end);

	ft::reverse_iterator<it_string_type>	ft_string_begin(it_string_begin);
	ft::reverse_iterator<it_string_type>	ft_string_middle(it_string_middle);
	ft::reverse_iterator<it_string_type>	ft_string_end(it_string_end);

	if (*std_string_begin != *ft_string_begin ||
		*std_string_middle != *ft_string_middle ||
		*std_string_end	!= *ft_string_end)
		return false;

	it_vector_type	it_vector_middle = v.begin() + 4;
	it_vector_type	it_vector_end = v.end();

	std::reverse_iterator<it_vector_type>	std_vector_middle(it_vector_middle);
	std::reverse_iterator<it_vector_type>	std_vector_end(it_vector_end);

	ft::reverse_iterator<it_vector_type>	ft_vector_middle(it_vector_middle);
	ft::reverse_iterator<it_vector_type>	ft_vector_end(it_vector_end);

	if (*std_vector_middle != *ft_vector_middle ||
		*std_vector_end	!= *ft_vector_end)
		return false;

	return true;
}

inline static bool	__structure_derefence_operator( void )
{
	it_string_type	it_string_begin = str.begin();
	it_string_type	it_string_middle = str.begin() + 2;
	it_string_type	it_string_end = str.end();

	std::reverse_iterator<it_string_type>	std_string_begin(it_string_begin);
	std::reverse_iterator<it_string_type>	std_string_middle(it_string_middle);
	std::reverse_iterator<it_string_type>	std_string_end(it_string_end);

	ft::reverse_iterator<it_string_type>	ft_string_begin(it_string_begin);
	ft::reverse_iterator<it_string_type>	ft_string_middle(it_string_middle);
	ft::reverse_iterator<it_string_type>	ft_string_end(it_string_end);

	if (std_string_begin.operator->() != ft_string_begin.operator->() ||
		std_string_middle.operator->() != ft_string_middle.operator->() ||
		std_string_end.operator->()	!= ft_string_end.operator->())
		return false;

	it_vector_type	it_vector_middle = v.begin() + 4;
	it_vector_type	it_vector_end = v.end();

	std::reverse_iterator<it_vector_type>	std_vector_middle(it_vector_middle);
	std::reverse_iterator<it_vector_type>	std_vector_end(it_vector_end);

	ft::reverse_iterator<it_vector_type>	ft_vector_middle(it_vector_middle);
	ft::reverse_iterator<it_vector_type>	ft_vector_end(it_vector_end);

	if (std_vector_middle.operator->() != ft_vector_middle.operator->() ||
		std_vector_end.operator->()	!= ft_vector_end.operator->())
		return false;

	return true;
}

inline static bool	__addition_operator( void )
{
	it_string_type	it_string = str.end();

	std::reverse_iterator<it_string_type>	std_string_rit(it_string);
	ft::reverse_iterator<it_string_type>	ft_string_rit(it_string);

	for (int i = 1; i <= 6; i++)
	{
		if (*(std_string_rit + i) != *(ft_string_rit + i))
			return false;
	}

	std::vector<int>	v;
	for (int i = 0; i < 7; i++)
		v.push_back(i);

	it_vector_type	it_vector = v.end();

	std::reverse_iterator<it_vector_type>	std_vector_rit(it_vector);
	ft::reverse_iterator<it_vector_type>	ft_vector_rit(it_vector);

	for (int i = 1; i <= 6; i++)
	{
		if (*(std_vector_rit + i) != *(ft_vector_rit + i))
			return false;
	}

	return true;
}

inline static bool	__substraction_operator( void )
{
	it_string_type	it_string = str.begin();

	std::reverse_iterator<it_string_type>	std_string_rit(it_string);
	ft::reverse_iterator<it_string_type>	ft_string_rit(it_string);

	for (int i = 1; i <= 6; i++)
	{
		if (*(std_string_rit - i) != *(ft_string_rit - i))
			return false;
	}

	std::vector<int>	v;
	for (int i = 0; i < 7; i++)
		v.push_back(i);

	it_vector_type	it_vector = v.begin();

	std::reverse_iterator<it_vector_type>	std_vector_rit(it_vector);
	ft::reverse_iterator<it_vector_type>	ft_vector_rit(it_vector);

	for (int i = 1; i <= 6; i++)
	{
		if (*(std_vector_rit - i) != *(ft_vector_rit - i))
			return false;
	}

	return true;
}

inline static bool	__pre_incrementation_operator( void )
{
	it_string_type	it_string = str.end();

	std::reverse_iterator<it_string_type>	std_string_rit(it_string);
	ft::reverse_iterator<it_string_type>	ft_string_rit(it_string);

	for (int i = 1; i <= 6; i++)
	{
		if (*++std_string_rit != *++ft_string_rit)
			return false;
	}

	std::vector<int>	v;
	for (int i = 0; i < 7; i++)
		v.push_back(i);

	it_vector_type	it_vector = v.end();

	std::reverse_iterator<it_vector_type>	std_vector_rit(it_vector);
	ft::reverse_iterator<it_vector_type>	ft_vector_rit(it_vector);

	for (int i = 1; i <= 6; i++)
	{
		if (*++std_vector_rit != *++ft_vector_rit)
			return false;
	}

	return true;
}

inline static bool	__post_incrementation_operator( void )
{
	it_string_type	it_string = str.end();

	std::reverse_iterator<it_string_type>	std_string_rit(it_string);
	ft::reverse_iterator<it_string_type>	ft_string_rit(it_string);

	for (int i = 1; i <= 6; i++)
	{
		if (*std_string_rit++ != *ft_string_rit++)
			return false;
	}

	std::vector<int>	v;
	for (int i = 0; i < 7; i++)
		v.push_back(i);

	it_vector_type	it_vector = v.end();

	std::reverse_iterator<it_vector_type>	std_vector_rit(it_vector);
	ft::reverse_iterator<it_vector_type>	ft_vector_rit(it_vector);

	for (int i = 1; i <= 6; i++)
	{
		if (*std_vector_rit++ != *ft_vector_rit++)
			return false;
	}

	return true;
}

inline static bool	__pre_decrementation_operator( void )
{
	it_string_type	it_string = str.begin();

	std::reverse_iterator<it_string_type>	std_string_rit(it_string);
	ft::reverse_iterator<it_string_type>	ft_string_rit(it_string);

	for (int i = 1; i <= 6; i++)
	{
		if (*--std_string_rit != *--ft_string_rit)
			return false;
	}

	std::vector<int>	v;
	for (int i = 0; i < 7; i++)
		v.push_back(i);

	it_vector_type	it_vector = v.begin();

	std::reverse_iterator<it_vector_type>	std_vector_rit(it_vector);
	ft::reverse_iterator<it_vector_type>	ft_vector_rit(it_vector);

	for (int i = 1; i <= 6; i++)
	{
		if (*--std_vector_rit != *--ft_vector_rit)
			return false;
	}

	return true;
}

inline static bool	__post_decrementation_operator( void )
{
	it_string_type	it_string = str.begin();

	std::reverse_iterator<it_string_type>	std_string_rit(it_string);
	ft::reverse_iterator<it_string_type>	ft_string_rit(it_string);

	for (int i = 1; i <= 6; i++)
	{
		if (*std_string_rit-- != *ft_string_rit--)
			return false;
	}

	std::vector<int>	v;
	for (int i = 0; i < 7; i++)
		v.push_back(i);

	it_vector_type	it_vector = v.begin() + 1;

	std::reverse_iterator<it_vector_type>	std_vector_rit(it_vector);
	ft::reverse_iterator<it_vector_type>	ft_vector_rit(it_vector);

	for (int i = 1; i <= 6; i++)
	{
		if (*std_vector_rit-- != *ft_vector_rit--)
			return false;
	}

	return true;
}

inline static bool	__addition_assignement_operator( void )
{
	it_string_type	it_string = str.end();

	std::reverse_iterator<it_string_type>	std_string_rit(it_string);
	ft::reverse_iterator<it_string_type>	ft_string_rit(it_string);

	for (int i = 3; i <= 1; i--)
	{
		std_string_rit += i;
		ft_string_rit += i;
		if (*std_string_rit != *ft_string_rit)
			return false;
	}

	std::vector<int>	v;
	for (int i = 0; i < 7; i++)
		v.push_back(i);

	it_vector_type	it_vector = v.end();

	std::reverse_iterator<it_vector_type>	std_vector_rit(it_vector);
	ft::reverse_iterator<it_vector_type>	ft_vector_rit(it_vector);

	for (int i = 3; i <= 1; i--)
	{
		std_vector_rit += i;
		ft_vector_rit += i;
		if (*std_vector_rit != *ft_vector_rit)
			return false;
	}

	return true;
}

inline static bool	__substraction_assignement_operator( void )
{
	it_string_type	it_string = str.begin();

	std::reverse_iterator<it_string_type>	std_string_rit(it_string);
	ft::reverse_iterator<it_string_type>	ft_string_rit(it_string);

	for (int i = 3; i <= 1; i--)
	{
		std_string_rit -= i;
		ft_string_rit -= i;
		if (*std_string_rit != *ft_string_rit)
			return false;
	}

	std::vector<int>	v;
	for (int i = 0; i < 7; i++)
		v.push_back(i);

	it_vector_type	it_vector = v.begin();

	std::reverse_iterator<it_vector_type>	std_vector_rit(it_vector);
	ft::reverse_iterator<it_vector_type>	ft_vector_rit(it_vector);

	for (int i = 3; i <= 1; i--)
	{
		std_vector_rit -= i;
		ft_vector_rit -= i;
		if (*std_vector_rit != *ft_vector_rit)
			return false;
	}

	return true;
}

inline static bool	__subscript_operator( void )
{
	it_string_type	it_string = str.end();

	std::reverse_iterator<it_string_type>	std_string_rit(it_string);
	ft::reverse_iterator<it_string_type>	ft_string_rit(it_string);

	for (int i = 10; i <= 1; i--)
	{
		if (std_string_rit[i] != ft_string_rit[i])
			return false;
	}

	std::vector<int>	v;
	for (int i = 0; i < 7; i++)
		v.push_back(i);

	it_vector_type	it_vector = v.end();

	std::reverse_iterator<it_vector_type>	std_vector_rit(it_vector);
	ft::reverse_iterator<it_vector_type>	ft_vector_rit(it_vector);

	for (int i = 10; i <= 1; i--)
	{
		if (std_vector_rit[i] != ft_vector_rit[i])
			return false;
	}

	return true;
}

/**************************NON-PUBLIC MEMBER OPERATORS**************************/

inline static bool	__relational_operators( void )
{
	it_string_type	it_string = str.end();

	std::reverse_iterator<it_string_type>	std_string_rit0(it_string);
	std::reverse_iterator<it_string_type>	std_string_rit1(it_string);
	ft::reverse_iterator<it_string_type>	ft_string_rit0(it_string);
	ft::reverse_iterator<it_string_type>	ft_string_rit1(it_string);

	if (std::operator==(std_string_rit0, std_string_rit1) != ft::operator==(ft_string_rit0, ft_string_rit1) ||
		std::operator!=(std_string_rit0, std_string_rit1) != ft::operator!=(ft_string_rit0, ft_string_rit1) ||
		std::operator<(std_string_rit0, std_string_rit1) != ft::operator<(ft_string_rit0, ft_string_rit1) ||
		std::operator<=(std_string_rit0, std_string_rit1) != ft::operator<=(ft_string_rit0, ft_string_rit1) ||
		std::operator>(std_string_rit0, std_string_rit1) != ft::operator>(ft_string_rit0, ft_string_rit1) ||
		std::operator>=(std_string_rit0, std_string_rit1) != ft::operator>=(ft_string_rit0, ft_string_rit1))
		return false;
	
	std_string_rit0++;
	ft_string_rit0++;

	if (std::operator==(std_string_rit0, std_string_rit1) != ft::operator==(ft_string_rit0, ft_string_rit1) ||
		std::operator!=(std_string_rit0, std_string_rit1) != ft::operator!=(ft_string_rit0, ft_string_rit1) ||
		std::operator<(std_string_rit0, std_string_rit1) != ft::operator<(ft_string_rit0, ft_string_rit1) ||
		std::operator<=(std_string_rit0, std_string_rit1) != ft::operator<=(ft_string_rit0, ft_string_rit1) ||
		std::operator>(std_string_rit0, std_string_rit1) != ft::operator>(ft_string_rit0, ft_string_rit1) ||
		std::operator>=(std_string_rit0, std_string_rit1) != ft::operator>=(ft_string_rit0, ft_string_rit1))
		return false;

	std_string_rit1 += 3;
	ft_string_rit1 += 3;

	if (std::operator==(std_string_rit0, std_string_rit1) != ft::operator==(ft_string_rit0, ft_string_rit1) ||
		std::operator!=(std_string_rit0, std_string_rit1) != ft::operator!=(ft_string_rit0, ft_string_rit1) ||
		std::operator<(std_string_rit0, std_string_rit1) != ft::operator<(ft_string_rit0, ft_string_rit1) ||
		std::operator<=(std_string_rit0, std_string_rit1) != ft::operator<=(ft_string_rit0, ft_string_rit1) ||
		std::operator>(std_string_rit0, std_string_rit1) != ft::operator>(ft_string_rit0, ft_string_rit1) ||
		std::operator>=(std_string_rit0, std_string_rit1) != ft::operator>=(ft_string_rit0, ft_string_rit1))
		return false;

	return true;
}

inline static bool	__nm_addition_operator( void )
{
	it_string_type	it(str.end());
	ft::reverse_iterator<it_string_type>	rit0(it);

	for (int i = 1; i < 6; i++)
	{
		ft::reverse_iterator<it_string_type>	rit1 = i + rit0;
		if (rit1 != rit0 + i)
			return false;
	}
	return true;
}

inline static bool	__nm_substraction_operator( void )
{
	it_string_type	it(str.end());
	ft::reverse_iterator<it_string_type>	rit0(it);

	for (int i = 1; i < 6; i++)
	{
		ft::reverse_iterator<it_string_type>	rit1 = i + rit0;
		if (rit1 - rit0 != i)
			return false;
	}
	return true;
}

void	test_reverse_iterator( void )
{
	t_sub_test	arr[] = {
		{__default_constructor, "default constructor"},
		{__initialization_constructor, "init constructor"},
		{__copy_constructor, "copy constructor"},
		{__base, "base"},
		{__derefence_operator, "operator*"},
		{__structure_derefence_operator, "operatro->"},
		{__addition_operator, "operator+"},
		{__substraction_operator, "operator-"},
		{__pre_incrementation_operator, "operator++ (pre)"},
		{__post_incrementation_operator, "operator++ (post)"},
		{__pre_decrementation_operator, "operator-- (pre)"},
		{__post_decrementation_operator, "operator-- (post)"},
		{__addition_assignement_operator, "operator+="},
		{__substraction_assignement_operator, "operator-="},
		{__subscript_operator, "operator[]"},
		{__relational_operators, "operators ==, !=, <, <=, >, >="},
		{__nm_addition_operator, "operator+ (non-member)"},
		{__nm_substraction_operator, "operator- (non-member)"},
		{NULL, ""}
	};

	run_sub_tests(arr);
}
