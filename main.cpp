#include "condition.hpp"
#include "iterator.hpp"
#include "iterator_vector.hpp"
#include "reverse_iterator.hpp"
#include "vector.hpp"
#include "pair.hpp"
#include "stack.hpp"
#include <vector>



#include <iostream>

#define TEST int
#define TESTED_NAMESPACE ft


int main()
{
	ft::vector<TEST> one(5, 3);
	ft::vector<TEST>::iterator it = one.begin();
	one.push_back(42);
//	one.insert(one.begin(), 42);
	it = one.begin();
	while (it != one.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
	return (1);
}
