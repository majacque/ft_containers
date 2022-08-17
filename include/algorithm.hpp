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

// TODO lexicographical_compare

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
