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
	map['a'] = 1;
	//exit(1);
	map.insert(ft::make_pair('b', 2));
	//map.insert(pr);

	return (1);
}
