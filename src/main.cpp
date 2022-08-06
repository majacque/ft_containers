#include <iostream>
#include <cstdlib>
#include <cstring>
#include "tests.hpp"

bool	g_verbose = false;

int	main(int argc, char **argv) {
	size_t	test_to_launch = 0;

	if (argc > 2
	|| (argc == 2 && !(test_to_launch = strtol(argv[1], NULL, 10)))
	|| test_to_launch > NB_TEST
	|| test_to_launch < 0)
	{
		std::cerr << "Usage: ./container.out [number of the test to launch]\n";
		return 1;
	}

	if (argc == 2)
	{
		--test_to_launch;
		g_verbose = true;
	}

	t_fn_test	arr[] = {
		{test_iterator_traits, "iterator traits:"},
		{NULL, ""}
	};

	if (g_verbose == false)
	{
		for (size_t i = 0; arr[i].f; i++)
		{
			std::cout << i + 1 << " - " << arr[i].str;
			arr[i].f();
			std::cout << "\n";
		}
	}
	else
		arr[test_to_launch].f();

	return 0;
}
