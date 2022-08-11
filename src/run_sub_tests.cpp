#include <iostream>
#include "tests_define.hpp"

extern bool	g_verbose;

void	run_sub_tests( t_sub_test const arr[] )
{
	if (g_verbose == true)
	{
		for (size_t i = 0; arr[i].f; i++)
		{
			if (arr[i].f() == true)
			{
				std::cerr << GREEN;
				std::cout << "[OK] - " << arr[i].str << "\n";
				std::cerr << RESET;
			}
			else
			{
				std::cerr << RED;
				std::cout << "[KO] - " << arr[i].str << "\n";
				std::cerr << RESET;
			}
		}
	}
	else
	{
		for (size_t i = 0; arr[i].f; i++)
		{
			if (arr[i].f() == true)
			{
				std::cerr << GREEN;
				std::cout << " [OK] ";
				std::cerr << RESET;
			}
			else
			{
				std::cerr << RED;
				std::cout << " [KO] ";
				std::cerr << RESET;
			}
		}
	}
}
