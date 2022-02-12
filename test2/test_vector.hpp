#include "check.hpp"
#include <vector>
#include "Vector.hpp"

class TestVector
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
		TestVector(void)
		{
			max_test = 0;
			success_test = 0;
			failed_test = 0;
		}
		void StartTest()
		{
			main_header("Vector");
			constructor();
			copy_constructor();
			max_size();
			resize();
			access_operator();
			front_back();
			assign();
			insert();
			erase();
			swap();
			operators();
			resume(max_test, success_test, failed_test);
		}
		~TestVector() {}
		#pragma region Test
		void constructor()
		{
			test_header("Constructor");
			Time.Start();
				ft::vector<int> vec_ft;
			Time.Stop();
			Time.Start();
				std::vector<int> vec_std;
			Time.Stop(true);
			checking("vec_ft == vec_std", &Time, vec_ft == vec_std);
			Time.Start();
				vec_ft.push_back(1);
				vec_ft.push_back(2);
				vec_ft.push_back(3);
			Time.Stop();
			Time.Start();
				vec_std.push_back(1);
				vec_std.push_back(2);
				vec_std.push_back(3);
			Time.Stop(true);
			checking("vec_ft === vec_std", &Time, vec_ft == vec_std);
		}

		void copy_constructor()
		{
			test_header("Copy constructor");
			Time.Start();
				ft::vector<int> vec_ft;
				vec_ft.push_back(1);
				vec_ft.push_back(2);
				vec_ft.push_back(3);
				ft::vector<int> swap_ft(vec_ft);
				vec_ft.push_back(4);
			Time.Stop();
			Time.Start();
				std::vector<int> vec_std;
				vec_std.push_back(1);
				vec_std.push_back(2);
				vec_std.push_back(3);
				std::vector<int> swap_std(vec_std);
				vec_std.push_back(4);
			Time.Stop(true);
			checking("vec_ft == vec_std", &Time, (vec_ft == vec_std));
			checking("swap_ft == swap_std", &Time, (swap_ft == swap_std));
			checking("vec_ft != swap_ft", &Time, (vec_ft != swap_ft));
			checking("vec_std != swap_std", &Time, (vec_std != swap_std));
		}

		void max_size()
		{
			test_header("Max size");
			Time.Start();
				ft::vector<std::string> vec_ft;
			Time.Stop();
			Time.Start();
				std::vector<std::string> vec_std;
			Time.Stop(true);
			check_max("vec_ft.max_size() == vec_std.max_size()", &Time, vec_ft.max_size(), vec_std.max_size());
			Time.Start();
				vec_ft.push_back("Hello World !");
			Time.Stop();
			Time.Start();
				vec_std.push_back("Hello World !");
			Time.Stop(true);
			check_max("vec_ft.max_size() == vec_std.max_size()", &Time, vec_ft.max_size(), vec_std.max_size());
		}

		void resize()
		{
			test_header("Resize");
			Time.Start();
				ft::vector<std::string> vec_ft;
				vec_ft.resize(10, "test");
			Time.Stop();
			Time.Start();
				std::vector<std::string> vec_std;
				vec_std.resize(10, "test");
			Time.Stop(true);
			checking("vec_ft == vec_std", &Time, (vec_ft == vec_std));
			Time.Start();
				vec_ft.resize(2, "42");
			Time.Stop();
			Time.Start();
				vec_std.resize(2, "42");
			Time.Stop(true);
			checking("vec_ft == vec_std", &Time, (vec_ft == vec_std));
		}

		void access_operator()
		{
			test_header("[] operator, at()");
			Time.Start();
				ft::vector<int> vec_ft;
				vec_ft.push_back(1);
				vec_ft.push_back(2);
				vec_ft.push_back(3);
			Time.Stop();
			Time.Start();
				std::vector<int> vec_std;
				vec_std.push_back(1);
				vec_std.push_back(2);
				vec_std.push_back(3);
			Time.Stop(true);
			checking("vec_ft[0] == vec_std[0]", &Time, vec_ft[0], vec_std[0]);
			checking("vec_ft[1] == vec_std[1]", &Time, vec_ft[1], vec_std[1]);
			checking("vec_ft[2] == vec_std[2]", &Time, vec_ft[2], vec_std[2]);
			try {
				std::cout << "vec_ft.at(100): " << vec_ft.at(100) << ": " << FAIL << std::endl;
			} catch (std::exception &e) {
				std::cout << e.what() << ": " << std::string(7, ' ') << BOLD << GREEN << GOOD << RESET << std::endl;
			}
			try {
				std::cout << "vec_std.at(100): " << vec_std.at(100) << ": " << FAIL  << std::endl;
			} catch (std::exception &e) {
				std::cout << e.what() << ": " << std::string(20, ' ') << BOLD << GREEN << GOOD << RESET << std::endl;
			}
			try {
				std::cout << "vec_ft.at(-1): " << vec_ft.at(-1) << ": " << FAIL  << std::endl;
			} catch (std::exception &e) {
				std::cout << e.what() << ": " << std::string(8, ' ') << BOLD << GREEN << GOOD << RESET << std::endl;
			}
			try {
				std::cout << "vec_std.at(-1): " << vec_std.at(-1) << ": " << FAIL  << std::endl;
			} catch (std::exception &e) {
				std::cout << e.what() << ": " << std::string(21, ' ') << BOLD << GREEN << GOOD << RESET << std::endl;
			}
		}

		void front_back()
		{
			test_header("Front / Back");
			Time.Start();		
				ft::vector<int> vec_ft;
				vec_ft.push_back(1);
				vec_ft.push_back(2);
				vec_ft.push_back(3);
			Time.Stop();
			Time.Start();
				std::vector<int> vec_std;
				vec_std.push_back(1);
				vec_std.push_back(2);
				vec_std.push_back(3);
			Time.Stop(true);
			checking("vec_ft.front() == vec_std.front()", &Time, vec_ft.front(), vec_std.front());
			checking("vec_ft.back() == vec_std.back()", &Time, vec_ft.front(), vec_std.front());
		}

		void assign()
		{
			test_header("Assign");
			std::string test[] = {"Hello", "world", "my", "name", "is", "bob", "!"};
			Time.Start();
				ft::vector<std::string> vec_ft;
				vec_ft.assign(test, test + 7);
			Time.Stop();
			Time.Start();
				std::vector<std::string> vec_std;
				vec_std.assign(test, test + 7);
			Time.Stop(true);
			checking("vec_ft == vec_std", &Time, vec_ft == vec_std);
			Time.Start();
				vec_ft.assign(10, "?");
			Time.Stop();
			Time.Start();
				vec_std.assign(10, "?");
			Time.Stop(true);
			checking("vec_ft == vec_std", &Time, vec_ft == vec_std);
		}

		void insert()
		{
			test_header("Insert");
			int test[] = {1, 2, 3};
			Time.Start();
				ft::vector<int> vec_ft;
				vec_ft.insert(vec_ft.begin(), 42);
				vec_ft.insert(vec_ft.end(), 21);
				vec_ft.insert(vec_ft.begin(), 10);
				vec_ft.insert(vec_ft.begin() + 1, 11);
				vec_ft.insert(vec_ft.begin() + 2, (size_t)3, 0);
				vec_ft.insert(vec_ft.begin() + 1, test, test + 3);
			Time.Stop();
			Time.Start();
				std::vector<int> vec_std;
				vec_std.insert(vec_std.begin(), 42);
				vec_std.insert(vec_std.end(), 21);
				vec_std.insert(vec_std.begin(), 10);
				vec_std.insert(vec_std.begin() + 1, 11);
				vec_std.insert(vec_std.begin() + 2, (size_t)3, 0);
				vec_std.insert(vec_std.begin() + 1, test, test + 3);
			Time.Stop(true);
			checking("vec_ft == vec_std", &Time, vec_ft == vec_std);
		}

		void erase()
		{
			test_header("Erase");
			std::string test[] = {"Hello", "world", "my", "name", "is", "bob", "!"};
			Time.Start();
				ft::vector<std::string> vec_ft;
				vec_ft.assign(test, test + 7);
				vec_ft.erase(vec_ft.begin() + 2);
			Time.Stop();
			Time.Start();
				std::vector<std::string> vec_std;
				vec_std.assign(test, test + 7);
				vec_std.erase(vec_std.begin() + 2);
			Time.Stop(true);
			checking("vec_ft == vec_std", &Time, vec_ft == vec_std);
			Time.Start();
				vec_ft.clear();
			Time.Stop();
			Time.Start();
				vec_std.clear();
			Time.Stop(true);
			checking("vec_ft == vec_std", &Time, vec_ft == vec_std);
		}

		void swap()
		{
			test_header("Swap");
			Time.Start();
				ft::vector<int> vec_ft;
				ft::vector<int> swap_ft;
				vec_ft.push_back(1);
				vec_ft.push_back(2);
				vec_ft.push_back(3);
				swap_ft.push_back(42);
				swap_ft.push_back(43);
				vec_ft.swap(swap_ft);
			Time.Stop();
			Time.Start();
				std::vector<int> vec_std;
				std::vector<int> swap_std;
				vec_std.push_back(1);
				vec_std.push_back(2);
				vec_std.push_back(3);
				swap_std.push_back(42);
				swap_std.push_back(43);
				vec_std.swap(swap_std);
			Time.Stop(true);
			checking("vec_ft == vec_std", &Time, vec_ft == vec_std);
			checking("swap_ft == swap_std", &Time, swap_ft == swap_std);
		}

		void operators()
		{
			test_header("Operators");
			Time.Start();
				ft::vector<int> vec_ft;
				ft::vector<int> op_ft;
				vec_ft.push_back(1);
				vec_ft.push_back(2);
				vec_ft.push_back(3);
				op_ft = vec_ft;
			Time.Stop();
			Time.Start();
				std::vector<int> vec_std;
				std::vector<int> op_std;
				vec_std.push_back(1);
				vec_std.push_back(2);
				vec_std.push_back(3);
				op_std = vec_std;
			Time.Stop(true);
			checking("vec_ft == vec_std", &Time, (vec_ft == op_ft), (vec_std == op_std));
			checking("vec_ft != vec_std", &Time, (vec_ft != op_ft), (vec_std != op_std));
			checking("vec_ft > vec_std", &Time, (vec_ft > op_ft), (vec_std > op_std));
			checking("vec_ft < vec_std", &Time, (vec_ft < op_ft), (vec_std < op_std));
			checking("vec_ft >= vec_std", &Time, (vec_ft >= op_ft), (vec_std >= op_std));
			checking("vec_ft <= vec_std", &Time, (vec_ft <= op_ft), (vec_std <= op_std));
			
			Time.Start();
				vec_ft.push_back(42);
			Time.Stop();
			Time.Start();
				vec_std.push_back(42);
			Time.Stop(true);
			checking("vec_ft == vec_std", &Time, (vec_ft == op_ft), (vec_std == op_std));
			checking("vec_ft != vec_std", &Time, (vec_ft != op_ft), (vec_std != op_std));
			checking("vec_ft > vec_std", &Time, (vec_ft > op_ft), (vec_std > op_std));
			checking("vec_ft < vec_std", &Time, (vec_ft < op_ft), (vec_std < op_std));
			checking("vec_ft >= vec_std", &Time, (vec_ft >= op_ft), (vec_std >= op_std));
			checking("vec_ft <= vec_std", &Time, (vec_ft <= op_ft), (vec_std <= op_std));
			
			Time.Start();
				op_ft.push_back(43);
			Time.Stop();
			Time.Start();
				op_std.push_back(43);
			Time.Stop(true);
			checking("vec_ft == vec_std", &Time, (vec_ft == op_ft), (vec_std == op_std));
			checking("vec_ft != vec_std", &Time, (vec_ft != op_ft), (vec_std != op_std));
			checking("vec_ft > vec_std", &Time, (vec_ft > op_ft), (vec_std > op_std));
			checking("vec_ft < vec_std", &Time, (vec_ft < op_ft), (vec_std < op_std));
			checking("vec_ft >= vec_std", &Time, (vec_ft >= op_ft), (vec_std >= op_std));
			checking("vec_ft <= vec_std", &Time, (vec_ft <= op_ft), (vec_std <= op_std));
		}
		#pragma endregion
};
