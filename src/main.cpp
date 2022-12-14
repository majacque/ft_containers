#include <iostream>
#include <cstdlib>
#include <cstring>
#include "tests.hpp"

bool	g_verbose = false;

int	main(int argc, char **argv) {
	size_t	test_to_launch = 0;

	if (argc > 2
	|| (argc == 2 && !(test_to_launch = strtol(argv[1], NULL, 10)))
	|| test_to_launch > NB_TEST)
	{
		std::cerr << "Usage: ./container.out [number of the test to launch]\n";
		return 1;
	}

	if (argc == 2)
	{
		--test_to_launch;
		g_verbose = true;
	}

	t_test	arr[] = {
		{test_iterator_traits, "iterator traits"},
		{test_reverse_iterator, "reverse iterator"},
		{test_type_traits, "type_traits"},
		{test_algorithm, "algorithm"},
		{test_utility, "utility"},
		{test_vector, "vector"},
		// {test_rb_tree, "red black tree"},
		{test_map, "map"},
		{NULL, ""}
	};

	if (g_verbose == false)
	{
		for (size_t i = 0; arr[i].f; i++)
		{
			try
			{
				std::cout << i + 1 << " - " << arr[i].str << ":";
				arr[i].f();
				std::cout << "\n";
			}
			catch(const std::exception& e)
			{
				std::cerr << RED "Error: " RESET << e.what() << '\n';
			}
		}
	}
	else
	{
		std::cout << arr[test_to_launch].str << ":\n";
		arr[test_to_launch].f();
	}

	#ifdef STD
	std::cout << "std.log\n";
	#else
	std::cout << "ft.log\n";
	#endif

	return 0;
}
