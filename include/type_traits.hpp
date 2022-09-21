#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft
{

/**
 * Enable type if condition is met.
 * The type T is enabled as member type enable_if::type if Cond is true.
 * Otherwise, enable_if::type is not defined.
 */

template <bool Cond, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T>
{
	typedef T type;
};

/**
 * @brief This template is designed to provide compile-time constants as types
 * 
 * @tparam T Type of the integral constant
 * @tparam v Value of the integral constant
 */
template <typename T, T v>
struct integral_constant
{
	typedef T						value_type;
	typedef integral_constant<T, v>	type;

	static value_type const			value = v;

	operator value_type(void) const
	{
		return value;
	}
};

/**
 * @brief Instantiation of integral_constant to represent the bool value true
 */
typedef integral_constant<bool, true>	true_type;

/**
 * @brief Instantitation of integral_constant to represent the bool value false
 */
typedef integral_constant<bool, false>	false_type;

/**
 * @brief Trait class that identifies whether T is an integral type.
 * 
 * @par It inherits from integral_constant as being either true_type or false_type,
 * depending on whether T is an integral type:
 * 
 * bool
 * char
 * [char16_t] // C++11
 * [char32_t] // C++11
 * wchar_t
 * signed char
 * short int
 * int
 * long int
 * long long int // C++11
 * unsigned char
 * unsigned short int
 * unsigned int
 * unsigned long int
 * unsigned long long int // C++11
 * 
 * All fundamental integral types, along with all their aliases (like those in cstdint),
 * are considered integral types by this class, including their const and volatile qualified variants.
 * 
 * @tparam T A type
 */
template <class T>
struct is_integral : public false_type {};
template <>
struct is_integral<bool> : public true_type {};
template <>
struct is_integral<char> : public true_type {};
// template <>
// struct is_integral<char16_t> : public true_type {};
// template <>
// struct is_integral<char32_t> : public true_type {};
template <>
struct is_integral<wchar_t> : public true_type {};
template <>
struct is_integral<signed char> : public true_type {};
template <>
struct is_integral<short int> : public true_type {};
template <>
struct is_integral<int> : public true_type {};
template <>
struct is_integral<long int> : public true_type {};
// template <>
// struct is_integral<long long int> : public true_type {};
template <>
struct is_integral<unsigned char> : public true_type {};
template <>
struct is_integral<unsigned short int> : public true_type {};
template <>
struct is_integral<unsigned int> : public true_type {};
template <>
struct is_integral<unsigned long int> : public true_type {};
// template <>
// struct is_integral<unsigned long long int> : public true_type {};

template <typename T>
class is_trivially_copyable : public false_type {};
template <>
class is_trivially_copyable<bool> : public true_type {};
template <>
class is_trivially_copyable<wchar_t> : public true_type {};
template <>
class is_trivially_copyable<signed char> : public true_type {};
template <>
class is_trivially_copyable<signed short> : public true_type {};
template <>
class is_trivially_copyable<signed int> : public true_type {};
template <>
class is_trivially_copyable<signed long> : public true_type {};
template <>
class is_trivially_copyable<unsigned char> : public true_type {};
template <>
class is_trivially_copyable<unsigned short> : public true_type {};
template <>
class is_trivially_copyable<unsigned int> : public true_type {};
template <>
class is_trivially_copyable<unsigned long> : public true_type {};
template <>
class is_trivially_copyable<float> : public true_type {};
template <>
class is_trivially_copyable<double> : public true_type {};
template <>
class is_trivially_copyable<long double> : public true_type {};

//is_same
template <class T, class U>
struct is_same : public false_type {};

template<typename _Tp>
struct is_same<_Tp, _Tp> : public true_type {};

}

#endif
