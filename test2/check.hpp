#ifndef __FT_CONTAINERS_TEST
# define __FT_CONTAINERS_TEST
# include <iostream>
# include <ctime>
# include <map>
# include <stack>
# include <vector>
# include <set>
# include "Map.hpp"
# include "Stack.hpp"
# include "Vector.hpp"

# define RESET "\e[0m"
# define GREY "\e[90m"
# define RED "\e[91m"
# define GREEN "\e[92m"
# define YELLOW "\e[93m"
# define BLUE "\e[96m"
# define MAGENTA "\e[95m"
# define BOLD "\e[1m"
# define GOOD "✓"
# define WARNING "⚠"
# define FAIL "❌"

class Timer
{
	private:
		double	start;
		double	end;
		double	std_time;
		double	ft_time;
	public:
		Timer() {}
		/**
		 * Start Timer
		 */
		void Start() { start = clock(); }
		/**
		 * Stop Timer
		 * @tparam std	If check time is for std function (false by default)
		 */
		double Stop(bool std = false) {
			end = clock();
			if (std) std_time = end - start;
			else ft_time = end - start;
			return (end - start);
		}
		/**
		 * Returns true if the ft time is less than or equal to the std * 20
		 */
		bool isValid() {
			if (std_time == 0 && ft_time <= 20) return true;
			else if (ft_time <= std_time * 20) return true;
			return false;
		}
		double getSTDtime() { return std_time; }
		double getFTtime() { return ft_time; }
};

inline void main_header(std::string str)
{
	int str_width = str.length();
	int max_width = str_width + 8;
	std::cout << BLUE << std::string(max_width, '*') << std::endl;
	std::cout << "*   " << GREEN << str << BLUE << "   *" << std::endl;
	std::cout << BLUE << std::string(max_width, '*') << RESET << std::endl;
}

inline void test_header(std::string str)
{
	std::string equal(64 - str.length() - 2, '=');
	std::cout << BLUE << "===  "  << str << "  " << equal << RESET << std::endl;
}

inline void resume(int max_test, int success_test, int failed_test)
{
	test_header("Resume");
	std::cout << "Tests : " << YELLOW << max_test << RESET << std::endl;
	std::cout << "Success / Failed : " << GREEN << success_test << RESET << " / " << RED << failed_test << RESET << std::endl;
	if (failed_test > 0)
		std::cout << "Oh no, you make " << RED << failed_test << RESET << " error(s)" << std::endl;
	else
		std::cout << BOLD << GREEN << "Good job " << GOOD << RESET << std::endl;
	std::cout << std::endl;
}

inline bool check_max(std::string name, Timer *time, size_t a, size_t b)
{
	std::string margin(((name.size()) ? 45 : 0) - name.length(), ' ');
	std::cout << name << ": " << "Time {std:" << time->getSTDtime() << "|ft:" << time->getFTtime() << "}" << margin << BOLD;
	if (a == b && time->isValid())
	{
		std::cout << GREEN << GOOD << RESET << std::endl;
		return (true);
	}
	else
	{
		std::cout << YELLOW << WARNING << RESET << std::endl;
		std::cout << "⤷ " << a << " <=!=> " << b << std::endl;
	}
	return (false);
}

/**
 * Check if actions is same in std and ft, with (ft_time) <= (std_time * 20)
 * @tparam name		Set name of check
 * @tparam time		Reference to Timer object
 * @tparam a		First element to compare
 * @tparam b		Second element to compare
 * @return true if correct
 */
template <typename T>
inline bool check(std::string name, Timer *time, T a, T b)
{
	std::string margin(((name.size()) ? 45 : 0) - name.length(), ' ');
	std::cout << name << ": " << "Time {std:" << time->getSTDtime() << "|ft:" << time->getFTtime() << "}" << margin << BOLD;
	if (a == b && time->isValid())
	{
		std::cout << GREEN << GOOD << RESET << std::endl;
		return (true);
	}
	else
	{
		std::cout << RED << FAIL << RESET << std::endl;
		std::cout << "⤷ " << a << " <=!=> " << b << std::endl;
	}
	return (false);
};

/**
 * Check if actions is same in std and ft, with (ft_time) <= (std_time * 20)
 * @tparam name		Set name of check
 * @tparam time		Reference to Timer object
 * @tparam check	Return of comparison
 * @return true if correct
 */
inline bool check(std::string name, Timer *time, bool check)
{
	std::string margin(((name.size()) ? 45 : 0) - name.length(), ' ');
	std::cout << name << ": " << "Time {std:" << time->getSTDtime() << "|ft:" << time->getFTtime() << "}" << margin << BOLD;
	if (check && time->isValid())
	{
		std::cout << GREEN << GOOD << RESET << std::endl;
		return (true);
	}
	else
		std::cout << RED << FAIL << RESET << std::endl;
	return (false);
};

template <typename T>
bool operator==(ft::vector<T> &a, std::vector<T> &b)
{
	if (a.size() != b.size())
		return (false);
	if (a.empty() != b.empty())
		return (false);
	for (size_t i = 0; i < a.size(); i++)
	{
		if (a[i] != b[i])
			return (false);
	}
	return (true);
};

template <typename T, typename S>
bool operator==(ft::map<T, S> &a, std::map<T, S> &b)
{
	if (a.size() != b.size())
		return (false);
	if (a.empty() != b.empty())
		return (false);
	typename ft::map<T, S>::iterator it = a.begin();
	typename std::map<T, S>::iterator it2 = b.begin();
	while (it != a.end())
	{
		if (it->first != it2->first || it->second != it2->second)
			return (false);
		++it;
		++it2;
	}
	return (true);
};

#endif
