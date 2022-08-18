#ifndef TESTS_HPP
# define TESTS_HPP

#include "tests_define.hpp"

#ifndef NB_TEST
# define NB_TEST 6
#endif

void	test_iterator_traits( void );
void	test_reverse_iterator( void );
void	test_type_traits( void );
void	test_algorithm( void );
void	test_utility( void );
void	test_vector( void );

#endif
