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



#include <iostream>

#define TEST int
#define TESTED_NAMESPACE ft
#define MAP int, int

int main()
{
	ft::map<MAP> map;
	ft::vector<TEST> one(5, 3);
	std::vector<TEST> std(5, 3);
	for (size_t i = 0; i < one.size(); i++)
	{
		one[i] = i + 1;
		std[i] = i + 1;
		std::cout << one[i] << std::endl;
	}
	std::cout << "------end--------" << std::endl;
	std::vector<TEST>::reverse_iterator ite_std = std.rbegin();
	ft::vector<TEST>::reverse_iterator ite_one = one.rbegin();
	while (ite_std != std.rend())
	{
		
		std::cout << "std: " << *ite_std << std::endl;
		std::cout << "moi : "<< *ite_one << std::endl;
		std::cout << "-------" << std::endl;
		ite_std++;
		ite_one++;
	}
	return (1);
}
