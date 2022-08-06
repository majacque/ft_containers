#ifndef TEST_DEFINE_HPP
# define TEST_DEFINE_HPP

#ifndef RED
# define RED "\033[1;31m"
#endif

#ifndef GREEN
# define GREEN "\033[1;32m"
#endif

#ifndef RESET
# define RESET "\033[0m"
#endif

typedef struct s_fn_test	t_fn_test;

struct s_fn_test
{
	bool		(*f)(void);
	std::string	str;
};

#endif
