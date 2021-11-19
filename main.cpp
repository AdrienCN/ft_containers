#include "condition.hpp"
#include "iterator.hpp"
#include "iterator_vector.hpp"
#include "reverse_iterator.hpp"
#include "iterator_map.hpp"
#include "vector.hpp"
#include "pair.hpp"
#include "stack.hpp"
#include "map.hpp"
#include <vector>
#include <stdlib.h>


#include <iostream>

#define TEST int
#define TESTED_NAMESPACE ft
#define MAP char, int

int main()
{
	ft::map<MAP> map;
	ft::pair<char, int> pr;
	pr.first = 'c';
	pr.second = '3';
	//exit(1);
	map.insert(ft::make_pair('a', 6));
	
	std::cout << "\t------" << std::endl;
	
	map.insert(ft::make_pair('d', 4));
	
	
	std::cout << "\t------" << std::endl;
	
	
	map.insert(pr);
	
	
	std::cout << "\t------" << std::endl;
	
	
	map.insert(ft::make_pair('e', 6));
	
	
	std::cout << "\t------" << std::endl;
	
	
	map.insert(ft::make_pair('b', 2));
	
	std::cout << "\t------" << std::endl;
	std::cout << "\t------" << std::endl;
	std::cout << "\t------" << std::endl;
	std::cout << "\t------" << std::endl;
	
	if (map.empty())
		std::cout << "empty" << std::endl;
	else
		std::cout << "full" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	ft::map<MAP> copy(map);
//	ft::map<MAP> range(map.begin(), map.end());
//	ft::map<MAP> assign = map;

	

	return (1);
}
