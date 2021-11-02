#ifndef ITER_VECTOR_HPP
#define ITER_VECTOR_HPP

#include "iterator.hpp"

namespace ft
{
	template <typename T>
	class iterator_vector : public ft::iterator<ft::random_access_tag, T, std::ptrdiff_t, T*, T&>
	{
		public:
		//	    ****TYPEDEF****
		typedef T						value_type;
		typedef std::ptrdiff_t			difference_type;
		typedef T*						pointer;
		typedef T&						reference;
		typedef ft::random_access_tag	iterator_category;


		//		****Attribut****
		pointer		_ptr;
		//Constructor
		iterator_vector(){};
		iterator_vector(T* ptr) : _ptr(ptr) {};
		iterator_vector(iterator_vector const & src) : _ptr(src._ptr) {};
		iterator_vector & operator=(iterator_vector const &src)
		{
			if (*this != &src)
				this->_ptr = src._ptr;
			return *this;
		};

		virtual ~iterator_vector() {};

		// **Incrementation**
			//++T
			iterator_vector & operator++()
			{
				_ptr++;
				return *this;
			};
			
			//T++
			iterator_vector & operator++(T);
			{
				iterator_vector tmp(*this);
				_ptr++;
				return tmp;
			};

		// **Equality**
	
		//changer pour (ft::iterator_vector<T> const & src) ?
		bool operator==(iterator_vector const & src)
		{
			return (_ptr == src._ptr);
		};
		
		bool operator!=(iterator_vector const & src)
		{
			return (_ptr != src._ptr);
		};

		// **Rval dereferenced **
	
		reference operator*(iterator_vector const & src)
		{
			return (*_ptr);

		};	
	
		pointer operator->(iterator_vector const & src)
		{
			return (_ptr);

		};	
	
		// **Lval dereferenced ** 


		private:
			
		protected:

	};


	class const_iterator_vector : public ft::iterator<ft::random_access_tag, T, T*, pt>
	{
	};
	class reverse_iterator_vector : public ft::iterator<ft::random_access_tag, T, T*, pt>
	{
	};
	class const_iterator_vector : public ft::iterator<ft::random_access_tag, T, T*, pt>
	{
	};
};
#endif
