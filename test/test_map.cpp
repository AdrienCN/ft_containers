#include "test_map.hpp"

template<class Key, class T>
void printState(const ft::map<Key, T>& test_map) {
	std::cout << "current \033[30;4msize()\033[0m: " << test_map.size() << std::endl;
	std::cout << "the return of \033[30;4mempty()\033[0m: " << verbose_bool(test_map.empty()) << std::endl;
	for(typename ft::map<Key, T>::const_iterator it = test_map.begin(); it != test_map.end(); it++)
		std::cout << "Key: " << it->first << " - Content: " << it->second << std::endl;
}

void test_map() {
	std::cout << std::endl << "Test for the container \033[31;1;4mmap\033[0m:" << std::endl;
	ft::map<std::string, std::string> test_insert;
	std::string strings[] = {"truc", "bidule", "batman", "robin", "machin", "chose",
							 "la famille adams", "pokemon", "rouge feu", "les simpsons", "ululu", "bidule",
							 "wtf", "nausicaa", "show", "me the money", "anna", "montana"};
	int arrSize = *(&strings + 1) - strings;
	ft::pair<ft::map<std::string, std::string>::iterator, bool> test_return;

	std::cout << "This test will focus on \033[31;1;4minsert()\033[0m:" << std::endl;

	for (int i = 0; i < arrSize; i += 2) {
		test_return = test_insert.insert(ft::make_pair(strings[i], strings[i + 1]));
		std::cout << "the key : \"" << test_return.first->first;
		std::cout << "\" with value: \"" << test_return.first->second << "\"";
		std::cout << (test_return.second ? " has been created" : " cannot be created") << std::endl;
	}

	test_return = test_insert.insert(ft::make_pair(strings[0], strings[1]));
	std::cout << "the key : \"" << test_return.first->first;
	std::cout << "\" with value: \"" << test_return.first->second << "\"";
	std::cout << (test_return.second ? " has been created" : " cannot be created (already exist)") << std::endl;

	printState(test_insert);

	std::cout << std::endl << "This test will focus on \033[31;1;4miterators\033[0m:" << std::endl;
	std::cout << "Let's take an iterator it = begin() and increment it till end():" << std::endl;
	ft::map<std::string, std::string>::iterator it = test_insert.begin();
	while (it != test_insert.end())
	{
		std::cout << "return of it: " << it->first << std::endl;
		it++;
	}
	std::cout << "Now let's decrement it till begin: " << std::endl;
	while (1)
	{
		it--;
		std::cout << "return of it: " << it->first << std::endl;
		if (it == test_insert.begin())
			break;
	}

	std::cout << std::endl << "This test will focus on \033[31;1;4mfind()\033[0m:" << std::endl;
	std::cout << "If i put 'batman' as a key, the iterator found contains: ";
	ft::map<std::string, std::string>::iterator found = test_insert.find(std::string("batman"));
	std::cout << found->first << "-" << found->second << std::endl;
	std::cout << "If i put 'yolo' as a key, the iterator found contains: ";
	found = test_insert.find(std::string("yolo"));
	std::cout << found->first << "-" << found->second << std::endl;

	std::cout << std::endl << "This test will focus on \033[31;1;4moperator[]\033[0m:" << std::endl;
	std::cout << "if I print test_insert[\"batman\"], the ouput is: " << test_insert["batman"] << std::endl;
	std::cout << "if I print test_insert[\"ululu\"], the ouput is: " << test_insert["ululu"] << std::endl;
	std::cout << "if I print test_insert[\"anna\"], the ouput is: " << test_insert["anna"] << std::endl;
	std::cout << "Now if i try with an inexistant key 'pikachu' : " << test_insert["pikachu"] << std::endl;
	std::cout << "Let's if the tree has been updated: " << std::endl;
	printState(test_insert);

	std::cout << std::endl << "This test will focus on \033[31;1;4mlower_bound()\033[0m:" << std::endl;
	std::cout << "Let's try to get the lower bound of 'batman' key: ";
	std::cout << test_insert.lower_bound(std::string("batman"))->first << std::endl;
	std::cout << "Let's try to get the lower bound of 'vroum' key: ";
	std::cout << test_insert.lower_bound(std::string("vroum"))->first << std::endl;

	std::cout << std::endl << "This test will focus on \033[31;1;4mupper_bound()\033[0m:" << std::endl;
	std::cout << "Let's try to get the lower bound of 'batman' key: ";
	std::cout << test_insert.upper_bound(std::string("batman"))->first << std::endl;
	std::cout << "Let's try to get the lower bound of 'vroum' key: ";
	std::cout << test_insert.upper_bound(std::string("vroum"))->first << std::endl;

	std::cout << std::endl << "This test will focus on \033[31;1;4merase()\033[0m:" << std::endl;
	std::cout << "Let's try to erase a pair with no child 'show': " << std::endl;
	test_insert.erase(std::string("show"));
	printState(test_insert);
	std::cout << "Let's try to erase a pair with one child 'rouge feu': " << std::endl;
	test_insert.erase(std::string("rouge feu"));
	printState(test_insert);
	std::cout << "Let's try to erase a pair with two children 'machin': " << std::endl;
	test_insert.erase(std::string("machin"));
	printState(test_insert);
	std::cout << "Let's try to erase the pair before the end ptr: " << std::endl;
	test_insert.erase(std::string("wtf"));
	printState(test_insert);
	std::cout << "Let's try to erase the root: " << std::endl;
	test_insert.erase(std::string("truc"));
	printState(test_insert);

	std::cout << std::endl << "This test will focus on \033[31;1;4mcount()\033[0m:" << std::endl;
	std::cout << "let's see the return of count for existant key 'ululu': " << test_insert.count(std::string("ululu")) << std::endl;
	std::cout << "let's see the return of count for inexistant key 'war': " << test_insert.count(std::string("war")) << std::endl;

	std::cout << std::endl << "This test will focus on \033[31;1;4mswap()\033[0m:" << std::endl;
	ft::map<std::string, std::string> test_swap;
	std::cout << "Let's create a second map with 'alakazam' => 'psy', 'dracofeau' => 'feu' and 'coconfort' => 'poison'" << std::endl;
	test_swap.insert(ft::make_pair("alakazam", "psy"));
	test_swap.insert(ft::make_pair("dracofeau", "feu"));
	test_swap.insert(ft::make_pair("coconfort", "poison"));
	printState(test_swap);
	std::cout << "Now let's use swap and print state of the first then the second container" << std::endl;
	test_insert.swap(test_swap);
	printState(test_insert);
	printState(test_swap);

	std::cout << std::endl << "This test will focus on \033[31;1;4mequal_range()\033[0m:" << std::endl;
	std::cout << "Let's search equal range for 'coconfort': " << std::endl;
	ft::pair<ft::map<std::string, std::string>::iterator, ft::map<std::string, std::string>::iterator> eq_test = test_insert.equal_range("coconfort");
	std::cout << "first iterator: " << eq_test.first->first << " and second iterator: " << eq_test.second->first << std::endl;

	std::cout << std::endl << "This test will focus on \033[31;1;4mcopy constructor()\033[0m:" << std::endl;
	std::cout << "Let's make a map with copy constructor with the second map passed" << std::endl;
	ft::map<std::string, std::string> test_copy = ft::map<std::string, std::string>(test_swap);
	printState(test_copy);

	std::cout << std::endl << "This test will focus on \033[31;1;4massignation operator()\033[0m:" << std::endl;
	std::cout << "Let's make a map from the alakazam contaienr" << std::endl;
	ft::map<std::string, std::string> test_assignation;
	test_assignation = test_insert;
	printState(test_assignation);
	std::cout << std::endl << "This test will focus on \033[31;1;4mcomparison operators()\033[0m:" << std::endl;
	std::cout << "Let's take two identical containers (the one copied before with alakazam):" << std::endl;
	std::cout << "The return of map1 == map2 is: " << verbose_bool(test_assignation == test_insert) << std::endl;
	std::cout << "The return of map1 != map2 is: " << verbose_bool(test_assignation != test_insert) << std::endl;
	std::cout << "The return of map1 < map2 is: " << verbose_bool(test_assignation < test_insert) << std::endl;
	std::cout << "The return of map1 <= map2 is: " << verbose_bool(test_assignation <= test_insert) << std::endl;
	std::cout << "The return of map1 > map2 is: " << verbose_bool(test_assignation > test_insert) << std::endl;
	std::cout << "The return of map1 >= map2 is: " << verbose_bool(test_assignation >= test_insert) << std::endl;
	std::cout << "Now let's take two different container (the one with alakazam and the other with anna montana" << std::endl;
	std::cout << "The return of map1 == map2 is: " << verbose_bool(test_assignation == test_swap) << std::endl;
	std::cout << "The return of map1 != map2 is: " << verbose_bool(test_assignation != test_swap) << std::endl;
	std::cout << "The return of map1 < map2 is: " << verbose_bool(test_assignation < test_swap) << std::endl;
	std::cout << "The return of map1 <= map2 is: " << verbose_bool(test_assignation <= test_swap) << std::endl;
	std::cout << "The return of map1 > map2 is: " << verbose_bool(test_assignation > test_swap) << std::endl;
	std::cout << "The return of map1 >= map2 is: " << verbose_bool(test_assignation >= test_swap) << std::endl;


	std::cout << std::endl << "This test will focus on \033[31;1;4mclear()\033[0m:" << std::endl;
	test_insert.clear();
	printState(test_insert);
}
