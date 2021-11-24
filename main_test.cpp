#include <iostream>
#include <string>
#include "test/common.hpp"
#include "test/test_vector.hpp"
#include "test/test_map.hpp"
#include "test/test_stack.hpp"

int main(int argc, char **argv) 
{
	std::string containers[3] = {"vector", "map", "stack"};
	void (*test_functions[3])(void) = {&test_vector, &test_map, &test_stack};

	if(argc != 2) 
	{
		std::cout << "Usage ./ft_containers <container_name>" << std::endl;
	} 
	else 
	{
		for(size_t i = 0; i < 3; i++) 
		{
			if (argv[1] == containers[i]) 
			{
				test_functions[i]();
				return 0;
			}
		}
		std::cout << "This container is unknown" << std::endl;
	}
	return (0);
}
