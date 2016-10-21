#pragma once

namespace quark 
{

	struct true_type { static const bool value = true; };
	struct false_type { static const bool value = false; };

	template <class T> struct is_integral : public false_type {};
	template <class T> struct is_signed : public false_type {};

	template <> struct is_integral<char> : public true_type {};
	template <> struct is_signed<char> : public false_type {};

	template <> struct is_integral<unsigned char> : public true_type {};
	template <> struct is_integral<unsigned short> : public true_type {};
	template <> struct is_integral<unsigned int> : public true_type {};
	template <> struct is_integral<unsigned long> : public true_type {};

	template <> struct is_integral<signed char> : public true_type {};
	template <> struct is_integral<signed short> : public true_type {};
	template <> struct is_integral<signed int> : public true_type {};
	template <> struct is_integral<signed long> : public true_type {};

	template <> struct is_signed<unsigned short> : public false_type {};
	template <> struct is_signed<unsigned int> : public false_type {};
	template <> struct is_signed<unsigned long> : public false_type {};

	template <> struct is_signed<signed char> : public true_type {};
	template <> struct is_signed<signed short> : public true_type {};
	template <> struct is_signed<signed int> : public true_type {};
	template <> struct is_signed<signed long> : public true_type {};


	template <> struct is_integral<unsigned long long> : public true_type {};
	template <> struct is_integral<signed long long> : public true_type {};
	template <> struct is_signed<unsigned long long> : public false_type {};
	template <> struct is_signed<signed long long> : public true_type {};


	namespace detail {
		template <typename T>
		struct set_type {
			static const bool enabled = true;
			typedef T type;
		};
	}


	template <typename T> struct make_signed {};
	template <> struct make_signed<unsigned char> : public detail::set_type<signed char> {};
	template <> struct make_signed<signed char> : public detail::set_type<signed char> {};
	template <> struct make_signed<unsigned short> : public detail::set_type<signed short> {};
	template <> struct make_signed<signed short> : public detail::set_type<signed short> {};
	template <> struct make_signed<unsigned int> : public detail::set_type<signed int> {};
	template <> struct make_signed<signed int> : public detail::set_type<signed int> {};
	template <> struct make_signed<unsigned long> : public detail::set_type<signed long> {};
	template <> struct make_signed<signed long> : public detail::set_type<signed long> {};

	template <> struct make_signed<unsigned long long> : public detail::set_type<signed long long> {};
	template <> struct make_signed<signed long long> : public detail::set_type<signed long long> {};

}






