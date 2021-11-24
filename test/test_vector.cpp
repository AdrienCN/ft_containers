#include "test_vector.hpp"

template<typename T>
void print_vector_content(const ft::vector<T>& to_print) {
	std::cout << "The vector contains : ";
	for(size_t i = 0; i < to_print.size(); i++)
		std::cout << to_print[i] << ", ";
	std::cout << std::endl;
}

template<typename T>
void print_vector_state(const ft::vector<T>& to_print) {
	print_vector_content(to_print);
	std::cout << "The size() is: " << to_print.size();
	std::cout << ", so empty() is " << verbose_bool(to_print.empty());
	std::cout << ", and capacity() is " << to_print.capacity() << std::endl;
}

void test_vector_constructor(void) {
	std::cout << std::endl << "Tests for \033[31;1;4mconstructors\033[0m: " << std::endl;
	std::cout << "Let's use the default constructor";
	std::cout << " and print the state of the first vector: " << std::endl;
	ft::vector<std::string> test_constructor1;
	print_vector_state(test_constructor1);

	std::cout << std::endl << "Now let's push 'salameche' and 'pikachu'";
	std::cout << " and print the state of the first vector: ";
	test_constructor1.push_back("salameche");
	test_constructor1.push_back("pikachu");
	print_vector_state(test_constructor1);

	std::cout << std::endl << "Let's use the copy constructor and print the state the second vector: " << std::endl;
	ft::vector<std::string> test_constructor2 = ft::vector<std::string>(test_constructor1);
	print_vector_state(test_constructor2);

	std::cout << std::endl << "Let's use the constructor with 42 copies of default T(): " << std::endl;
	ft::vector<std::string> test_constructor3 = ft::vector<std::string>(42);
	print_vector_state(test_constructor3);

	std::cout << std::endl << "Let's use the constructor with 42 copies of 'melofee': " << std::endl;
	ft::vector<std::string> test_constructor4 = ft::vector<std::string>(42, "melofee");
	print_vector_state(test_constructor4);

	std::cout << std::endl << "Let's use the constructor with InputIt from the first vector: " << std::endl;
	ft::vector<std::string> test_constructor5 = ft::vector<std::string>(test_constructor1.begin(), test_constructor1.end());
	print_vector_state(test_constructor5);

	std::cout << std::endl << "Finaly let's try the assignation with the melofee vector " << std::endl;
	ft::vector<std::string> test_constructor6;
	test_constructor6 = test_constructor4;
	print_vector_state(test_constructor6);
}

void test_vector_pushpop_back(void) {
	std::cout << std::endl << "Tests for \033[31;1;4mpush_back()\033[0m: " << std::endl;
	ft::vector<std::string> test_push_back;

	std::cout << "Let's create a vector then push_back() 'mewtwo', 'articodin' and 'raflesia': " << std::endl;
	test_push_back.push_back("mewtwo");
	print_vector_state(test_push_back);
	test_push_back.push_back("articodin");
	print_vector_state(test_push_back);
	test_push_back.push_back("raflesia");
	print_vector_state(test_push_back);

	std::cout << "Now let's use pop_back() three times: " << std::endl;
	test_push_back.pop_back();
	print_vector_state(test_push_back);
	test_push_back.pop_back();
	print_vector_state(test_push_back);
	test_push_back.pop_back();
	print_vector_state(test_push_back);
}

void test_vector_assign(void) {
	std::cout << std::endl << "Tests for \033[31;1;4massign()\033[0m: " << std::endl;
	ft::vector<std::string> test_assign1;

	std::cout << "Let's try assign 21 'roudoudou' on an empty vector: " << std::endl;
	test_assign1.assign(21, "roudoudou");
	print_vector_state(test_assign1);

	ft::vector<std::string> test_assign2;
	std::cout << std::endl << "Let's create a second vector";
	std::cout << " then push_back() 'mewtwo', 'articodin' and 'raflesia': " << std::endl;
	test_assign2.push_back("mewtwo");
	test_assign2.push_back("articodin");
	test_assign2.push_back("raflesia");
	print_vector_state(test_assign2);
	std::cout << "Let's try assign 12 'asticot' on this non empty vector: " << std::endl;
	test_assign2.assign(12, "asticot");
	print_vector_state(test_assign2);

	ft::vector<std::string> test_assign3;
	std::cout << std::endl << "Let's create an third empty container";
	std::cout << ", and use assign with iterators from the first container:" << std::endl;
	test_assign3.assign(test_assign1.begin(), test_assign1.end());
	print_vector_state(test_assign3);
}

void test_vector_frontback(void) {
	std::cout << std::endl << "Tests for \033[31;1;4mfront() & back()\033[0m: " << std::endl;
	ft::vector<std::string> test_front;

	std::cout << "Let's create a vector with 'raichu', 'machopeur' and 'nosferapti': " << std::endl;
	test_front.push_back("raichu");
	std::cout << "front() :" << test_front.front() << std::endl;
	std::cout << "back() :" << test_front.back() << std::endl;
	test_front.push_back("machopeur");
	std::cout << "front() :" << test_front.front() << std::endl;
	std::cout << "back() :" << test_front.back() << std::endl;
	test_front.push_back("nosferapti");
	std::cout << "front() :" << test_front.front() << std::endl;
	std::cout << "back() :" << test_front.back() << std::endl;
	std::cout << "Let's pop_back twice: " << std::endl;
	test_front.pop_back();
	std::cout << "front() :" << test_front.front() << std::endl;
	std::cout << "back() :" << test_front.back() << std::endl;\
	test_front.pop_back();
	std::cout << "front() :" << test_front.front() << std::endl;
	std::cout << "back() :" << test_front.back() << std::endl;
}

void test_vector_insert(void) {
	std::cout << std::endl << "Tests for \033[31;1;4minsert()\033[0m: " << std::endl;

	std::cout << "Let's insert on empty vector<int> container:" << std::endl;
	ft::vector<int> test_insert1;
	std::cout << "*First let's try to insert at pos = begin() with integer 42 :" << std::endl;
	test_insert1.insert(test_insert1.begin(), 42);
	print_vector_state(test_insert1);
	std::cout << "*Let's create a new empty container";
	std::cout << " and try to insert at pos = end() with integer 42 :" << std::endl;
	ft::vector<int> test_insert2;
	test_insert2.insert(test_insert2.end(), 42);
	print_vector_state(test_insert2);

	std::cout << std::endl << "Let's insert on vector<int> container";
	std::cout << " with one element 42 (the previous one):" << std::endl;
	std::cout << "*First let's try to insert at pos = begin() with integer 21 :" << std::endl;
	test_insert1.insert(test_insert1.begin(), 21);
	print_vector_state(test_insert1);
	std::cout << "*Then let's try to insert at pos = end() with integer 12 :" << std::endl;
	test_insert1.insert(test_insert1.end(), 12);
	print_vector_state(test_insert1);
	std::cout << "Let's try to insert with pos = begin() + 2 with integer 123: " << std::endl;
	test_insert1.insert(test_insert1.begin() + 2, 123);
	print_vector_state(test_insert1);
	std::cout << "*Then let's try to insert at pos = end() - 2 with integer 789 :" << std::endl;
	test_insert1.insert(test_insert1.end() - 2, 789);
	print_vector_state(test_insert1);

	std::cout << std::endl << "Let's use the insert(pos, count, val) prototype with pos = begin() + 1, ";
	std::cout << "count = 9 and val = '666' on the previous container" << std::endl;
	test_insert1.insert(test_insert1.begin() + 1, 9, 666);
	print_vector_state(test_insert1);
	std::cout << "The use the insert(pos, count, val) prototype with pos = end(), ";
	std::cout << "count = 5 and val = '75' on the previous container" << std::endl;
	test_insert1.insert(test_insert1.end(), 5, 75);
	print_vector_state(test_insert1);

	std::cout << std::endl << "Let's use the insert prototype with input iterators :" << std::endl;
	std::cout << "Let's create a new vector<int> with 12 integer -1:" << std::endl;
	ft::vector<int> test_insert3 = ft::vector<int>(12, -1);
	print_vector_state(test_insert3);
	std::cout << "Then let's try to insert this new vector at the end of the previous one:" << std::endl;
	test_insert1.insert(test_insert1.end(), test_insert3.begin(), test_insert3.end());
	print_vector_state(test_insert1);
}

void test_vector_erase(void) {
	std::cout << std::endl << "Tests for \033[31;1;4merase()\033[0m: " << std::endl;

	std::cout << "Let's create an empty container:" << std::endl;
	ft::vector<std::string> test_erase1;
	print_vector_state(test_erase1);

	std::cout << "Let's try to erase begin() on empty container:" << std::endl;
	test_erase1.erase(test_erase1.begin());
	print_vector_state(test_erase1);

	std::cout << "Let's create a vector<string> with 'carapuce', 'carabaffe' and 'tortank':" << std::endl;
	test_erase1.push_back("carapuce");
	test_erase1.push_back("carabaffe");
	test_erase1.push_back("tortank");
	print_vector_state(test_erase1);
	std::cout << "Let's try to erase begin():" << std::endl;
	test_erase1.erase(test_erase1.begin());
	print_vector_state(test_erase1);
	std::cout << "Let's try to erase begin() + 1:" << std::endl;
	test_erase1.erase(test_erase1.begin() + 1);
	print_vector_state(test_erase1);
	std::cout << "Let's try to erase end() - 1:" << std::endl;
	test_erase1.erase(test_erase1.end() - 1);
	print_vector_state(test_erase1);

	std::cout << std::endl << "Let's create a vector<string> with 'pikachu',";
	std::cout << " 'bulbizare', 'herbizare', 'florizard', 'raichu':" << std::endl;
	ft::vector<std::string> test_erase2;
	test_erase2.push_back("pikachu");
	test_erase2.push_back("bulbizare");
	test_erase2.push_back("herbizare");
	test_erase2.push_back("florizard");
	test_erase2.push_back("raichu");
	print_vector_state(test_erase2);
	std::cout << "Let's use erase() prototype with first = begin + 1 and last = end - 1" << std::endl;
	test_erase2.erase(test_erase2.begin() + 1, test_erase2.end() - 1);
	print_vector_state(test_erase2);
}

void test_vector_at(void) {
	std::cout << std::endl << "Tests for \033[31;1;4mat()\033[0m: " << std::endl;

	std::cout << "Let's test the exception on an empty container: " << std::endl;
	ft::vector<std::string> test_at;
	try {
		std::string test;
		test = test_at.at(2);
		std::cout << "this should not happen and test contains: " << test << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "Let's create a string vector with 'papilusion', 'scarabrute' and 'racaillou'" << std::endl;
	test_at.push_back("papilusion");
	test_at.push_back("scarabrute");
	test_at.push_back("racaillou");
	try {
		std::string test;
		test = test_at.at(2);
		std::cout << "The result at(2) is: " << test << std::endl;
	}
	catch (std::exception& e) {
		std::cout << "this should not happen" << std::endl;
		std::cout << e.what() << std::endl;
	}

	std::cout << "Let's test the exception on this container: " << std::endl;
	try {
		std::string test;
		test = test_at.at(42);
		std::cout << "this should not happen and test contains: " << test << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void test_vector_operator_bracket(void) {
	std::cout << std::endl << "Tests for \033[31;1;4moperator[]()\033[0m: " << std::endl;

	std::cout << "Let's create a string vector with 'papilusion', 'scarabrute', ";
	std::cout << "'racaillou', 'mew', 'voltorbe'" << std::endl;
	ft::vector<std::string> test_operator_bracket;
	test_operator_bracket.push_back("papilusion");
	test_operator_bracket.push_back("scarabrute");
	test_operator_bracket.push_back("racaillou");
	test_operator_bracket.push_back("mew");
	test_operator_bracket.push_back("voltorbe");

	for(int i = 0; i < 5; i++)
		std::cout << "test[" << i << "] = " << test_operator_bracket[i] << std::endl;

	std::cout << "Let's try to change the content with operator[]:" << std::endl;
	std::cout << "Let's set test[0] to 'mystherbe'" << std::endl;
	test_operator_bracket[0] = "mystherbe";
	std::cout << "test[0] = " << test_operator_bracket[0] << std::endl;
	print_vector_state(test_operator_bracket);
 }

void test_vector_clear(void) {
	std::cout << std::endl << "Tests for \033[31;1;4mclear()\033[0m: " << std::endl;

	std::cout << "Let's create a int vector with new() with count= 9 elements with value = 6" << std::endl;
	ft::vector<int>* test_clear = new ft::vector<int>(9, 6);
	print_vector_state(*test_clear);

	std::cout << "Now let's use clear() and print state of the vector:" << std::endl;
	test_clear->clear();
	print_vector_state(*test_clear);

	delete test_clear;
}

void test_vector_max_size(void) {
	std::cout << std::endl << "Tests for \033[31;1;4mmax_size()\033[0m: " << std::endl;
	ft::vector<int> test_max_size;
	std::cout << "The return of max_size() for a int vector is: " << test_max_size.max_size() << std::endl;
}

void test_vector_reserve(void) {
	std::cout << std::endl << "Tests for \033[31;1;4mreserve()\033[0m: " << std::endl;
	ft::vector<int> test_reserve;

	std::cout << "Let's test with an empty container:" << std::endl;
	print_vector_state(test_reserve);
	std::cout << "Let's reserve 10 blocks" << std::endl;
	test_reserve.reserve(10);
	print_vector_state(test_reserve);
	std::cout << "Now let's insert 10 values" << std::endl;
	test_reserve.insert(test_reserve.begin(), 10, 42);
	print_vector_state(test_reserve);
	std::cout << "Let's try to reserve 10 which shouldn't do anything" << std::endl;
	test_reserve.reserve(10);
	print_vector_state(test_reserve);
	std::cout << "Let's try to reserve 50" << std::endl;
	test_reserve.reserve(50);
	print_vector_state(test_reserve);
}

void test_vector_resize(void) {
	std::cout << std::endl << "Tests for \033[31;1;4mresize()\033[0m: " << std::endl;

	std::cout << "Let's create an int vector with 10 times integer 42" << std::endl;
	ft::vector<int> test_resize = ft::vector<int>(10, 42);
	print_vector_state(test_resize);
	std::cout << "Let's try to resize to 5" << std::endl;
	test_resize.resize(5);
	print_vector_state(test_resize);
	std::cout << "Let's try to resize to 9 with 21" << std::endl;
	test_resize.resize(9, 21);
	print_vector_state(test_resize);
	std::cout << "Let's try to resize to 50 with default value" << std::endl;
	test_resize.resize(50);
	print_vector_state(test_resize);
}

void test_vector_iterator(void) {
	std::cout << std::endl << "Tests for \033[31;1;4miterators\033[0m: " << std::endl;

	std::cout << "Let's create a int vector with 4, 8, 15, 16, 23, 42" << std::endl;
	ft::vector<int> test_iterator;
	test_iterator.push_back(4);
	test_iterator.push_back(8);
	test_iterator.push_back(15);
	test_iterator.push_back(16);
	test_iterator.push_back(23);
	test_iterator.push_back(42);
	std::cout << "Let's create an iterator begin() of this vector" << std::endl;
	ft::vector<int>::iterator it = test_iterator.begin();
	std::cout << "*it = " << *it << std::endl;
	std::cout << "*++it = " << *++it << std::endl;
	std::cout << "*it++ = " << *it++ << " then *it is : " << *it << std::endl;
	std::cout << "*(it + 3) = " << *(it + 3) << " then *it is : " << *it << std::endl;
	std::cout << "*(it += 3) = " << *(it += 3) << std::endl;
	std::cout << "*--it = " << *(--it) << std::endl;
	std::cout << "*it-- = " << *(it--) << " then *it is : " << *it << std::endl;
	std::cout << "*(it - 2) = " << *(it - 2) << " then *it is : " << *it << std::endl;
	std::cout << "*(it -= 2) = " << *(it -= 2) << std::endl;

	std::cout << std::endl << "Let's create a constant iterator begin() of this vector" << std::endl;
	ft::vector<int>::const_iterator cit = test_iterator.begin();
	std::cout << "*cit = " << *cit << std::endl;
	std::cout << "*++cit = " << *++cit << std::endl;
	std::cout << "*cit++ = " << *cit++ << " then *cit is : " << *cit << std::endl;
	std::cout << "*(cit + 3) = " << *(cit + 3) << " then *cit is : " << *cit << std::endl;
	std::cout << "*(cit += 3) = " << *(cit += 3) << std::endl;
	std::cout << "*--cit = " << *(--cit) << std::endl;
	std::cout << "*cit-- = " << *(cit--) << " then *cit is : " << *cit << std::endl;
	std::cout << "*(cit - 2) = " << *(cit - 2) << " then *cit is : " << *cit << std::endl;
	std::cout << "*(cit -= 2) = " << *(cit -= 2) << std::endl;

	std::cout << std::endl <<"Let's test comparison between iterator and constant iterators:" << std::endl;
	std::cout << "(*cit is " << *cit << " and *it is " << *it << ")" << std::endl;
	std::cout << "cit == it return: " << verbose_bool(cit == it) << std::endl;
	std::cout << "cit != it return: " << verbose_bool(cit != it) << std::endl;
	std::cout << "cit < it return: " << verbose_bool(cit < it) << std::endl;
	std::cout << "cit <= it return: " << verbose_bool(cit <= it) << std::endl;
	std::cout << "cit > it return: " << verbose_bool(cit > it) << std::endl;
	std::cout << "cit >= it return: " << verbose_bool(cit >= it) << std::endl;
	std::cout << "Now let's increase cit by one" << std::endl;
	std::cout << "(*++cit is " << *++cit << " and *it is " << *it << ")" << std::endl;
	std::cout << "cit == it return: " << verbose_bool(cit == it) << std::endl;
	std::cout << "cit != it return: " << verbose_bool(cit != it) << std::endl;
	std::cout << "cit < it return: " << verbose_bool(cit < it) << std::endl;
	std::cout << "cit <= it return: " << verbose_bool(cit <= it) << std::endl;
	std::cout << "cit > it return: " << verbose_bool(cit > it) << std::endl;
	std::cout << "cit >= it return: " << verbose_bool(cit >= it) << std::endl;

	std::cout << std::endl << "Let's test subtraction it = begin() and it2 = begin() + 2" << std::endl;
	ft::vector<int>::iterator it2 = test_iterator.begin() + 2;
	it = test_iterator.begin();
	std::cout << "it2 - it = " << (it2 - it) << std::endl;

	std::cout << std::endl << "Let's test operator[] with it = begin() :" << std::endl;
	size_t i = 0;
	for (ft::vector<int>::iterator pouit = it; pouit != test_iterator.end(); pouit++) {
		std::cout << "it[" << i << "] = " << it[i] << std::endl;
		i++;
	}

	std::cout << std::endl << "Let's create a reverse iterator rbegin()" << std::endl;
	ft::vector<int>::reverse_iterator rit = test_iterator.rbegin();
	std::cout << "*rit = " << *rit << std::endl;
	std::cout << "*++rit = " << *++rit << std::endl;
	std::cout << "*rit++ = " << *rit++ << " then *rit is : " << *rit << std::endl;
	std::cout << "*(rit + 3) = " << *(rit + 3) << " then *rit is : " << *rit << std::endl;
	std::cout << "*(rit += 3) = " << *(rit += 3) << std::endl;
	std::cout << "*--rit = " << *(--rit) << std::endl;
	std::cout << "*rit-- = " << *(rit--) << " then *rit is : " << *rit << std::endl;
	std::cout << "*(rit - 2) = " << *(rit - 2) << " then *rit is : " << *rit << std::endl;
	std::cout << "*(rit -= 2) = " << *(rit -= 2) << std::endl;

}

void test_vector_comparison(void) {
	std::cout << std::endl << "Tests for \033[31;1;4mcomparison operators:\033[0m: " << std::endl;

	std::cout << "Let's create two same vectors of char with 'a', 'b', 'c', 'd':" << std::endl;
	ft::vector<char> test_comparison1, test_comparison2;
	test_comparison1.push_back('a');
	test_comparison1.push_back('b');
	test_comparison1.push_back('c');
	test_comparison1.push_back('d');
	test_comparison2 = test_comparison1;
	print_vector_state(test_comparison1);
	print_vector_state(test_comparison2);
	std::cout << "The return of test_comparison1 == test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 == test_comparison2) << std::endl;
	std::cout << "The return of test_comparison1 != test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 != test_comparison2) << std::endl;
	std::cout << "The return of test_comparison1 < test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 < test_comparison2) << std::endl;
	std::cout << "The return of test_comparison1 <= test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 <= test_comparison2) << std::endl;
	std::cout << "The return of test_comparison1 > test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 > test_comparison2) << std::endl;
	std::cout << "The return of test_comparison1 >= test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 >= test_comparison2) << std::endl;


	std::cout << std::endl << "Let's create a vector with 'e', 'f', 'g', 'h' and compare to the first one" << std::endl;
	test_comparison2.clear();
	test_comparison2.push_back('e');
	test_comparison2.push_back('f');
	test_comparison2.push_back('g');
	test_comparison2.push_back('h');
	print_vector_state(test_comparison1);
	print_vector_state(test_comparison2);
	std::cout << "The return of test_comparison1 == test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 == test_comparison2) << std::endl;
	std::cout << "The return of test_comparison1 != test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 != test_comparison2) << std::endl;
	std::cout << "The return of test_comparison1 < test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 < test_comparison2) << std::endl;
	std::cout << "The return of test_comparison1 <= test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 <= test_comparison2) << std::endl;
	std::cout << "The return of test_comparison1 > test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 > test_comparison2) << std::endl;
	std::cout << "The return of test_comparison1 >= test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 >= test_comparison2) << std::endl;
}

void test_vector_swap(void) {
	std::cout << std::endl << "Tests for \033[31;1;4mswap()\033[0m: " << std::endl;

	std::cout << "Let's create two int vectors : 1/ 12, 21, 42 - 2/ 4 8 15 16 23 42" << std::endl;
	ft::vector<int> test_swap1, test_swap2;
	test_swap1.push_back(12);
	test_swap1.push_back(21);
	test_swap1.push_back(42);
	std::cout << "First container: " << std::endl;
	print_vector_state(test_swap1);
	test_swap2.push_back(4);
	test_swap2.push_back(8);
	test_swap2.push_back(15);
	test_swap2.push_back(16);
	test_swap2.push_back(23);
	test_swap2.push_back(42);
	std::cout << "Second container: " << std::endl;
	print_vector_state(test_swap2);
	std::cout << "Now let's use swap():" << std::endl;
	test_swap1.swap(test_swap2);
	std::cout << "First container: " << std::endl;
	print_vector_state(test_swap1);
	std::cout << "Second container: " << std::endl;
	print_vector_state(test_swap2);
}

void test_vector() {
	std::cout << "Tests for \033[31;1;4mvector()\033[0m container: " << std::endl;
	test_vector_constructor();
	test_vector_pushpop_back();
	test_vector_assign();
	test_vector_frontback();
	test_vector_insert();
	test_vector_erase();
	test_vector_at();
	test_vector_operator_bracket();
	test_vector_clear();
	test_vector_max_size();
	test_vector_reserve();
	test_vector_resize();
	test_vector_iterator();
	test_vector_comparison();
	test_vector_swap();
}
