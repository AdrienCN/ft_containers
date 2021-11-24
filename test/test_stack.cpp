#include "test_stack.hpp"

void test_stack_constructor(void) {
	std::cout << std::endl << "Theses tests will focus on \033[31;1;4mconstructors\033[0m: " << std::endl;
	std::cout << "Default constructor: " << std::endl;
	ft::stack<int> test_constructor1;
	std::cout << "Let's push() 42, 21 and 0" << std::endl;
	test_constructor1.push(42);
	test_constructor1.push(21);
	test_constructor1.push(0);
	std::cout << "Let's see top() of the first stack : " << test_constructor1.top() << std::endl;
	std::cout << "Let's test the copy constructor and create a new container from the first one: " << std::endl;
	ft::stack<int> test_constructor2 = ft::stack<int>(test_constructor1);
	std::cout << "Let's see top of the second stack : " << test_constructor2.top() << std::endl;
	std::cout << "Let's remove the top with pop()" << std::endl;
	test_constructor2.pop();
	std::cout << "Let's see top of the second stack : " << test_constructor2.top() << std::endl;
	std::cout << "Let's try the assignation operator from the second stack: " << std::endl;
	ft::stack<int> test_assignation;
	test_assignation = test_constructor2;
	std::cout << "Let's see top of the third stack : " << test_assignation.top() << std::endl;
}

void test_stack_push(void) {
	std::cout << std::endl << "Theses tests will focus on \033[31;1;4mpush() && top()\033[0m: " << std::endl;
	ft::stack<std::string> test_push;
	std::cout << "Let's push() 'batman', 'robin' and 'pikachu'" << std::endl;
	test_push.push("batman");
	std::cout << "Let's see top() of the stack : " << test_push.top() << std::endl;
	test_push.push("robin");
	std::cout << "Let's see top() of the stack : " << test_push.top() << std::endl;
	test_push.push("pikachu");
	std::cout << "Let's see top() of the stack : " << test_push.top() << std::endl;
}

void test_stack_pop(void) {
	std::cout << std::endl << "Theses tests will focus on \033[31;1;4mpop() && top()\033[0m: " << std::endl;
	ft::stack<std::string> test_pop;
	std::cout << "Let's push() 'batman', 'robin' and 'pikachu'" << std::endl;
	test_pop.push("batman");
	test_pop.push("robin");
	test_pop.push("pikachu");
	std::cout << "Let's see top() of the stack : " << test_pop.top() << std::endl;
	std::cout << "Now let's use pop(): " << std::endl;
	test_pop.pop();
	std::cout << "Let's see top() of the stack : " << test_pop.top() << std::endl;
	std::cout << "Now let's use pop(): " << std::endl;
	test_pop.pop();
	std::cout << "Let's see top() of the stack : " << test_pop.top() << std::endl;
//	std::cout << "Now let's use pop(): " << std::endl;
//	test_pop.pop();
//	std::cout << "Let's see top() of the stack : " << test_pop.top() << std::endl;
}

void test_stack_size(void) {
	std::cout << std::endl << "Theses tests will focus on \033[31;1;4mempty() and size()\033[0m: " << std::endl;
	ft::stack<std::string> test_size;
	std::cout << "Let's see the size() on empty container: " << test_size.size();
	std::cout << " and empty() is: " << verbose_bool(test_size.empty()) << std::endl;
	std::cout << "Let's push() 'batman'" << std::endl;
	test_size.push("batman");
	std::cout << "Let's see size() of the stack : " << test_size.size();
	std::cout << " and empty() is: " << verbose_bool(test_size.empty()) << std::endl;
	std::cout << "Let's push() 'robin'" << std::endl;
	test_size.push("robin");
	std::cout << "Let's see size() of the stack : " << test_size.size();
	std::cout << " and empty() is: " << verbose_bool(test_size.empty()) << std::endl;
	std::cout << "Let's push() 'pikachu'" << std::endl;
	test_size.push("pikachu");
	std::cout << "Let's see size() of the stack : " << test_size.size();
	std::cout << " and empty() is: " << verbose_bool(test_size.empty()) << std::endl;
	std::cout << "Let's use pop(): " << std::endl;
	test_size.pop();
	std::cout << "Let's see size() of the stack : " << test_size.size();
	std::cout << " and empty() is: " << verbose_bool(test_size.empty()) << std::endl;
	std::cout << "Let's use pop(): " << std::endl;
	test_size.pop();
	std::cout << "Let's see size() of the stack : " << test_size.size();
	std::cout << " and empty() is: " << verbose_bool(test_size.empty()) << std::endl;
	std::cout << "Let's use pop(): " << std::endl;
	test_size.pop();
	std::cout << "Let's see size() of the stack : " << test_size.size();
	std::cout << " and empty() is: " << verbose_bool(test_size.empty()) << std::endl;
}

void test_stack_comparison(void) {
	std::cout << std::endl << "Theses tests will focus on \033[31;1;4mcomparison operators\033[0m: " << std::endl;
	ft::stack<char> test_comparison1, test_comparison2, test_comparison3;
	std::cout << "test's create two identical char stacks with 'a', 'b', 'c', 'd' : " << std::endl;
	test_comparison1.push('a');
	test_comparison2.push('a');
	test_comparison1.push('b');
	test_comparison2.push('b');
	test_comparison1.push('c');
	test_comparison2.push('c');
	test_comparison1.push('d');
	test_comparison2.push('d');
	std::cout << "Top of the first stack is: " << test_comparison1.top();
	std::cout << " and size() is : " << test_comparison1.size() << std::endl;
	std::cout << "Top of the second stack is: " << test_comparison2.top();
	std::cout << " and size() is : " << test_comparison2.size() << std::endl;
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

	std::cout << std::endl << "Let's create one char stacks with 'a', 'b', 'c', 'd', ";
	std::cout << "and a second stack with 'e', 'f', 'g', 'h'" << std::endl;
	test_comparison3.push('e');
	test_comparison3.push('f');
	test_comparison3.push('g');
	test_comparison3.push('h');
	std::cout << "Top of the first stack is: " << test_comparison1.top();
	std::cout << " and size() is : " << test_comparison1.size() << std::endl;
	std::cout << "Top of the second stack is: " << test_comparison3.top();
	std::cout << " and size() is : " << test_comparison3.size() << std::endl;
	std::cout << "The return of test_comparison1 == test_comparaison3 is : ";
	std::cout << verbose_bool(test_comparison1 == test_comparison3) << std::endl;
	std::cout << "The return of test_comparison1 != test_comparaison3 is : ";
	std::cout << verbose_bool(test_comparison1 != test_comparison3) << std::endl;
	std::cout << "The return of test_comparison1 < test_comparaison3 is : ";
	std::cout << verbose_bool(test_comparison1 < test_comparison3) << std::endl;
	std::cout << "The return of test_comparison1 <= test_comparaison3 is : ";
	std::cout << verbose_bool(test_comparison1 <= test_comparison3) << std::endl;
	std::cout << "The return of test_comparison1 > test_comparaison3 is : ";
	std::cout << verbose_bool(test_comparison1 > test_comparison3) << std::endl;
	std::cout << "The return of test_comparison1 >= test_comparaison3 is : ";
	std::cout << verbose_bool(test_comparison1 >= test_comparison3) << std::endl;
}

void test_stack(void) {
	std::cout << "Theses tests will focus on container \033[31;1;4mstack\033[0m:" << std::endl;
	test_stack_constructor();
	test_stack_push();
	test_stack_pop();
	test_stack_size();
	test_stack_comparison();
}
