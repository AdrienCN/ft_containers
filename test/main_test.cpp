#include <iostream>
#include <string>
#include <sys/time.h>
#include "common.hpp"
#include "test_vector.hpp"
#include "test_map.hpp"
#include "test_stack.hpp"

#define BGRN "\033[1;92m"
#define RESET "\033[0;00m"

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
				struct timeval start;
				if (gettimeofday(&start, NULL) == -1)
				{
					std::cout << "Error fatal : gettimeofday failed" << std::endl;
					return (1);
				}
				test_functions[i]();
				struct timeval end;
				if (gettimeofday(&end, NULL) == -1)
				{
					std::cout << "Error fatal : gettimeofday failed" << std::endl;
					return (1);
				}
				unsigned long long duration = (end.tv_sec * 1000000 + end.tv_usec)- (start.tv_sec * 1000000 + start.tv_usec);
				std::cout << BGRN << "\tTimecount : " << duration << " micro_seconds" << RESET << std::endl;
				return 0;
			}
		}
		std::cout << "This container is unknown" << std::endl;
	}
	return (0);
}
