#include "check.hpp"
#include <set>
#include <list>
#include "Set.hpp"
#include <utility>
#include <iostream>
#include <string.h>
#include <sstream>
#define sstr( x ) static_cast< std::ostringstream & >( ( std::ostringstream() << std::dec << x ) ).str()

class TestSet
{
	private:
		Timer Time;
		int max_test;
		int success_test;
		int failed_test;
	private:
		template <typename T>
		inline void checking(std::string name, Timer *time, T a, T b)
		{
			max_test++;
			if (check(name, time, a, b)) success_test++;
			else failed_test++;
		}
		inline void checking(std::string name, Timer *time, bool checking)
		{
			max_test++;
			if (check(name, time, checking)) success_test++;
			else failed_test++;
		}
	public:
		bool testIsSuccess() { return (failed_test == 0); }
		TestSet()
		{
			max_test = 0;
			success_test = 0;
			failed_test = 0;
		}
		void StartTest()
		{
			main_header("Set");
			constructor();
			max_size();
			insert();
			erase();
			swap();
			clear();
			find();
			count();
			bounds();
			range();
			operators();
			resume(max_test, success_test, failed_test);
		}
		~TestSet() {}
		#pragma region Test
		void constructor()
		{
			test_header("Constructor : Default / Copy / Range");
			Time.Start();
				ft::set<int> map_ft_1;
			Time.Stop();
			Time.Start();
				std::set<int> map_std_1;
			Time.Stop(true);
			checking("(default) map_ft_1 == map_std_1", &Time, (map_ft_1 == map_std_1));
			
			std::list<int> lst_1;
			unsigned int lst_size = 7;
			for (unsigned int i = 0; i < lst_size; ++i)
				lst_1.push_back(lst_size - i);

			lst_1.clear();
			Time.Start();
				ft::set<int> map_ft_2(lst_1.begin(), lst_1.end());
			Time.Stop();
			Time.Start();
				std::set<int> map_std_2(lst_1.begin(), lst_1.end());
			Time.Stop(true);
			checking("(range) map_ft_2 == map_std_2", &Time, (map_ft_2 == map_std_2));

			Time.Start();
				ft::set<int> map_ft_3(map_ft_2);
			Time.Stop();
			Time.Start();
				std::set<int> map_std_3(map_std_2);
			Time.Stop(true);
			checking("(copy) map_ft_3 == map_std_3", &Time, (map_ft_3 == map_std_3));

			Time.Start();
				ft::set<int> map_ft_4;
				map_ft_4.insert(1);
				map_ft_4.insert(2);
				map_ft_4.insert(3);
			Time.Stop();
			Time.Start();
				std::set<int> map_std_4;
				map_std_4.insert(1);
				map_std_4.insert(2);
				map_std_4.insert(3);
			Time.Stop(true);
			checking("(copy) map_ft_4 == map_std_4", &Time, (map_ft_4 == map_std_4));

			std::list<std::string> lst_2;
			lst_2.push_back("Hello"); lst_2.push_back("World");
			lst_2.push_back("and"); lst_2.push_back("welcome");
			lst_2.push_back("to"); lst_2.push_back("test");
			lst_2.push_back("and");
			Time.Start();
				ft::set<std::string> map_ft_5(lst_2.rbegin(), lst_2.rend());
			Time.Stop();
			Time.Start();
				std::set<std::string> map_std_5(lst_2.rbegin(), lst_2.rend());
			Time.Stop(true);
			checking("(copy) map_ft_5 == map_std_5", &Time, (map_ft_5 == map_std_5));
			
			
		}

		void max_size()
		{
			test_header("Max Size");
			Time.Start();
				ft::set<int> map_ft;
				(void)map_ft.max_size();
			Time.Stop();
			Time.Start();
				std::set<int> map_std;
				(void)map_std.max_size();
			Time.Stop(true);
			check_max("map_ft.max_size() == map_std.max_size()", &Time, map_ft.max_size(), map_std.max_size());
			Time.Start();
				ft::set<std::string> map_ft_2;
				(void)map_ft_2.max_size();
			Time.Stop();
			Time.Start();
				std::set<std::string> map_std_2;
				(void)map_std_2.max_size();
			Time.Stop(true);
			check_max("map_ft_2.max_size() == map_std_2.max_size()", &Time, map_ft_2.max_size(), map_std_2.max_size());
		}

		void insert()
		{
			test_header("Insert");
			Time.Start();
				ft::set<std::string> map_ft_1, map_ft_2;
			Time.Stop();
			Time.Start();
				std::set<std::string> map_std_1, map_std_2;
			Time.Stop(true);
			checking("(Insert) map_ft == map_std", &Time, (map_ft_1 == map_std_1));

			Time.Start();
				map_ft_1.insert("one"); map_ft_1.insert("two");
				map_ft_1.insert("three"); map_ft_1.insert("four");
				map_ft_1.insert("five");
			Time.Stop();
			Time.Start();
				map_std_1.insert("one"); map_std_1.insert("two");
				map_std_1.insert("three"); map_std_1.insert("four");
				map_std_1.insert("five");
			Time.Stop(true);
			checking("(Insert) map_ft == map_std", &Time, (map_ft_1 == map_std_1));
		
			Time.Start();
				map_ft_1.insert(map_ft_1.begin(), "ZERO");
			Time.Stop();
			Time.Start();
				map_std_1.insert(map_std_1.begin(), "ZERO");
			Time.Stop(true);
			checking("(Insert) map_ft == map_std", &Time, (map_ft_1 == map_std_1));

			Time.Start();
				map_ft_2.insert(map_ft_2.begin(), "hello");
				map_ft_2.insert(map_ft_2.end(), "world");
				map_ft_2.insert(map_ft_2.end(), "and");
			Time.Stop();
			Time.Start();
				map_std_2.insert(map_std_2.begin(), "hello");
				map_std_2.insert(map_std_2.end(), "world");
				map_std_2.insert(map_std_2.end(), "and");
			Time.Stop(true);
			checking("(Insert) map_ft == map_std", &Time, (map_ft_2 == map_std_2));
		}

		void erase()
		{
			test_header("Erase");
			std::list<std::string> lst;
			lst.push_back("a"); lst.push_back("b"); lst.push_back("c");
			lst.push_back("d"); lst.push_back("e"); lst.push_back("f");

			Time.Start();
				ft::set<std::string> map_ft(lst.begin(), lst.end());
			Time.Stop();
			Time.Start();
				std::set<std::string> map_std(lst.begin(), lst.end());
			Time.Stop(true);
			checking("map_ft == map_std", &Time, map_ft == map_std);

			Time.Start();
				map_ft.erase(++map_ft.begin());
			Time.Stop();
			Time.Start();
				map_std.erase(++map_std.begin());
			Time.Stop(true);
			checking("map_ft == map_std", &Time, map_ft == map_std);

			Time.Start();
				map_ft.erase(++map_ft.begin(), --map_ft.end());
			Time.Stop();
			Time.Start();
				map_std.erase(++map_std.begin(), --map_std.end());
			Time.Stop(true);
			checking("map_ft == map_std", &Time, map_ft == map_std);

			Time.Start();
				map_ft.erase("a");
			Time.Stop();
			Time.Start();
				map_std.erase("a");
			Time.Stop(true);
			checking("map_ft == map_std", &Time, map_ft == map_std);
		}

		void swap()
		{
			test_header("Swap");
			std::list<std::string> lst;
			lst.push_back("a"); lst.push_back("b"); lst.push_back("c");
			lst.push_back("d"); lst.push_back("e"); lst.push_back("f");

			Time.Start();
				ft::set<std::string> map_ft(lst.rbegin(), lst.rend());
				ft::set<std::string> swap_ft;
				map_ft.swap(swap_ft);
			Time.Stop();
			Time.Start();
				std::set<std::string> map_std(lst.rbegin(), lst.rend());
				std::set<std::string> swap_std;
				map_std.swap(swap_std);
			Time.Stop(true);
			checking("map_ft == map_std", &Time, map_ft == map_std);
			checking("swap_ft == swap_std", &Time, swap_ft == swap_std);
		}

		void clear()
		{
			test_header("Clear");
			Time.Start();
				ft::set<std::string> map_ft;
				map_ft.insert("a");
				map_ft.insert("b");
				map_ft.clear();
			Time.Stop();
			Time.Start();
				std::set<std::string> map_std;
				map_std.insert("a");
				map_std.insert("b");
				map_std.clear();
			Time.Stop(true);
			checking("map_ft == map_std", &Time, map_ft == map_std);
		}

		void find()
		{
			test_header("Find");
			Time.Start();
				ft::set<std::string> map_ft;
				map_ft.insert("a");
				map_ft.insert("b");
			Time.Stop();
			Time.Start();
				std::set<std::string> map_std;
				map_std.insert("a");
				map_std.insert("b");
			Time.Stop(true);
			checking("map_ft.find('a') == map_std.find('a')", &Time, *map_ft.find("a"), *map_std.find("a"));
			checking("map_ft.find('z') == map_std.find('z')", &Time, map_ft.find("z") == map_ft.end(), map_std.find("z") == map_std.end());
		}

		void count()
		{
			test_header("Count");
			std::list<std::string> lst;
			lst.push_back("a"); lst.push_back("b"); lst.push_back("b");

			Time.Start();
				ft::set<std::string> map_ft(lst.begin(), lst.end());
				(void)map_ft.count("a");
				(void)map_ft.count("b");
				(void)map_ft.count("z");
			Time.Stop();
			Time.Start();
				std::set<std::string> map_std(lst.begin(), lst.end());
				(void)map_std.count("a");
				(void)map_std.count("b");
				(void)map_std.count("z");
			Time.Stop(true);
			checking("map_ft.count('a') == map_std.count('a')", &Time, map_ft.count("a"), map_std.count("a"));
			checking("map_ft.count('b') == map_std.count('b')", &Time, map_ft.count("b"), map_std.count("b"));
			checking("map_ft.count('z') == map_std.count('z')", &Time, map_ft.count("z"), map_std.count("z"));
		}

		#pragma region bounds
		void bounds_lower(ft::set<int> map_ft, std::set<int> map_std, int x)
		{
			ft::set<int>::iterator FTit = map_ft.lower_bound(x);
			std::set<int>::iterator STDit = map_std.lower_bound(x);
			std::string _ft = (FTit == map_ft.end()) ? "end()" : sstr(*FTit);
			std::string _std = (STDit == map_std.end()) ? "end()" : sstr(*STDit);
			std::cout << sstr("map_ft.lower_bound(" << x << ") == map_std.lower_bound(" << x << ")");
			checking("", &Time, _ft, _std);
		}
		void const_bounds_lower(ft::set<int> map_ft, std::set<int> map_std, int x)
		{
			ft::set<int>::const_iterator FTit = map_ft.lower_bound(x);
			std::set<int>::const_iterator STDit = map_std.lower_bound(x);
			std::string _ft = (FTit == map_ft.end()) ? "end()" : sstr(*FTit);
			std::string _std = (STDit == map_std.end()) ? "end()" : sstr(*STDit);
			std::cout << sstr("map_ft.lower_bound(" << x << ") == map_std.lower_bound(" << x << ")");
			checking("", &Time, _ft, _std);
		}

		void bounds_upper(ft::set<int> map_ft, std::set<int> map_std, int x)
		{
			ft::set<int>::iterator FTit = map_ft.upper_bound(x);
			std::set<int>::iterator STDit = map_std.upper_bound(x);
			std::string _ft = (FTit == map_ft.end()) ? "end()" : sstr(*FTit);
			std::string _std = (STDit == map_std.end()) ? "end()" : sstr(*STDit);
			std::cout << sstr("map_ft.upper_bound(" << x << ") == map_std.upper_bound(" << x << ")");
			checking("", &Time, _ft, _std);
		}
		void const_bounds_upper(ft::set<int> map_ft, std::set<int> map_std, int x)
		{
			ft::set<int>::const_iterator FTit = map_ft.upper_bound(x);
			std::set<int>::const_iterator STDit = map_std.upper_bound(x);
			std::string _ft = (FTit == map_ft.end()) ? "end()" : sstr(*FTit);
			std::string _std = (STDit == map_std.end()) ? "end()" : sstr(*STDit);
			std::cout << sstr("map_ft.upper_bound(" << x << ") == map_std.upper_bound(" << x << ")");
			checking("", &Time, _ft, _std);
		}
		#pragma endregion
		void bounds()
		{
			test_header("Lower bound / Upper bound");
			std::list<int> lst;
			for (int i = 1; i < 10; i++)
				lst.push_back((i + 1) * 3);
			ft::set<int> map_ft(lst.begin(), lst.end());
			std::set<int> map_std(lst.begin(), lst.end());
			Time.Start();
				(void)map_ft.lower_bound(-10);
				(void)map_ft.lower_bound(5);
				(void)map_ft.lower_bound(10);
				(void)map_ft.lower_bound(50);
				(void)map_ft.lower_bound(4);
				(void)map_ft.lower_bound(18);
				(void)map_ft.lower_bound(78);
				(void)map_ft.upper_bound(-10);
				(void)map_ft.upper_bound(5);
				(void)map_ft.upper_bound(10);
				(void)map_ft.upper_bound(50);
				(void)map_ft.upper_bound(4);
				(void)map_ft.upper_bound(18);
				(void)map_ft.upper_bound(78);
			Time.Stop();
			Time.Start();
				(void)map_std.lower_bound(-10);
				(void)map_std.lower_bound(5);
				(void)map_std.lower_bound(10);
				(void)map_std.lower_bound(50);
				(void)map_std.lower_bound(4);
				(void)map_std.lower_bound(18);
				(void)map_std.lower_bound(78);
				(void)map_std.upper_bound(-10);
				(void)map_std.upper_bound(5);
				(void)map_std.upper_bound(10);
				(void)map_std.upper_bound(50);
				(void)map_std.upper_bound(4);
				(void)map_std.upper_bound(18);
				(void)map_std.upper_bound(78);
			Time.Stop(true);

			bounds_lower(map_ft, map_std, -10);
			bounds_lower(map_ft, map_std, 5);
			bounds_lower(map_ft, map_std, 10);
			bounds_lower(map_ft, map_std, 50);
			const_bounds_lower(map_ft, map_std, -10);
			const_bounds_lower(map_ft, map_std, 4);
			const_bounds_lower(map_ft, map_std, 18);
			const_bounds_lower(map_ft, map_std, 78);

			bounds_upper(map_ft, map_std, -10);
			bounds_upper(map_ft, map_std, 5);
			bounds_upper(map_ft, map_std, 10);
			bounds_upper(map_ft, map_std, 50);
			const_bounds_upper(map_ft, map_std, -10);
			const_bounds_upper(map_ft, map_std, 4);
			const_bounds_upper(map_ft, map_std, 18);
			const_bounds_upper(map_ft, map_std, 78);
		}

		void range()
		{
			test_header("Range");
			std::list<int> lst;
			lst.push_back(1); lst.push_back(42); lst.push_back(42); lst.push_back(42);

			Time.Start();
				ft::set<int> map_ft(lst.begin(), lst.end());
				ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> a = map_ft.equal_range(1);
			Time.Stop();
			Time.Start();
				std::set<int> map_std(lst.begin(), lst.end());
				std::pair<std::set<int>::iterator, std::set<int>::iterator> b = map_std.equal_range(1);
			Time.Stop(true);
			checking("a.first == b.first", &Time, *a.first, *b.first);
			checking("a.second == b.second", &Time, *a.second, *b.second);
		}

		void operators()
		{
			test_header("Operators");
			std::list<int> lst;
			lst.push_back(1); lst.push_back(42); lst.push_back(42); lst.push_back(42);
			Time.Start();
				ft::set<int> map_ft(lst.begin(), lst.end()), map_ft_2;
				map_ft_2 = map_ft;
			Time.Stop();
			Time.Start();
				std::set<int> map_std(lst.begin(), lst.end()), map_std_2;
				map_std_2 = map_std;
			Time.Stop(true);
			checking("map_ft == map_std", &Time, (map_ft == map_ft_2), (map_std == map_std_2));
			checking("map_ft != map_std", &Time, (map_ft != map_ft_2), (map_std != map_std_2));
			checking("map_ft > map_std", &Time, (map_ft > map_ft_2), (map_std > map_std_2));
			checking("map_ft < map_std", &Time, (map_ft < map_ft_2), (map_std < map_std_2));
			checking("map_ft >= map_std", &Time, (map_ft >= map_ft_2), (map_std >= map_std_2));
			checking("map_ft <= map_std", &Time, (map_ft <= map_ft_2), (map_std <= map_std_2));
			
			Time.Start();
				map_ft.insert(21);
			Time.Stop();
			Time.Start();
				map_std.insert(21);
			Time.Stop(true);
			checking("map_ft == map_std", &Time, (map_ft == map_ft_2), (map_std == map_std_2));
			checking("map_ft != map_std", &Time, (map_ft != map_ft_2), (map_std != map_std_2));
			checking("map_ft > map_std", &Time, (map_ft > map_ft_2), (map_std > map_std_2));
			checking("map_ft < map_std", &Time, (map_ft < map_ft_2), (map_std < map_std_2));
			checking("map_ft >= map_std", &Time, (map_ft >= map_ft_2), (map_std >= map_std_2));
			checking("map_ft <= map_std", &Time, (map_ft <= map_ft_2), (map_std <= map_std_2));
			
			Time.Start();
				map_ft_2.insert(3);
			Time.Stop();
			Time.Start();
				map_std_2.insert(3);
			Time.Stop(true);
			checking("map_ft == map_std", &Time, (map_ft == map_ft_2), (map_std == map_std_2));
			checking("map_ft != map_std", &Time, (map_ft != map_ft_2), (map_std != map_std_2));
			checking("map_ft > map_std", &Time, (map_ft > map_ft_2), (map_std > map_std_2));
			checking("map_ft < map_std", &Time, (map_ft < map_ft_2), (map_std < map_std_2));
			checking("map_ft >= map_std", &Time, (map_ft >= map_ft_2), (map_std >= map_std_2));
			checking("map_ft <= map_std", &Time, (map_ft <= map_ft_2), (map_std <= map_std_2));
		}
		#pragma endregion
};