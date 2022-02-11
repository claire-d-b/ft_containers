#include "Map.hpp"

int main()
{
	ft::map< int, int > map;
    ft::pair< int, int > node0(8, 8);
    ft::pair< int, int > node1(18, 18);
    ft::pair< int, int > node2(5, 5);
    ft::pair< int, int > node3(15, 15);
    ft::pair< int, int > node4(17, 17);
    ft::pair< int, int > node5(25, 25);
    ft::pair< int, int > node6(40, 40);
    ft::pair< int, int > node7(80, 80);
    ft::pair< int, int > node8(3, 3);
    ft::pair< int, int > node9(10, 10);
	map.insert(node0);
	map.insert(node1);
	map.insert(node2);
	map.insert(node3);
	map.insert(node4);
	map.insert(node5);
	map.insert(node6);
	map.insert(node7);
	map.insert(node8);
	map.insert(node9);
	map.print();
	map.erase(node5.first);
	map.erase(node2.first);
	map.erase(node4.first);
	map.erase(node1.first);
	map.erase(node7.first);
	map.erase(node8.first);
	map.erase(node6.first);
	map.erase(node0.first);
	map.erase(node3.first);
	map.erase(node9.first);
	//bst.deleteNode(node9.val);
    std::cout << "********" << std::endl;
	map.print();
	//bst.freeNodes(bst.getRoot());
	return 0;
}