#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft
{

/**
 * @brief Test whether the elements in two ranges are equal
 * 
 * @par Compares the elements in the range [first1,last1) with those in the range beginning at first2.
 * The elements are compared using operator==.
 * Some (or all) of the objects in both ranges are accessed (once at most).
 * 
 * @param first1 Input iterator to the initial position of the first sequence
 * @param last1 Input iterator to the final position of the first sequence
 * @param first2 Input iterator to the initial position of the second sequence
 * @return true if all the elements in the range [first1,last1) compare equal to those of the range starting at first2, and false otherwise
 */
template <class InputIterator1, class InputIterator2>
bool equal( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
{
	while (first1 != last1) 
	{
		if (!(*first1 == *first2))
			return false;
		++first1;
		++first2;
	}
	return true;
}

/**
 * @brief Test whether the elements in two ranges are equal
 * 
 * @par Compares the elements in the range [first1,last1) with those in the range beginning at first2.
 * The elements are compared using @a pred.
 * Some (or all) of the objects in both ranges are accessed (once at most).
 * 
 * @param first1 Input iterator to the initial position of the first sequence
 * @param last1 Input iterator to the final position of the first sequence
 * @param first2 Input iterator to the initial position of the second sequence
 * @param pred Binary function that accepts two elements as argument (one of each of the two sequences, in the same order), and returns a value convertible to bool. The value returned indicates whether the elements are considered to match in the context of this function.
 * The function shall not modify any of its arguments.
 * This can either be a function pointer or a function object.
 * @return true if all the elements in the range [first1,last1) compare equal to those of the range starting at first2, and false otherwise
 */
template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
{
	while (first1 != last1) 
	{
		if (!pred(*first1,*first2))
			return false;
		++first1;
		++first2;
	}
	return true;
}

/**
 * @brief Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2)
 * 
 * @par A lexicographical comparison is the kind of comparison generally used to sort words alphabetically in dictionaries;
 * It involves comparing sequentially the elements that have the same position in both ranges against each other until one element is not equivalent to the other.
 * The result of comparing these first non-matching elements is the result of the lexicographical comparison.
 * If both sequences compare equal until one of them ends, the shorter sequence is lexicographically less than the longer one.
 * The elements are compared using operator<.
 * The objects in the ranges [first1,last1) and [first2,last2) are accessed.
 * 
 * @param first1 @param last1 Input iterators to the initial and final positions of the first sequence.
 * The range used is [first1,last1), which contains all the elements between first1 and last1, including the element pointed by first1 but not the element pointed by last1.
 * @param first2 @param last2 Input iterators to the initial and final positions of the second sequence. The range used is [first2,last2).
 */
template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
{
	while (first1 != last1)
	{
	if (first2 == last2 || *first2 < *first1)
		return false;
	else if (*first1 < *first2)
		return true;
	++first1;
	++first2;
	}
	return first2 != last2;
}

/**
 * @brief Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2)
 * 
 * @par A lexicographical comparison is the kind of comparison generally used to sort words alphabetically in dictionaries;
 * It involves comparing sequentially the elements that have the same position in both ranges against each other until one element is not equivalent to the other.
 * The result of comparing these first non-matching elements is the result of the lexicographical comparison.
 * If both sequences compare equal until one of them ends, the shorter sequence is lexicographically less than the longer one.
 * The elements are compared using @a comp.
 * The objects in the ranges [first1,last1) and [first2,last2) are accessed.
 * 
 * @param first1 @param last1 Input iterators to the initial and final positions of the first sequence.
 * The range used is [first1,last1), which contains all the elements between first1 and last1, including the element pointed by first1 but not the element pointed by last1.
 * @param first2 @param last2 Input iterators to the initial and final positions of the second sequence. The range used is [first2,last2).
 * @param comp Binary function that accepts two arguments of the types pointed by the iterators, and returns a value convertible to bool.
 * The value returned indicates whether the first argument is considered to go before the second in the specific strict weak ordering it defines.
 * The function shall not modify any of its arguments.
 * This can either be a function pointer or a function object.
 */
template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2,
							Compare comp)
{
	while (first1 != last1)
	{
	if (first2 == last2 || comp(*first2,*first1))
		return false;
	else if (comp(*first1,*first2))
		return true;
	++first1;
	++first2;
	}
	return first2 != last2;
}

}

#endif
