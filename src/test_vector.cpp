#include "tests_define.hpp"
#include "vector.hpp"
#include <vector>
#include <cstring>
#include <string>
/* 
inline static bool	__( void )
{
	return true;
}
 */

typedef ft::vector<int>	t_vector_int;
typedef ft::vector<std::string>	t_vector_str;

// CONSTRUCTOR

inline static bool	__default_constructor( void )
{
	std::vector<int>	std_v_int;
	ft::vector<int>		ft_v_int;
	std::vector<double>	std_v_double;
	ft::vector<double>	ft_v_double;

	// REMIND test with empty()
	if (std_v_int.size() != ft_v_int.size() ||
		std_v_int.capacity() != ft_v_int.capacity())
		return false;

	if (std_v_double.size() != ft_v_double.size() ||
		std_v_double.capacity() != ft_v_double.capacity())
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
	std::vector<int>	std_v_int(6,7);
	ft::vector<int>		ft_v_int(6,7);
	for (size_t i = 0; i < std_v_int.size() && i < ft_v_int.size(); i++)
	{
		if (std_v_int[i] != ft_v_int[i])
			return false;
	}

	std::vector<std::string>	std_v_string(3, "Factorio");
	ft::vector<std::string>		ft_v_string(3, "Factorio");
	for (size_t i = 0; i < std_v_string.size() && i < ft_v_string.size(); i++)
	{
		if (std_v_string[i] != ft_v_string[i])
			return false;
	}

	if (__fill_construct_length_error() == false)
		return false;

	// REMIND test with size(), capacity(), empty()
	return true;
}

inline static bool	__range_constructor( void )
{
	t_vector_int	v0(6,7);
	t_vector_int	v1(v0.begin(), v0.end());

	if (v0.size() != v1.size() ||
		v0.capacity() != v1.capacity())
		return false;

	for (size_t i = 0; i < 6; i++)
	{
		if (v0[i] != v1[i])
			return false;
	}

	// REMIND test with v0 != v1
	return true;
}

inline static bool	__copy_constructor( void )
{
	t_vector_int	v0(6,7);
	t_vector_int	v1(v0);

	if (v0.size() != v1.size() ||
		v0.capacity() != v1.capacity())
		return false;

	for (size_t i = 0; i < 6; i++)
	{
		if (v0[i] != v1[i])
			return false;
	}

	// REMIND test with v0 != v1
	return true;
}

// OPERATOR=

inline static bool	__assign_operator( void )
{
	t_vector_int	v0(6,7);
	t_vector_int	v1;

	v1 = v0;

	if (v1.size() != v0.size() ||
		v1.capacity() != v0.capacity())
		return false;

	for (size_t i = 0; i < 6; ++i)
	{
		if (v1[i] != v0[i])
			return false;
	}

	// REMIND test with v0 != v1
	return true;
}

// ITERATOR

inline static bool	__begin( void )
{
	t_vector_int	v_int_empty;

	t_vector_int::iterator	it = v_int_empty.begin();

	if (it.base() != t_vector_int::pointer())
		return false;

	// REMIND test with vector not empty
	return true;
}

inline static bool	__end( void )
{
	t_vector_int	v_int_empty;

	t_vector_int::iterator	it = v_int_empty.begin();

	if (it.base() != t_vector_int::pointer())
		return false;

	// REMIND test with vector not empty
	return true;
}

inline static bool	__rbegin( void )
{
	t_vector_int	v(6,7);

	if (v.rbegin().base().base() != v.end().base())
		return false;

	// REMIND test with different data
	return true;
}

inline static bool	__rend( void )
{
	t_vector_int	v(6,7);

	if (v.begin().base() != v.rend().base().base())
		return false;

	// REMIND test with different data
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

	// REMIND test with capacity() != size()
	return true;
}

inline static bool	__max_size( void )
{
	t_vector_int	v;

	if (v.max_size() != std::allocator<int>().max_size())
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

	// REMIND test with different data
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

	// REMIND test after reserve(), insert(), push_back()...
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

	// REMIND test with different data
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

	// REMIND test for size() != capacity()
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

	// REMIND test with different data
	// test with (pos, end, begin)
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

	// REMIND test with different data
	return true;
}

// ELEMENT ACCESS

inline static bool	__access_element_operator( void )
{
	t_vector_int	v_int(6,7);

	try
	{
		v_int[0] = 0;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: operator[]: " << e.what() << std::endl;
		return false;
	}

	// REMIND test with different data
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
		{__max_size, "max size"},
		{__resize, "resize"},
		{__capacity, "capacity"},
		{__assign_fill, "assign (fill)"},
		{__assign_range, "assign (range)"},
		{__insert_fill, "insert (fill)"},
		{__insert_range, "insert (range)"},
		{__erase, "erase"},
		{__access_element_operator, "operator[]"},
		{NULL, ""}
	};

	run_sub_tests(arr);
}
