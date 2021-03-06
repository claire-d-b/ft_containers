#ifndef UTILS_H
#define UTILS_H

namespace ft
{
    template <typename T, T val>
	struct storage
	{
		static const T value = val;
	};

	struct false_type : public storage<bool, false> {};
	struct true_type : public storage<bool, true> {};

	template <class T> struct is_integral : public false_type {};
	template <> struct is_integral<int> : public true_type {};
	template <> struct is_integral<unsigned int> : public true_type {};
	template <> struct is_integral<bool> : public true_type {};
	template <> struct is_integral<char> : public true_type {};
	template <> struct is_integral<unsigned char> : public true_type {};
	template <> struct is_integral<signed char> : public true_type {};
	template <> struct is_integral<short> : public true_type {};
	template <> struct is_integral<unsigned short> : public true_type {};
	template <> struct is_integral<long> : public true_type {};
	template <> struct is_integral<unsigned long> : public true_type {};
	template <> struct is_integral<long long> : public true_type {};
	template <> struct is_integral<unsigned long long> : public true_type {};

	template<bool B, typename T = void>
		struct enable_if {};

	template<typename T>
		struct enable_if<true, T> { typedef T type; };

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
  		bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
			while (first1 != last1) 
			{
				if (!pred(*first1, *first2))
					return (false);
				first1++;
				first2++;
			}
			return (true);
		}
	template <class InputIterator1, class InputIterator2>
  		bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
			while (first1 != last1) 
			{
				if (!(*first1 == *first2))
					return (false);
				first1++;
				first2++;
			}
			return (true);
		}
	
	template <class InputIterator1, class InputIterator2, class Compare>
  		bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp) {
			while (first1 != last1)
			{
				if (first2 == last2 || comp(*first2, *first1))
					return (false);
				else if (comp(*first1, *first2))
					return (true);
				first1++;
				first2++;
			}
			return (first2 != last2);
		}
	template <class InputIterator1, class InputIterator2>
  		bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
			while (first1 != last1)
			{
				if (first2 == last2 || *first2 < *first1)
					return (false);
				else if (*first1 < *first2)
					return (true);
				first1++;
				first2++;
			}
			return (first2 != last2);
		}
}

#endif