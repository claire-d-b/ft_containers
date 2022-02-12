#include "check.hpp"
#include <map>
#include "Map.hpp"
#include <utility>

class TestMap
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
		TestMap()
		{
			max_test = 0;
			success_test = 0;
			failed_test = 0;
		}
		void StartTest()
		{
			main_header("Map");
			constructor();
			max_size();
			access();
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
		~TestMap() {}
		#pragma region Test
		void constructor()
		{
			test_header("Constructor : Default / Copy / Range");
			ft::pair<int, int> ft_pair[] = {ft::make_pair(0, 1), ft::make_pair(1, 0), ft::make_pair(2, 1)};
			std::pair<int, int> std_pair[] = {std::make_pair(0, 1), std::make_pair(1, 0), std::make_pair(2, 1)};
			Time.Start();
				ft::map<int, int> map_ft_1;
			Time.Stop();
			Time.Start();
				std::map<int, int> map_std_1;
			Time.Stop(true);
			checking("(default) map_ft_1 == map_std_1", &Time, (map_ft_1 == map_std_1));
			Time.Start();
				ft::map<int, int> map_ft_2(ft_pair, ft_pair + 3);
			Time.Stop();
			Time.Start();
				std::map<int, int> map_std_2(std_pair, std_pair + 3);
			Time.Stop(true);
			checking("(range) map_ft_2 == map_std_2", &Time, (map_ft_2 == map_std_2));
			Time.Start();
				ft::map<int, int> map_ft_3(map_ft_2);
			Time.Stop();
			Time.Start();
				std::map<int, int> map_std_3(map_std_2);
			Time.Stop(true);
			checking("(copy) map_ft_3 == map_std_3", &Time, (map_ft_3 == map_std_3));
			Time.Start();
				ft::map<int, int> map_ft_4;
				map_ft_4[0] = 1;
				map_ft_4[1] = 2;
				map_ft_4[2] = 3;
			Time.Stop();
			Time.Start();
				std::map<int, int> map_std_4;
				map_std_4[0] = 1;
				map_std_4[1] = 2;
				map_std_4[2] = 3;
			Time.Stop(true);
			checking("(copy) map_ft_4 == map_std_4", &Time, (map_ft_4 == map_std_4));
			Time.Start();
				ft::map<int, int> map_ft_5;
				map_ft_5 = map_ft_4;
			Time.Stop();
			Time.Start();
				std::map<int, int> map_std_5;
				map_std_5 = map_std_4;
			Time.Stop(true);
			checking("(copy) map_ft_5 == map_std_5", &Time, (map_ft_5 == map_std_5));
		}

		void max_size()
		{
			test_header("Max Size");
			Time.Start();
				ft::map<int, int> map_ft;
				(void)map_ft.max_size();
			Time.Stop();
			Time.Start();
				std::map<int, int> map_std;
				(void)map_std.max_size();
			Time.Stop(true);
			check_max("map_ft.max_size() == map_std.max_size()", &Time, map_ft.max_size(), map_std.max_size());
			Time.Start();
				ft::map<std::string, int> map_ft_2;
				(void)map_ft_2.max_size();
			Time.Stop();
			Time.Start();
				std::map<std::string, int> map_std_2;
				(void)map_std_2.max_size();
			Time.Stop(true);
			check_max("map_ft_2.max_size() == map_std_2.max_size()", &Time, map_ft_2.max_size(), map_std_2.max_size());
		}

		void access()
		{
			test_header("access []");
			Time.Start();
				ft::map<std::string, int> map_ft;
				map_ft["a"] = 1;
				map_ft["b"] = 0;
				map_ft["c"] = 42;
				map_ft["d"] = -5;
				map_ft["d"] = 11;
				map_ft["test"] = 100;
			Time.Stop();
			Time.Start();
				std::map<std::string, int> map_std;
				map_std["a"] = 1;
				map_std["b"] = 0;
				map_std["c"] = 42;
				map_std["d"] = -5;
				map_std["d"] = 11;
				map_std["test"] = 100;
			Time.Stop(true);
			checking("map_ft == map_std", &Time, map_ft == map_std);
			checking("map_ft['a'] == map_std['a']", &Time, map_ft["a"], map_std["a"]);
			checking("map_ft['d'] == map_std['d']", &Time, map_ft["d"], map_std["d"]);
			checking("map_ft['test'] == map_std['test']", &Time, map_ft["test"], map_std["test"]);
			checking("map_ft['z'] == map_std['z']", &Time, map_ft["z"], map_std["z"]);
		}

		void insert()
		{
			test_header("Insert");
			std::pair<int, int> ft_pair[] = {std::make_pair(0, 1), std::make_pair(1, 0), std::make_pair(2, 1)};
			ft::pair<int, int> std_pair[] = {ft::make_pair(0, 1), ft::make_pair(1, 0), ft::make_pair(2, 1)};
			Time.Start();
				ft::map<int, int> map_ft(std_pair, std_pair + 3);
			Time.Stop();
			Time.Start();
				std::map<int, int> map_std(ft_pair, ft_pair + 3);
			Time.Stop(true);
			checking("(Insert) map_ft == map_std", &Time, (map_ft == map_std));

			Time.Start();
				ft::map<int, int> map_ft_2(std_pair, std_pair + 3);
				map_ft_2.insert(++map_ft_2.begin(), ft::make_pair(5, 5));
			Time.Stop();
			Time.Start();
				std::map<int, int> map_std_2(ft_pair, ft_pair + 3);
				map_std_2.insert(++map_std_2.begin(), std::make_pair(5, 5));
			Time.Stop();
			checking("(One) map_ft == map_std", &Time, (map_ft == map_std));
			
			Time.Start();
				map_ft.insert(ft::make_pair(5, 0));
				map_ft.insert(ft::make_pair(10, 54));
			Time.Stop();
			Time.Start();
				map_std.insert(std::make_pair(5, 0));
				map_std.insert(std::make_pair(10, 54));
			Time.Stop(true);
			checking("(Two) map_ft == map_std", &Time, (map_ft == map_std));
		}

		void erase()
		{
			test_header("Erase");
			Time.Start();
				ft::map<std::string, int> map_ft;
				map_ft["test"] = 1;
				map_ft["a"] = 2;
				map_ft["b"] = 3;
				map_ft["c"] = 4;
				map_ft["d"] = 6;
				map_ft["e"] = 8;
			Time.Stop();
			Time.Start();
				std::map<std::string, int> map_std;
				map_std["test"] = 1;
				map_std["a"] = 2;
				map_std["b"] = 3;
				map_std["c"] = 4;
				map_std["d"] = 6;
				map_std["e"] = 8;
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

			/*Time.Start();
				map_ft.erase("a");
			Time.Stop();
			Time.Start();
				map_std.erase("a");
			Time.Stop(true);
			checking("map_ft == map_std", &Time, map_ft == map_std);*/
		}

		void swap()
		{
			test_header("Swap");
			Time.Start();
				ft::map<std::string, int> map_ft;
				ft::map<std::string, int> swap_ft;
				map_ft["a"] = 1;
				map_ft["b"] = 2;
				map_ft["c"] = 3;
				swap_ft["a"] = 42;
				swap_ft["b"] = 21;
				map_ft.swap(swap_ft);
			Time.Stop();
			Time.Start();
				std::map<std::string, int> map_std;
				std::map<std::string, int> swap_std;
				map_std["a"] = 1;
				map_std["b"] = 2;
				map_std["c"] = 3;
				swap_std["a"] = 42;
				swap_std["b"] = 21;
				map_std.swap(swap_std);
			Time.Stop(true);
			checking("map_ft == map_std", &Time, map_ft == map_std);
			checking("swap_ft == swap_std", &Time, swap_ft == swap_std);
		}

		void clear()
		{
			test_header("Clear");
			Time.Start();
				ft::map<std::string, int> map_ft;
				map_ft["a"] = 1;
				map_ft["b"] = 42;
				map_ft.clear();
			Time.Stop();
			Time.Start();
				std::map<std::string, int> map_std;
				map_std["a"] = 1;
				map_std["b"] = 42;
				map_std.clear();
			Time.Stop(true);
			checking("map_ft == map_std", &Time, map_ft == map_std);
		}

		void find()
		{
			test_header("Find");
			Time.Start();
				ft::map<std::string, int> map_ft;
				map_ft["a"] = 5;
				map_ft["b"] = 10;
				(void)map_ft.find("a")->second;
				(void)map_ft.find("z")->second;
			Time.Stop();
			Time.Start();
				std::map<std::string, int> map_std;
				map_std["a"] = 5;
				map_std["b"] = 10;
				(void)map_std.find("a")->second;
				(void)map_std.find("z")->second;
			Time.Stop(true);
			checking("map_ft.find('a') == map_std.find('a')", &Time, map_ft.find("a")->second, map_std.find("a")->second);
			/**
			 * This thing is made because find return depend of implementation of tree,
			 * so as long as the return is not equal to the existing value the implementation is valid
			 */
			int temp1 = map_ft.find("z")->second; int temp2 = map_std.find("z")->second;
			checking("map_ft.find('z') == map_std.find('z')", &Time, (temp1 != 5 && temp1 != 10), (temp2 != 5 && temp2 != 10));
		}

		void count()
		{
			test_header("Count");
			Time.Start();
				ft::map<std::string, int> map_ft;
				map_ft["a"] = 1;
				map_ft["b"] = 42;
				map_ft["b"] = 21;
				(void)map_ft.count("a");
				(void)map_ft.count("b");
				(void)map_ft.count("z");
			Time.Stop();
			Time.Start();
				std::map<std::string, int> map_std;
				map_std["a"] = 1;
				map_std["b"] = 42;
				map_std["b"] = 21;
				(void)map_std.count("a");
				(void)map_std.count("b");
				(void)map_std.count("z");
			Time.Stop(true);
			checking("map_ft.count('a') == map_std.count('a')", &Time, map_ft.count("a"), map_std.count("a"));
			checking("map_ft.count('b') == map_std.count('b')", &Time, map_ft.count("b"), map_std.count("b"));
			checking("map_ft.count('z') == map_std.count('z')", &Time, map_ft.count("z"), map_std.count("z"));
		}

		void bounds()
		{
			test_header("Lower bound / Upper bound");
			Time.Start();
				ft::map<std::string, int> map_ft;
				map_ft["a"] = 1;
				map_ft["b"] = 42;
				map_ft["c"] = 42;
				map_ft["d"] = 42;
				(void)map_ft.lower_bound("a")->first;
				(void)map_ft.lower_bound("c")->first;
				(void)map_ft.upper_bound("a")->first;
				(void)map_ft.upper_bound("c")->first;
			Time.Stop();
			Time.Start();
				std::map<std::string, int> map_std;
				map_std["a"] = 1;
				map_std["b"] = 42;
				map_std["c"] = 42;
				map_std["d"] = 42;
				(void)map_std.lower_bound("a")->first;
				(void)map_std.lower_bound("c")->first;
				(void)map_std.upper_bound("a")->first;
				(void)map_std.upper_bound("c")->first;
			Time.Stop(true);
			checking("map_ft.lower_bound() == map_std.lower_bound()", &Time, map_ft.lower_bound("a")->first, map_std.lower_bound("a")->first);
			checking("map_ft.lower_bound() == map_std.lower_bound()", &Time, map_ft.lower_bound("c")->first, map_std.lower_bound("c")->first);
			checking("map_ft.upper_bound() == map_std.upper_bound()", &Time, map_ft.upper_bound("a")->first, map_std.upper_bound("a")->first);
			checking("map_ft.upper_bound() == map_std.upper_bound()", &Time, map_ft.upper_bound("c")->first, map_std.upper_bound("c")->first);
		}

		void range()
		{
			test_header("Range");
			Time.Start();
				ft::map<std::string, int> map_ft;
				map_ft["a"] = 1;
				map_ft["b"] = 42;
				map_ft["c"] = 42;
				map_ft["d"] = 42;
				ft::pair<ft::map<std::string, int>::iterator, ft::map<std::string, int>::iterator> a = map_ft.equal_range("a");
			Time.Stop();
			Time.Start();
				std::map<std::string, int> map_std;
				map_std["a"] = 1;
				map_std["b"] = 42;
				map_std["c"] = 42;
				map_std["d"] = 42;
				std::pair<std::map<std::string, int>::iterator, std::map<std::string, int>::iterator> b = map_std.equal_range("a");
			Time.Stop(true);
			checking("a.first->first == b.first->first", &Time, a.first->first, b.first->first);
			checking("a.first->second == b.first->second", &Time, a.first->second, b.first->second);
			checking("a.second->first == b.second->first", &Time, a.second->first, b.second->first);
			checking("a.second->second == b.second->second", &Time, a.second->second, b.second->second);
		}

		void operators()
		{
			test_header("Operators");
			Time.Start();
				ft::map<std::string, int> map_ft;
				map_ft["a"] = 1;
				map_ft["b"] = 42;
				map_ft["c"] = 42;
				map_ft["d"] = 42;
				ft::map<std::string, int> map_ft_2;
				map_ft_2 = map_ft;
			Time.Stop();
			Time.Start();
				std::map<std::string, int> map_std;
				map_std["a"] = 1;
				map_std["b"] = 42;
				map_std["c"] = 42;
				map_std["d"] = 42;
				std::map<std::string, int> map_std_2;
				map_std_2 = map_std;
			Time.Stop(true);
			checking("map_ft == map_std", &Time, (map_ft == map_ft_2), (map_std == map_std_2));
			checking("map_ft != map_std", &Time, (map_ft != map_ft_2), (map_std != map_std_2));
			checking("map_ft > map_std", &Time, (map_ft > map_ft_2), (map_std > map_std_2));
			checking("map_ft < map_std", &Time, (map_ft < map_ft_2), (map_std < map_std_2));
			checking("map_ft >= map_std", &Time, (map_ft >= map_ft_2), (map_std >= map_std_2));
			checking("map_ft <= map_std", &Time, (map_ft <= map_ft_2), (map_std <= map_std_2));
			
			Time.Start();
				map_ft["e"] = 1;
			Time.Stop();
			Time.Start();
				map_std["e"] = 1;
			Time.Stop(true);
			checking("map_ft == map_std", &Time, (map_ft == map_ft_2), (map_std == map_std_2));
			checking("map_ft != map_std", &Time, (map_ft != map_ft_2), (map_std != map_std_2));
			checking("map_ft > map_std", &Time, (map_ft > map_ft_2), (map_std > map_std_2));
			checking("map_ft < map_std", &Time, (map_ft < map_ft_2), (map_std < map_std_2));
			checking("map_ft >= map_std", &Time, (map_ft >= map_ft_2), (map_std >= map_std_2));
			checking("map_ft <= map_std", &Time, (map_ft <= map_ft_2), (map_std <= map_std_2));
			
			for (ft::map<std::string, int>::iterator it = map_ft_2.begin(); it != map_ft_2.end(); it++)
				std::cout << it->first << "|" << it->second << std::endl;
			Time.Start();
				map_ft_2["e"] = 3;
			Time.Stop();
			for (ft::map<std::string, int>::iterator it = map_ft_2.begin(); it != map_ft_2.end(); it++)
				std::cout << it->first << "|" << it->second << std::endl;

			Time.Start();
				map_std_2["e"] = 3;
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