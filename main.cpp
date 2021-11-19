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
	pr._first = 'c';
	pr._second = '3';
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

	return (1);
}
