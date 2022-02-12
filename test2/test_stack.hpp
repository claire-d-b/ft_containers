#include "check.hpp"
#include <stack>
#include "Stack.hpp"

class TestStack
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
		TestStack()
		{
			max_test = 0;
			success_test = 0;
			failed_test = 0;
		}
		void StartTest()
		{
			main_header("Stack");
			constructor();
			copy_constructor();
			push_pop_top();
			operators();
			resume(max_test, success_test, failed_test);
		}
		~TestStack() {}
		#pragma region Test
		void constructor()
		{
			test_header("Constructor");
			Time.Start();
				ft::stack<int> stack_ft;
			Time.Stop();
			Time.Start();
				std::stack<int> stack_std;
			Time.Stop(true);
			checking("stack_ft.size() == stack_std.size()", &Time, stack_ft.size() == stack_std.size());
			checking("stack_ft.empty() == stack_std.empty()", &Time, stack_ft.empty() == stack_std.empty());
		}
		void copy_constructor()
		{
			test_header("Copy constructor");
			Time.Start();
				ft::stack<int> stack_ft;
				stack_ft.push(0);
				stack_ft.push(1);
				stack_ft.push(2);
				ft::stack<int> swap_ft(stack_ft);
			Time.Stop();
			Time.Start();
				std::stack<int> stack_std;
				stack_std.push(0);
				stack_std.push(1);
				stack_std.push(2);
				std::stack<int> swap_std(stack_std);
			Time.Stop(true);
			checking("stack_ft.size() == stack_std.size()", &Time, stack_ft.size() == stack_std.size());
			checking("stack_ft.empty() == stack_std.empty()", &Time, stack_ft.empty() == stack_std.empty());
			checking("stack_ft.top() == stack_std.top()", &Time, stack_ft.top(), stack_std.top());
			checking("stack_ft.size() == swap_std.size()", &Time, stack_ft.size() == swap_std.size());
			checking("stack_ft.empty() == swap_std.empty()", &Time, stack_ft.empty() == swap_std.empty());
			checking("stack_ft.top() == swap_std.top()", &Time, stack_ft.top(), swap_std.top());
			checking("stack_ft.size() == swap_ft.size()", &Time, stack_ft.size() == swap_ft.size());
			checking("stack_ft.empty() == swap_ft.empty()", &Time, stack_ft.empty() == swap_ft.empty());
			checking("stack_ft.top() == swap_ft.top()", &Time, stack_ft.top(), swap_ft.top());
		}

		void push_pop_top()
		{
			test_header("Push Pop Top");
			Time.Start();
				ft::stack<int> stack_ft;
				stack_ft.push(0);
				stack_ft.push(1);
				stack_ft.push(2);
			Time.Stop();
			Time.Start();
				std::stack<int> stack_std;
				stack_std.push(0);
				stack_std.push(1);
				stack_std.push(2);
			Time.Stop(true);
			checking("stack_ft.size() == stack_std.size()", &Time, stack_ft.size() == stack_std.size());
			checking("stack_ft.empty() == stack_std.empty()", &Time, stack_ft.empty() == stack_std.empty());
			checking("stack_ft.top() == stack_std.top()", &Time, stack_ft.top(), stack_std.top());

			Time.Start();
				stack_ft.pop();
			Time.Stop();
			Time.Start();
				stack_std.pop();
			Time.Stop(true);
			checking("stack_ft.size() == stack_std.size()", &Time, stack_ft.size() == stack_std.size());
			checking("stack_ft.top() == stack_std.top()", &Time, stack_ft.top(), stack_std.top());
		}
		void operators()
		{
			test_header("Operator");
			Time.Start();
				ft::stack<int> stack_ft;
				ft::stack<int> op_ft;
				stack_ft.push(0);
				stack_ft.push(1);
				stack_ft.push(2);
				op_ft = stack_ft;
			Time.Stop();
			Time.Start();
				std::stack<int> stack_std;
				std::stack<int> op_std;
				stack_std.push(0);
				stack_std.push(1);
				stack_std.push(2);
				op_std = stack_std;
			Time.Stop(true);
			checking("stack_ft == stack_std", &Time, (stack_ft == op_ft), (stack_std == op_std));
			checking("stack_ft != stack_std", &Time, (stack_ft != op_ft), (stack_std != op_std));
			checking("stack_ft > stack_std", &Time, (stack_ft > op_ft), (stack_std > op_std));
			checking("stack_ft < stack_std", &Time, (stack_ft < op_ft), (stack_std < op_std));
			checking("stack_ft >= stack_std", &Time, (stack_ft >= op_ft), (stack_std >= op_std));
			checking("stack_ft <= stack_std", &Time, (stack_ft <= op_ft), (stack_std <= op_std));
		}
		#pragma endregion
};