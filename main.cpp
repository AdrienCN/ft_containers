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
#include <string>


#include <iostream>

#define TEST int
#define TESTED_NAMESPACE ft
#define MAP char, int
#define MAP_PAIR ft::pair<const char, int>

int main()
{
	//ft::map<MAP> map;
	ft::map<char, std::string> map;
/*
	char c = 'a';
	for (int i  = 5; i > 0; i--)
	{	
		map.insert(ft::make_pair(c, 6));
		c += 1;
	}

	ft::map<MAP> range(map.begin(), map.end());
	ft::map<MAP> copy(map);
	ft::map<MAP> assign = map;
*/
	map['a'] = "coucou";


	/*
	//exit(1);
	map.insert(ft::make_pair('e', 6));

	std::cout << "\t------" << std::endl;

	map.insert(ft::make_pair('b', 4));


	std::cout << "\t------" << std::endl;


	map.insert(ft::make_pair('d', 6));


	std::cout << "\t------" << std::endl;


	map.insert(ft::make_pair('a', 6));


	std::cout << "\t------" << std::endl;


	map.insert(ft::make_pair('c', 2));

	std::cout << "\t------" << std::endl;
	map.insert(ft::make_pair('z', 2));

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
	ft::map<MAP>::iterator ite = map.end();
	ft::map<MAP>::iterator it = map.begin();

	std::cout << "map.size() = " << map.size() << std::endl;
	std::cout << "map.begin()->first = " << map.begin()->first << " | (--map.end()))->first = " << (--(map.end()))->first << std::endl;
	unsigned long a = 0 ;
	while (ite != map.rend())// && a <= map.size())
	{
		std::cout << "(ite)->first =  (" << ite->first << ") | a = " << map.size() - a << std::endl;

		ft::node<MAP_PAIR> node = *(ite._ptr);
		

		std::cout << "-Left : ";
		if (node.left)
			std::cout << "(" << node.left->pr.first << ")";
		else
			std::cout << "(NULL)";
		std::cout << "     | -Right : ";
		if(node.right)
			std::cout << "(" << node.right->pr.first << ")";
		else
			std::cout << "(NULL)";

		std::cout << "     | -Parent : ";
		if (node.parent)
			std::cout << "(" << node.parent->pr.first << ")" << std::endl;
		else
			std::cout << "(NULL)" << std::endl;

		if (ite == map.begin())
			break;
		--ite;
		a++;
	}

	std::cout << "\t------" << std::endl;
	std::cout << "\t------" << std::endl;
	a = 0;
	while (it->first != map.end()->first )//&& a < map.size())
	{
		std::cout << "(it)->first = (" << it->first << ")  | a = " << a <<std::endl;

		ft::node<MAP_PAIR> node = *(it._ptr);
		

		std::cout << "-Left : ";
		if (node.left)
			std::cout << "(" << node.left->pr.first << ")";
		else
			std::cout << "(NULL)";
		std::cout << "     | -Right : ";
		if(node.right)
			std::cout << "(" << node.right->pr.first << ")";
		else
			std::cout << "(NULL)";

		std::cout << "     | -Parent : ";
		if (node.parent)
			std::cout << "(" << node.parent->pr.first << ")" << std::endl;
		else
			std::cout << "(NULL)" << std::endl;



		++it;
		a++;
	}

	std::cout << "start iterator test" << std::endl;
	for (ft::map<MAP>::iterator it = map.begin(); it != map.end(); it++)
	{
		std::cout << "it = " << it->first << std::endl;
	}
	
	*/


	return (1);
}
