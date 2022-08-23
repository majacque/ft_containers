#include "tests_define.hpp"
#include "vector.hpp"
#include <vector>
#include <cstring>
#include <string>

inline static bool	__default_constructor( void )
{
	std::vector<int>	std_v_int;
	ft::vector<int>		ft_v_int;
	std::vector<double>	std_v_double;
	ft::vector<double>	ft_v_double;

	if (sizeof(std_v_int) != sizeof(ft_v_int) ||
		sizeof(std_v_double) != sizeof(ft_v_double))
		return false;

	// REMIND test with size(), capacity(), empty()
	return true;
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

	// REMIND test with size(), capacity(), empty()
	return true;
}

void	test_vector( void )
{
	t_sub_test	arr[] = {
		{__default_constructor, "default constructor"},
		{__fill_constructor, "fill constructor"},
		{NULL, ""}
	};

	run_sub_tests(arr);
}
