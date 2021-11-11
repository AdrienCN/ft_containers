#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <typename T, typename Container = ft::vector<T> >
		class stack
		{
			public:
				typedef	T					value_type;
				typedef	Container			container_type;
				typedef	std::size_t		size_type;

				container_type		_ctnr;

				explicit stack (const container_type& ctnr = container_type()) : _ctnr(ctnr) {};
				virtual ~stack() {};

				bool empty() const
				{
					return (_ctnr.is_empty());
				}

				size_type size() const
				{
					return (_ctnr.size());
				}

				value_type &top()
				{
					return (_ctnr.back());
				}

				const value_type &top() const
				{
					return (_ctnr.back());
				}

				void push(const value_type &val)
				{
					_ctnr.push_back(val);
				}

				void pop()
				{
					_ctnr.pop_back();
				}

				friend bool operator== <T, Container>(stack const& lhs, stack const& rhs);
				friend bool operator!= <T, Container>(stack const& lhs, stack const& rhs);
				friend bool operator< <T, Container>(stack const& lhs, stack const& rhs);
				friend bool operator<= <T, Container>(stack const& lhs, stack const& rhs);
				friend bool operator> <T, Container>(stack const& lhs, stack const& rhs);
				friend bool operator>= <T, Container>(stack const& lhs, stack const& rhs);

		};
	template <class T, class Container>
		bool operator==(stack<T,Container> const& lhs, stack<T,Container> const& rhs)
		{
			return lhs._ctnr == rhs._ctnr;
		}

	template <class T, class Container>
		bool operator!=(stack<T,Container> const& lhs, stack<T,Container> const& rhs)
		{
			return lhs._ctnr != rhs._ctnr;
		}

	template <class T, class Container>
		bool operator<(stack<T,Container> const& lhs, stack<T,Container> const& rhs)
		{
			return lhs._ctnr < rhs._ctnr;
		}

	template <class T, class Container>
		bool operator<=(stack<T,Container> const& lhs, stack<T,Container> const& rhs)
		{
			return lhs._ctnr <= rhs._ctnr;
		}

	template <class T, class Container>
		bool operator>(stack<T,Container> const& lhs, stack<T,Container> const& rhs)
		{
			return lhs._ctnr > rhs._ctnr;
		}

	template <class T, class Container>
		bool operator>=(stack<T,Container> const& lhs, stack<T,Container> const& rhs)
		{
			return lhs._ctnr >= rhs._ctnr;
		}
};
#endif
