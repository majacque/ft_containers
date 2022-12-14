#include "tests_define.hpp"
#include "vector.hpp"
#include <vector>
#include <cstring>
#include <string>

typedef NAMESPACE::vector<int>			t_vector_int;
typedef NAMESPACE::vector<std::string>	t_vector_str;

// CONSTRUCTOR

inline static bool	__default_constructor( void )
{
	t_vector_int	v_int;
	t_vector_str	v_str;

	if (v_int.size() || v_int.capacity())
		return false;

	if (v_str.size() || v_str.capacity())
		return false;

	return true;
}

inline static bool	__fill_construct_length_error( void )
{
	bool	is_int = false;
	bool	is_str = false;

	size_t	length = -1;

	try
	{
		t_vector_int	v_1(length, 7);
	}
	catch(const std::length_error& e)
	{
		if (size_t(-1) < std::allocator<int>().max_size())
			return false;
		is_int = true;
	}

	try
	{
		t_vector_str	v_1(length, "421");
	}
	catch(const std::length_error& e)
	{
		if (size_t(-1) < std::allocator<std::string>().max_size())
			return false;
		is_str = true;
	}

	return is_int & is_str;
}

inline static bool	__fill_constructor( void )
{
	t_vector_int	v_int(6, 7);
	for (size_t i = 0; i < 6; ++i)
	{
		if (v_int[i] != 7)
			return false;
	}
	
	t_vector_str	v_str(3, "Factorio");
	for (size_t i = 0; i < 3; ++i)
	{
		if (v_str[i] != "Factorio")
			return false;
	}

	if (v_int.size() != 6 ||
		v_int.capacity() != 6)
		return false;
	
	if (v_str.size() != 3 ||
		v_str.capacity() != 3)
		return false;

	return true;
}

inline static bool	__range_constructor( void )
{
	t_vector_int	v0(6,7);
	t_vector_int	v1(v0.begin(), v0.end());

	if (v0.capacity() != v1.capacity() ||
		v0 != v1)
		return false;

	return true;
}

inline static bool	__copy_constructor( void )
{
	t_vector_int	v0(6,7);
	t_vector_int	v1(v0);

	if (v0.capacity() != v1.capacity() ||
		v0 != v1)
		return false;

	return true;
}

// OPERATOR=

inline static bool	__assign_operator( void )
{
	t_vector_int	v0(6,7);
	t_vector_int	v1;

	v1 = v0;

	if (v1.capacity() != v0.capacity() ||
		v0 != v1)
		return false;

	return true;
}

// ITERATOR

inline static bool	__begin( void )
{
	t_vector_int	v_int_empty;

	t_vector_int::iterator	it = v_int_empty.begin();

	if (it.base() != t_vector_int::pointer())
		return false;

	t_vector_int	v_int(6,7);
	v_int[0] = 1;

	it = v_int.begin();
	if (*it != 1)
		return false;

	return true;
}

inline static bool	__end( void )
{
	t_vector_int	v_int_empty;

	t_vector_int::iterator	it = v_int_empty.end();

	if (it.base() != t_vector_int::pointer())
		return false;

	t_vector_int	v_int(6,7);
	v_int[5] = 1;

	it = v_int.end();
	--it;
	if (*it != 1)
		return false;
	return true;
}

inline static bool	__rbegin( void )
{
	t_vector_int	v(6,7);

	if (v.rbegin().base().base() != v.end().base())
		return false;

	return true;
}

inline static bool	__rend( void )
{
	t_vector_int	v(6,7);

	if (v.begin().base() != v.rend().base().base())
		return false;

	return true;
}

// CAPACITY

inline static bool	__size( void )
{
	t_vector_int	v_int_default;
	t_vector_str	v_str_default;

	if (v_int_default.size() ||
		v_str_default.size())
		return false;

	size_t			length = 0;
	t_vector_int	v0_int(length, 7);
	t_vector_str	v0_str(length, "421");
	if (v0_int.size() != length ||
		v0_str.size() != length)
		return false;

	length = 6;
	t_vector_int	v6_int(length, 7);
	t_vector_str	v6_str(length, "421");
	if (v6_int.size() != length ||
		v6_str.size() != length)
		return false;

	return true;
}

inline static bool	__resize( void )
{
	t_vector_int	v(6,7);

	v.resize(3);

	if (v.size() != 3 ||
		v.capacity() != 6)
		return false;

	v.resize(5);

	if (v.size() != 5 ||
		v.capacity() != 6)
		return false;

	if (v[3] || v[4])
		return false;

	return true;
}

inline static bool	__capacity( void )
{
	t_vector_int	v_int_default;
	t_vector_str	v_str_default;

	if (v_int_default.capacity() ||
		v_str_default.capacity())
		return false;

	size_t			length = 0;
	t_vector_int	v0_int(length, 7);
	t_vector_str	v0_str(length, "421");
	if (v0_int.capacity() != length ||
		v0_str.capacity() != length)
		return false;

	length = 6;
	t_vector_int	v6_int(length, 7);
	t_vector_str	v6_str(length, "421");
	if (v6_int.capacity() != length ||
		v6_str.capacity() != length)
		return false;

	return true;
}

inline static bool	__empty( void )
{
	t_vector_int	v;

	if (v.empty() == false)
		return false;

	v.insert(v.begin(), 6, 7);

	if (v.empty() == true)
		return false;

	v.clear();

	if (v.empty() == false)
		return false;
	return true;
}

inline static bool	__reserve_length_error( void )
{
	try
	{
		t_vector_int	v;

		v.reserve(-1);
	}
	catch(const std::length_error& )
	{
		return true;
	}

	return false;
}

inline static bool	__reserve( void )
{
	t_vector_int	v(6,7);

	v.reserve(5);

	if (v.size() != 6 ||
		v.capacity() != 6)
		return false;

	v.reserve(12);

	if (v.size() != 6 ||
		v.capacity() != 12)
		return false;

	for (size_t i = 0; i < 6; ++i)
	{
		if (v[i] != 7)
			return false;
	}

	return __reserve_length_error();
}

// ELEMENT ACCESS

inline static bool	__access_element_operator( void )
{
	t_vector_int	v_int(6,7);

	try
	{
		v_int[0] = 1;
		if (*v_int.begin() != 1 ||
			v_int[1] != 7)
			return false;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: operator[]: " << e.what() << std::endl;
		return false;
	}

	return true;
}

inline static bool	__at_out_of_range( void )
{
	try
	{
		t_vector_int	v(6,7);

		t_vector_int::reference	rf = v.at(12);
	}
	catch(const std::out_of_range& )
	{
		return true;
	}

	return false;
}

inline static bool	__at( void )
{
	t_vector_int	v(6,7);

	t_vector_int::reference rf = v.at(0);
	t_vector_int::const_reference crf = v.at(0);

	rf = 12;

	if (v[0] != 12 ||
		crf != 12)
		return false;

	return __at_out_of_range();
}

inline static bool	__front( void )
{
	t_vector_int	v(6,7);

	t_vector_int::reference	rf = v.front();
	t_vector_int::const_reference	crf = v.front();

	if (&rf != v.begin().base() ||
		&crf != v.begin().base())
		return false;

	return true;
}

inline static bool	__back( void )
{
	t_vector_int	v(6,7);

	t_vector_int::reference	rf = v.back();
	t_vector_int::const_reference	crf = v.back();

	if (&rf != (v.end() - 1).base() ||
		&crf != (v.end() - 1).base())
		return false;

	return true;
}

// MODIFIERS

inline static bool	__assign_fill( void )
{
	t_vector_int	v(6,7);

	v.assign(5,6);

	if (v.size() != 5 ||
		v.capacity() != 6)
		return false;

	return true;
}

inline static bool	__assign_range( void )
{
	t_vector_int	v0(6,7);
	t_vector_int	v1(6,2);

	v1.assign(v0.begin(), v0.end());

	if (v1.size() != 6 ||
		v1.capacity() != 6)
		return false;

	for (size_t i = 0; i < 6; ++i)
	{
		if (v1[i] != 7)
			return false;
	}
	return true;
}

inline static bool	__push_back( void )
{
	t_vector_int		v_ft;
	std::vector<int>	v_std;

	v_ft.push_back(1);
	v_std.push_back(1);

	if (v_ft.size() != v_std.size() ||
		v_ft.capacity() != v_std.capacity() ||
		v_ft[0] != v_std[0])
		return false;


	v_ft.push_back(2);
	v_std.push_back(2);
	v_ft.push_back(3);
	v_std.push_back(3);
	v_ft.push_back(4);
	v_std.push_back(4);
	v_ft.push_back(5);
	v_std.push_back(5);

	if (v_ft.size() != v_std.size() ||
		v_ft.capacity() != v_std.capacity())
		return false;

	for (size_t i = 0; i < 5; ++i)
	{
		if (v_ft[i] != v_std[i])
			return false;
	}

	return true;
}

inline static bool	__pop_back( void )
{
	t_vector_int	v(6,7);

	v.pop_back();

	if (v.size() != 5 ||
		v.capacity() != 6)
		return false;

	v.pop_back();
	v.pop_back();
	v.pop_back();

	if (v.size() != 2 ||
		v.capacity() != 6)
		return false;

	v.pop_back();
	v.pop_back();

	if (v.empty() == false ||
		v.capacity() != 6)
		return false;

	v.pop_back();
	v.pop_back();

	return true;
}

inline static bool	__insert_fill( void )
{
	t_vector_int	v_int_default;
	size_t			length = 6;
	int				val = 7;

	v_int_default.insert(v_int_default.begin(), length, val);

	if (v_int_default.size() != length ||
		v_int_default.capacity() != length)
		return false;

	for (size_t i = 0; i < length; i++)
	{
		if (v_int_default[i] != val)
			return false;
	}

	val = 1;
	v_int_default.insert(v_int_default.begin() + 1, length, val);

	if (v_int_default.size() != length * 2 ||
		v_int_default.capacity() != length * 2)
		return false;

	for (size_t i = 1; i < length + 1; i++)
	{
		if (v_int_default[i] != val)
			return false;
	}

	return true;
}

inline static bool	__insert_range( void )
{
	t_vector_int	v0(6,7);
	t_vector_int	v1(6,2);

	v0.insert(v0.begin() + 1, v1.begin(), v1.end());

	if (v0.size() != 12 || v0.capacity() != 12)
		return false;

	size_t	i = 0;
	if (v0[i] != 7)
		return false;

	++i;
	for (; i < 7; ++i)
	{
		if (v0[i] != 2)
			return false;
	}
	for (; i < 6; ++i)
	{
		if (v0[i] != 7)
			return false;
	}

	return true;
}

inline static bool	__erase( void )
{
	t_vector_int	v(6,7);

	for (size_t i = 0; i < 6; ++i)
		v[i] += i;

	t_vector_int::iterator it = v.erase(v.begin());

	if (v.size() != 5 ||
		v.capacity() != 6 ||
		it != v.begin())
		return false;

	for (int i = 0; i < 5; ++i)
	{
		if (v[i] != i + 8)
			return false;
	}

	v.erase(v.begin() + 1, v.end());

	if (v.size() != 1 ||
		v.capacity() != 6 ||
		v[0] != 8)
		return false;

	return true;
}

inline static bool	__swap( void )
{
	t_vector_int	v0(6,7);
	t_vector_int	v1(7,6);

	v0.swap(v1);

	if (v0.size() != 7 ||
		v1.size() != 6)
		return false;

	for (size_t i = 0; i < v0.size(); ++i)
	{
		if (v0[i] != 6)
			return false;
	}

	for (size_t i = 0; i < v1.size(); ++i)
	{
		if (v1[i] != 7)
			return false;
	}

	return true;
}

inline static bool	__clear( void )
{
	t_vector_int	v(6,7);

	v.clear();

	if (v.empty() == false ||
		v.capacity() != 6)
		return false;

	return true;
}

// NON MEMBER

inline static bool	__nm_swap( void )
{
	t_vector_int	v0(6,7);
	t_vector_int	v1(7,6);

	ft::swap(v0, v1);

	if (v0.size() != 7 ||
		v1.size() != 6)
		return false;

	for (size_t i = 0; i < v0.size(); ++i)
	{
		if (v0[i] != 6)
			return false;
	}

	for (size_t i = 0; i < v1.size(); ++i)
	{
		if (v1[i] != 7)
			return false;
	}

	return true;
}

inline static bool	__relational_operators( void )
{
	t_vector_int	v0(6,7);
	t_vector_int	v1(6,7);

	if ((v0 == v1) == false ||
		(v0 != v1) == true ||
		(v0 < v1) == true ||
		(v0 <= v1) == false ||
		(v0 > v1) == true ||
		(v0 >= v1) == false)
		return false;

	v1[5] += 6;

	if ((v0 == v1) == true ||
		(v0 != v1) == false ||
		(v0 < v1) == false ||
		(v0 <= v1) == false ||
		(v0 > v1) == true ||
		(v0 >= v1) == true)
		return false;

	v0[5] += 8;

	if ((v0 == v1) == true ||
		(v0 != v1) == false ||
		(v0 < v1) == true ||
		(v0 <= v1) == true ||
		(v0 > v1) == false ||
		(v0 >= v1) == false)
		return false;

	return true;
}

bool	__benchmark( void )
{
	t_vector_int	v;
	for (int i = 0; i < 100000; ++i)
	{
		v.push_back(i);
	}

	while (!v.empty())
	{
		v.erase(v.begin());
	}

	return true;
}

void	test_vector( void )
{
	t_sub_test	arr[] = {
		{__default_constructor, "constructor (default)"},
		{__fill_constructor, "constructor (fill)"},
		{__range_constructor, "constructor (rang)"},
		{__copy_constructor, "constructor (copy)"},
		{__assign_operator, "operator="},
		{__begin, "begin"},
		{__end, "end"},
		{__rbegin, "rbegin"},
		{__rend, "rend"},
		{__size, "size"},
		{__resize, "resize"},
		{__capacity, "capacity"},
		{__empty, "empty"},
		{__reserve, "reserve"},
		{__access_element_operator, "operator[]"},
		{__at, "at"},
		{__front, "front"},
		{__back, "back"},
		{__assign_fill, "assign (fill)"},
		{__assign_range, "assign (range)"},
		{__push_back, "push_back"},
		{__pop_back, "pop_back"},
		{__insert_fill, "insert (fill)"},
		{__insert_range, "insert (range)"},
		{__erase, "erase"},
		{__swap, "swap"},
		{__clear, "clear"},
		{__nm_swap, "swap (non member)"},
		{__relational_operators, "relational operators"},
		{__benchmark, "benchmark"},
		{NULL, ""}
	};

	run_sub_tests(arr);
}
