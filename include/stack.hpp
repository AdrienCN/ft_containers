#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
		class stack;
	template <class T, class Container>
		bool operator==(stack<T,Container> const& lhs, stack<T,Container> const& rhs)
		{
			return lhs.c == rhs.c;
		}

	template <class T, class Container>
		bool operator!=(stack<T,Container> const& lhs, stack<T,Container> const& rhs)
		{
			return lhs.c != rhs.c;
		}

	template <class T, class Container>
		bool operator<(stack<T,Container> const& lhs, stack<T,Container> const& rhs)
		{
			return lhs.c < rhs.c;
		}

	template <class T, class Container>
		bool operator<=(stack<T,Container> const& lhs, stack<T,Container> const& rhs)
		{
			return lhs.c <= rhs.c;
		}

	template <class T, class Container>
		bool operator>(stack<T,Container> const& lhs, stack<T,Container> const& rhs)
		{
			return lhs.c > rhs.c;
		}

	template <class T, class Container>
		bool operator>=(stack<T,Container> const& lhs, stack<T,Container> const& rhs)
		{
			return lhs.c >= rhs.c;
		}

	template <typename T, typename Container>
		class stack
		{
			public:
				typedef	T					value_type;
				typedef	Container			container_type;
				typedef	std::size_t		size_type;

				container_type		c;

				explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {};
				virtual ~stack() {};

				bool empty() const
				{
					return (c.empty());
				}

				size_type size() const
				{
					return (c.size());
				}

				value_type &top()
				{
					return (c.back());
				}

				const value_type &top() const
				{
					return (c.back());
				}

				void push(const value_type &val)
				{
					c.push_back(val);
				}

				void pop()
				{
					c.pop_back();
				}
		};
};
#endif
