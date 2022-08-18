#include "tests_define.hpp"
#include "vector.hpp"
#include <vector>
#include <cstring>

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

void	test_vector( void )
{
	t_sub_test	arr[] = {
		{__default_constructor, "default constructor"},
		{NULL, ""}
	};

	run_sub_tests(arr);
}
