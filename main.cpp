#include <iostream>
#include <map>
#include <iterator>
#include "includes/Map.hpp"

# define RESET   		"\033[0m"
# define RED     		"\033[31m"
# define GREEN   		"\033[32m"
# define YELLOW  		"\033[33m"
# define BLUE    		"\033[34m"
# define BOLDRED     	"\033[1m\033[31m"
# define BOLDGREEN   	"\033[1m\033[32m"
# define BOLDYELLOW  	"\033[1m\033[33m"
# define BOLDBLUE    	"\033[1m\033[34m"
# define COLOR(COL_VAL)	std::cout << COL_VAL;

template<class M>
void	display_map(M &map)
{
	std::cout << "Display map :\n";

	for (typename M::iterator it = map.begin(); it != map.end(); ++it)
		std::cout << it->first << " : " << it->second << "\n";

	std::cout << "Size : " << map.size() << std::endl;
	std::cout << "Max size : " << map.max_size() << std::endl;
	std::cout << "Empty ? : " << map.empty() << "\n\n";
}

void	test_insertmap_std_intint(std::map<int, int> &map)
{
	map.insert(std::make_pair(3, 4));
	map.insert(std::make_pair(1, 2));
	map.insert(std::make_pair(0, 0));
	map.insert(std::make_pair(5, 6));
	map.insert(std::make_pair(7, 8));
}

void	test_insertmap_ft_intint(ft::map<int, int> &map)
{
	map.insert(ft::make_pair(3, 4));
	map.insert(ft::make_pair(1, 2));
	map.insert(ft::make_pair(0, 0));
	map.insert(ft::make_pair(5, 6));
	map.insert(ft::make_pair(7, 8));
}

void	test_insertmap_std_intstr(std::map<int, std::string> &map)
{
	map.insert(std::make_pair(3, "three"));
	map.insert(std::make_pair(1, "one"));
	map.insert(std::make_pair(5, "five"));
	map.insert(std::make_pair(7, "seven"));
}

void	test_insertmap_ft_intstr(ft::map<int, std::string> &map)
{
	map.insert(ft::make_pair<int, std::string>(3, "three"));
	map.insert(ft::make_pair<int, std::string>(1, "one"));
	map.insert(ft::make_pair<int, std::string>(5, "five"));
	map.insert(ft::make_pair<int, std::string>(7, "seven"));
}

template <class M>
void	test_find(M &map)
{
	std::cout << "\nfind 5 : " << (map.find(5))->second << "\n"; 
	std::cout << "find 6 : ";
	if (map.find(6) == map.end())
		std::cout << "Cannot find key 6\n"; 
	std::cout << "map count(5) : " << map.count(5) << "\n"; 
	std::cout << "map count(6) : " << map.count(6) << "\n"; 
	std::cout << "map[5] : " << map[5] << "\n"; 
	std::cout << "map[6] : " << map[6] << "\n"; 
	std::cout << "map count(5) : " << map.count(5) << "\n"; 
	std::cout << "map count(6) : " << map.count(6) << "\n";
	std::cout << "map[6] = 42 : "; 
	map[6] = 42;
	std::cout << "map[6] - " << map[6] << "\n"; 
}

template <class M>
void	test_erase_map(M &map)
{
	std::cout << "\nTest erase map 5 \n";
	map.erase(5);
	display_map(map);
	std::cout << "\nTest erase begin\n";
	map.erase(map.begin());
	display_map(map);
	std::cout << "\nTest erase begin to find(6)\n";
	map.erase(map.begin(), map.find(6));
	display_map(map);
	std::cout << "\nTest erase begin to end\n";
	map.erase(map.begin(), map.end());
	display_map(map);
}

void	test_map_int_int()
{
	std::map<int, int> std_map;
	ft::map<int, int> ft_map;

	COLOR(BOLDYELLOW) test_insertmap_std_intint(std_map);
	display_map(std_map);

	COLOR(BOLDGREEN) test_insertmap_ft_intint(ft_map);
	display_map(ft_map);

	COLOR(BOLDYELLOW) test_find(std_map);
	COLOR(BOLDGREEN) test_find(ft_map);

	COLOR(BOLDYELLOW) test_erase_map(std_map);
	COLOR(BOLDGREEN) test_erase_map(ft_map);
}

void	test_map_int_string()
{
	std::map<int, std::string> std_map;
	ft::map<int, std::string> ft_map;

	COLOR(BOLDYELLOW) test_insertmap_std_intstr(std_map);
	display_map(std_map);

	COLOR(BOLDGREEN) test_insertmap_ft_intstr(ft_map);
	display_map(ft_map);

	COLOR(BOLDYELLOW) test_erase_map(std_map);
	COLOR(BOLDGREEN) test_erase_map(ft_map);
}

template <class M>
void	test_plus_less(M &map)
{

	std::cout << "it begin++ loop :\n";

	for (typename M::iterator it_beg = map.begin(); it_beg != map.end(); it_beg++)
		std::cout << it_beg->first << " : " << it_beg->second << "\n";


	std::cout << "it end-- loop :\n";

	typename M::iterator it = map.end();
	
	it--;

	while (it-- != map.begin())
	{
		std::cout << it->first << " : " << it->second << "\n";
	}
}

template <class M>
void	test_plus_less_rev(M &map)
{

	std::cout << "it rbegin++ loop :\n";

	for (typename M::reverse_iterator it_beg = map.rbegin(); it_beg != map.rend(); it_beg++)
		std::cout << it_beg->first << " : " << it_beg->second << "\n";


	std::cout << "it rend-- loop :\n";

	typename M::reverse_iterator it = map.rend();

	while (--it != map.rbegin())
	{
		std::cout << it->first << " : " << it->second << "\n";
	}
	std::cout << it->first << " : " << it->second << "\n";
}

void	test_iterator()
{
	std::map<int, std::string> std_map;
	ft::map<int, std::string> ft_map;
	
	test_insertmap_std_intstr(std_map);
	test_insertmap_ft_intstr(ft_map);

	COLOR(BOLDYELLOW) test_plus_less(std_map);
	COLOR(BOLDGREEN) test_plus_less(ft_map);
}

void	test_reverse_iterator()
{
	std::map<int, std::string> std_map;
	ft::map<int, std::string> ft_map;
	
	test_insertmap_std_intstr(std_map);
	test_insertmap_ft_intstr(ft_map);

	COLOR(BOLDYELLOW) test_plus_less_rev(std_map);
	COLOR(BOLDGREEN) test_plus_less_rev(ft_map);
}

void	test_map_bounds_val(int val)
{
	std::map<int, int> std_map;
	ft::map<int, int> ft_map;

	test_insertmap_std_intint(std_map);
	test_insertmap_ft_intint(ft_map);

	COLOR(BOLDYELLOW)	std::cout << "Upperbound std : " << (std_map.upper_bound(val))->first << "\n";
	COLOR(BOLDGREEN)
	if ((ft_map.upper_bound(val)) != ft_map.end())
		std::cout << "Upperbound ft : " << (ft_map.upper_bound(val))->first << "\n";
	else 
		std::cout << "Is map end\n";

	COLOR(BOLDYELLOW)	std::cout << "Lower std : " << (std_map.lower_bound(val))->first << "\n";
	COLOR(BOLDGREEN)	
	if ((ft_map.lower_bound(val)) != ft_map.end())
		std::cout << "Lower ft : " << (ft_map.lower_bound(val))->first << "\n";
	else 
		std::cout << "Is map end\n";

	COLOR(BOLDYELLOW)	std::cout << "Equal std : " << (std_map.equal_range(val)).first->first << " - " << (std_map.equal_range(val)).second->first  << "\n";
	COLOR(BOLDGREEN)	
	if ((ft_map.equal_range(val)).first != ft_map.end() && (ft_map.equal_range(val)).second != ft_map.end())
		std::cout << "Equal ft : " << (ft_map.equal_range(val)).first->first << " - " << (ft_map.equal_range(val)).second->first  << "\n";
	else 
		std::cout << "Is map end\n";
}

void	test_map_bounds()
{
	COLOR(BLUE) std::cout << "\nTest map bounds 5 :\n";
	test_map_bounds_val(5);
	COLOR(BLUE) std::cout << "\nTest map bounds 0 :\n";
	test_map_bounds_val(0);
	COLOR(BLUE) std::cout << "\nTest map bounds -5 :\n";
	test_map_bounds_val(-5);
	COLOR(BLUE) std::cout << "\nTest map bounds 42 :\n";
	test_map_bounds_val(42);

}

template <class M>
void	test_swap_m(M &map_one, M &map_two)
{
	std::cout << "display map one :\n";
	display_map(map_one);
	std::cout << "display map two :\n";
	display_map(map_two);

	std::cout << "Swap map one <-> map two\n\n";
	map_one.swap(map_two);

	std::cout << "display map one :\n";
	display_map(map_one);
	std::cout << "display map two :\n";
	display_map(map_two);

}

template <class M>
void	init_map(M &map_one, M &map_two)
{
	map_one[0] = 1; 
	map_one[2] = 3; 
	map_one[4] = 5; 
	map_one[6] = 7; 
	map_two[8] = 9;
	map_two[10] = 11;
	map_two[12] = 13;
	map_two[14] = 15;
}

void	test_swap()
{
	std::map<int, int> std_map_one;
	std::map<int, int> std_map_two;
	ft::map<int, int> ft_map_one;
	ft::map<int, int> ft_map_two;

	init_map(std_map_one, std_map_two);
	init_map(ft_map_one, ft_map_two);

	COLOR(BOLDYELLOW) test_swap_m(std_map_one, std_map_two); 
	COLOR(BOLDGREEN) test_swap_m(ft_map_one, ft_map_two);

	COLOR(BLUE)	std::cout << "Test comparison operator \n";

	// std_map_two = std_map_one;
	// ft_map_two = ft_map_one;

	COLOR(BOLDYELLOW)	std::cout << "Operator == std : " << (std_map_one == std_map_two) << "\n";
	COLOR(BOLDGREEN)	std::cout << "Operator == ft : " << (ft_map_one == ft_map_two) << "\n";
	COLOR(BOLDYELLOW)	std::cout << "Operator != std : " << (std_map_one != std_map_two) << "\n";
	COLOR(BOLDGREEN)	std::cout << "Operator != ft : " << (ft_map_one != ft_map_two) << "\n";
	COLOR(BOLDYELLOW)	std::cout << "Operator < std : " << (std_map_one < std_map_two) << "\n";
	COLOR(BOLDGREEN)	std::cout << "Operator < ft : " << (ft_map_one < ft_map_two) << "\n";
	COLOR(BOLDYELLOW)	std::cout << "Operator > std : " << (std_map_one > std_map_two) << "\n";
	COLOR(BOLDGREEN)	std::cout << "Operator > ft : " << (ft_map_one > ft_map_two) << "\n";
	COLOR(BOLDYELLOW)	std::cout << "Operator >= std : " << (std_map_one >= std_map_two) << "\n";
	COLOR(BOLDGREEN)	std::cout << "Operator >= ft : " << (ft_map_one >= ft_map_two) << "\n";
	COLOR(BOLDYELLOW)	std::cout << "Operator <= std : " << (std_map_one <= std_map_two) << "\n";
	COLOR(BOLDGREEN)	std::cout << "Operator <= ft : " << (ft_map_one <= ft_map_two) << "\n";
}

void	test_input_iterator()
{
	COLOR(BOLDYELLOW)
	std::map<int, int> std_map;
	std_map.insert(std::make_pair(0, 1));
	std_map.insert(std::make_pair(1, 2));
	std_map.insert(std::make_pair(3, 4));

	std::map<int, int>::iterator std_beg = std_map.begin();
	std::map<int, int>::iterator std_end = std_map.end();

	std::map<int, int> std_map_2(std_beg, std_end);
	display_map(std_map_2);

	COLOR(BOLDGREEN)
	ft::map<int, int> ft_map;
	ft_map.insert(ft::make_pair(0, 1));
	ft_map.insert(ft::make_pair(1, 2));
	ft_map.insert(ft::make_pair(3, 4));

	ft::map<int, int>::iterator ft_beg = ft_map.begin();
	ft::map<int, int>::iterator ft_end = ft_map.end();

	ft::map<int, int> ft_map_2(ft_beg, ft_end);
	display_map(ft_map_2);
}

int main()
{
	COLOR(BLUE) std::cout << "Test map <int, int>\n";
	test_map_int_int();

	COLOR(BLUE) std::cout << "\nTest map <int, string>\n";
	test_map_int_string();

	COLOR(BLUE) std::cout << "\nTest iterator functions\n";
	test_iterator();

	COLOR(BLUE) std::cout << "\nTest reverse iterator functions\n";
	test_reverse_iterator();
	
	COLOR(BLUE) std::cout << "\nTest map bounds\n";
	test_map_bounds();

	COLOR(BLUE) std::cout << "\nTest input iterator\n";
	test_input_iterator();
	
	COLOR(BLUE) std::cout << "\nTest swap and op\n";
	test_swap();

	COLOR(RESET)
}
