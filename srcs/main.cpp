#include "Stack.hpp"
#include "Vector.hpp"
#include "Map.hpp"
#include <algorithm>
#include <vector>
#include <list>
#include <map>

void map_tests(void)
{
    ft::map<float, std::string> map;
    ft::map<float, std::string> mapcopy;
    ft::map<char, int> map2;
    for (size_t i = 0; i < 8; i++)
        map.insert(ft::pair< float, std::string >(i, std::string("test")));

    std::cout << "*************" << std::endl;
    for (ft::map<float, std::string>::iterator it = map.begin(); it != map.end(); it++)
        std::cout << it->first << "|" << it->second << std::endl;
    std::cout << "*************" << std::endl;
    std::cout << map2.empty() << std::endl;
    std::cout << "*************" << std::endl;
    map = mapcopy;
    std::cout << "*************" << std::endl;
    for (ft::map<float, std::string>::iterator it = map.begin(); it != map.end(); it++)
        std::cout << it->first << "|" << it->second << std::endl;
    std::cout << "*************" << std::endl;
    map2.erase(map2.begin(), ++map2.begin());
    std::cout << "*************" << std::endl;
    for (ft::map<float, std::string>::reverse_iterator it = map.rbegin(); it != map.rend(); --it)
        std::cout << it->first << "|" << it->second << std::endl;
    std::cout << "*************" << std::endl;
    map.erase(map.begin(), map.end());
    std::cout << "*************" << std::endl;
    for (ft::map<float, std::string>::iterator it = map.begin(); it != map.end(); it++)
        std::cout << it->first << "|" << it->second << std::endl;
    std::cout << "*************" << std::endl;
    for (ft::map<float, std::string>::iterator it = mapcopy.begin(); it != mapcopy.end(); it++)
        std::cout << it->first << "|" << it->second << std::endl;
    std::cout << "*************" << std::endl;
    map.swap(mapcopy);
    std::cout << "*************" << std::endl;
    for (ft::map<float, std::string>::iterator it = map.begin(); it != map.end(); it++)
        std::cout << it->first << "|" << it->second << std::endl;
    for (ft::map<float, std::string>::iterator it = mapcopy.begin(); it != mapcopy.end(); it++)
        std::cout << it->first << "|" << it->second << std::endl;
    std::cout << "*************" << std::endl;
    std::cout << (map == mapcopy) << std::endl;
    std::cout << "*************" << std::endl;
    map.clear();
    std::cout << "*************" << std::endl;
    for (ft::map<float, std::string>::iterator it = map.begin(); it != map.end(); it++)
        std::cout << it->first << "|" << it->second << std::endl;
    std::cout << "*************" << std::endl;
    ft::map<int, int > maps;
    ft::pair< int, int > pair1(4, 80);
    ft::pair< int, int > pair2(7, 50);
    ft::map< int, int > mapp;
    ft::pair< int, int > pair3(5, 10);
    ft::pair< int, int > pair4(1, 20);
    ft::pair< int, int > pair5(2, 30);
    ft::pair< int, int > pair6(3, 40);
    mapp.insert(pair1);
    mapp.insert(pair3);
    mapp.insert(pair4);
    mapp.insert(pair5);
    mapp.insert(pair6);
    for(ft::map<int, int>::iterator it = mapp.begin(); it != mapp.end(); it++)
        std::cout << it->first << "|" << it->second << std::endl;
    mapp.insert(++mapp.begin(), pair2);
    for(ft::map<int, int>::iterator it = maps.begin(); it != maps.end(); it++)
        std::cout << it->first << "|" << it->second << std::endl;
    maps.erase(maps.rbegin(), maps.rend());
    mapp.erase(3);
    mapp.erase(mapp.begin());
    for(ft::map<int, int>::iterator it = mapp.begin(); it != mapp.end(); it++)
        std::cout << it->first << "|" << it->second << std::endl;
    for(ft::map<int, int>::iterator it = maps.begin(); it != maps.end(); it++)
        std::cout << it->first << "|" << it->second << std::endl;
}

void stack_tests(void)
{
    ft::stack< int > stack1;
    ft::stack< int > stack2;
    std::cout << "*************" << std::endl;
    std::cout << stack1.empty() << std::endl;
    std::cout << "*************" << std::endl;
    std::cout << stack1.size() << std::endl;
    std::cout << "*************" << std::endl;
    ft::stack< int > stackempty;
    stack1.push(16);
    std::cout << "*************" << std::endl;
    stackempty.push(1);
    std::cout << "**********" << std::endl;
    std::cout << stack1.top() << std::endl;
    stack1.pop();
    std::cout << "**********" << std::endl;
    for (size_t i = 0; i < 10; i++)
        stack2.push(i * 10);
    std::cout << "**********" << std::endl;
    std::cout << stack2.top() << std::endl;
}

void vector_tests(void)
{
    unsigned long size = 5;
    ft::vector< char > vector1(size);
    for (unsigned long i = 0; i < vector1.size(); i++)
        vector1[i] = '@';
    for (unsigned long i = 0; i < vector1.size(); i++)
        std::cout << vector1[i] << std::endl;

    ft::vector< char > vectorCopy(vector1);
    ft::vector< char > vectorAssign;
    vectorAssign = vector1;
    for (unsigned long i = 0; i < vectorCopy.capacity(); i++)
        vectorCopy[i] = 'a';
    for (unsigned long i = 0; i < vectorCopy.capacity(); i++)
        std::cout << vectorCopy[i] << std::endl;
    std::cout << "*************" << std::endl;
    for (unsigned long i = 0; i < vectorAssign.capacity(); i++)
        vectorAssign[i] = 'b';
    for (unsigned long i = 0; i < vectorAssign.capacity(); i++)
        std::cout << vectorAssign[i] << std::endl;
    std::cout << "*************" << std::endl;
    std::cout << vectorCopy.size() << std::endl;
    std::cout << "*************" << std::endl;
    std::cout << vectorCopy.empty() << std::endl;
    vectorAssign.push_back('x');
    vectorCopy.push_back('y');
    std::cout << "*************" << std::endl;
    std::cout << vectorCopy.size() << std::endl;
    std::cout << "*************" << std::endl;
    std::cout << vectorAssign.size() << std::endl;
    std::cout << "*************" << std::endl;
    std::cout << vectorAssign.at(5) << std::endl;
    std::cout << "*************" << std::endl;
    std::cout << vectorCopy.at(5) << std::endl;
    std::cout << "*************" << std::endl;
    for (unsigned long i = 0; i < vectorAssign.capacity(); i++)
        std::cout << vectorAssign[i] << std::endl;
    std::cout << "*************" << std::endl;
    for (unsigned long i = 0; i < vectorAssign.capacity(); i++)
        std::cout << vectorCopy[i] << std::endl;
    std::cout << "*************" << std::endl;
    std::cout << vectorAssign.back() << std::endl;
    std::cout << "*************" << std::endl;
    std::cout << vectorCopy.back() << std::endl;
    vectorAssign.pop_back();
    vectorCopy.pop_back();
    std::cout << "*************" << std::endl;
    for (unsigned long i = 0; i < vectorAssign.capacity(); i++)
        std::cout << vectorAssign[i] << std::endl;
    std::cout << "*************" << std::endl;
    for (unsigned long i = 0; i < vectorCopy.capacity(); i++)
        std::cout << vectorCopy[i] << std::endl;
    std::cout << "*************" << std::endl;
    std::cout << vectorAssign.front() << std::endl;
    std::cout << "*************" << std::endl;
    std::cout << vectorCopy.front() << std::endl;
    std::cout << "*************" << std::endl;
    std::cout << *vectorAssign.data() << std::endl;
    std::cout << "*************" << std::endl;
    std::cout << *vectorCopy.data() << std::endl;
    std::cout << "*************" << std::endl;
    std::cout << vectorAssign.size() << std::endl;
    std::cout << "*************" << std::endl;
    std::cout << vectorAssign.capacity() << std::endl;
    std::cout << "*************" << std::endl;
    std::cout << vectorAssign.max_size() << std::endl;
    std::cout << "*************" << std::endl;
    ft::vector<int *> vectorNb(5);
    std::vector<int *> realVector(5);
    std::cout << vectorNb.max_size() << std::endl;
    std::cout << "*************" << std::endl;
    std::cout << realVector.max_size() << std::endl;
    std::cout << "*************" << std::endl;
    vectorAssign.resize(3, '0');
    for (unsigned long i = 0; i < vectorAssign.capacity(); i++)
        std::cout << vectorAssign[i] << std::endl;
    std::cout << "*************" << std::endl;
    vectorCopy.resize(15, '*');
    std::cout << "*************" << std::endl;
    for (unsigned long i = 0; i < vectorCopy.capacity(); i++)
        std::cout << vectorCopy[i] << std::endl;
    for (unsigned long i = 0; i < vectorAssign.capacity(); i++)
        std::cout << vectorAssign[i] << std::endl;
    std::cout << "*************" << std::endl;
    vectorCopy.assign(7, '$');
    for (unsigned long i = 0; i < vectorCopy.capacity(); i++)
        std::cout << vectorCopy[i] << std::endl;
    std::cout << "*************" << std::endl;
    vectorCopy.insert(vectorCopy.begin() + 3, '0');
    vectorCopy.insert(vectorCopy.begin() + 8, vectorAssign.begin(), vectorAssign.end());
    vectorCopy.insert(vectorCopy.begin() + 4, 3, '0');
    for (unsigned long i = 0; i < vectorCopy.capacity(); i++)
        std::cout << vectorCopy[i] << std::endl;
    std::cout << "*************" << std::endl;
    std::cout << *vectorCopy.erase(vectorCopy.begin() + 3, vectorCopy.begin() + 7) << std::endl;
    std::cout << "*************" << std::endl;
    for (unsigned long i = 0; i < vectorCopy.capacity(); i++)
        std::cout << vectorCopy[i] << std::endl;
    std::cout << "*************" << std::endl;
    std::cout << *vectorCopy.erase(vectorCopy.begin()) << std::endl;
    std::cout << "*************" << std::endl;
    for (unsigned long i = 0; i < vectorCopy.capacity(); i++)
        std::cout << vectorCopy[i] << std::endl;
    ft::vector< float > swapf;
    ft::vector< float > swapc;
    swapf.assign(5, 0.02f);
    swapc.assign(6, 0.15f);
    swapf.swap(swapc);
    ft::vector< int > int1;
    ft::vector< int > int2;
    int1.assign(5, 2);
    int2.assign(6, 5);
    std::cout << "*************" << std::endl;
    for (unsigned long i = 0; i < swapf.capacity(); i++)
        std::cout << swapf[i] << std::endl;
    std::cout << "*************" << std::endl;
    for (unsigned long i = 0; i < swapc.capacity(); i++)
        std::cout << swapc[i] << std::endl;
    swapc.clear();
    std::list< int > list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    ft::vector< int > listV(list.begin(), list.end());
    std::cout << "*************" << std::endl;
    for (unsigned long i = 0; i < listV.capacity(); i++)
        std::cout << listV[i] << std::endl;
}

int main( void )
{
    stack_tests();
    vector_tests();
    map_tests();
    return 0;
}