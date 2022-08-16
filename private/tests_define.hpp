#ifndef TEST_DEFINE_HPP
# define TEST_DEFINE_HPP

#include <string>

#ifndef RED
# define RED "\033[1;31m"
#endif

#ifndef GREEN
# define GREEN "\033[1;32m"
#endif

#ifndef RESET
# define RESET "\033[0m"
#endif

typedef struct s_sub_test	t_sub_test;

struct s_sub_test
{
	bool		( *f )( void );
	std::string	str;
};

typedef struct s_test	t_test;

struct s_test
{
	void		( *f )( void );
	std::string	str;
};

void	run_sub_tests( t_sub_test const arr[] );

#endif
