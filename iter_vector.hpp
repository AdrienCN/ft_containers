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
		iterator_vector(pointer ptr) : _ptr(ptr) {};
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


		// **Dereferencement **
	
		reference operator*(iterator_vector const & src)
		{
			return (*_ptr);
		};	
	
		pointer operator->(iterator_vector const & src)
		{
			return (_ptr);
		};
		
		iterator_vector &operator--()
		{
			_ptr--;
			return *this;
		};

		iterator_vector & operator--(T)
		{
			iterator_vector tmp(*this);
			_ptr--;
			return *this;
		};

		iterator_vector & operator+(difference_type n) const
		{
			return (this->_ptr + n);
		};

		iterator_vector & operator+(difference_type n, iterator_vector const & rhs)
		{
			return (n + rhs._ptr);
		};
	
		iterator_vector & operator-(difference_type n)
		{
			return (this->_ptr  - n);
		};

		difference_type  operator-(iterator_vector const & lhs, iterator_vector const & rhs)
		{
			return (lhs._ptr - rhs._ptr);
		};

		bool operator<(iterator_vector const & lhs, iterator_vector const & rhs)
		{
			return lhs._ptr < rhs._ptr;
		};	
		bool operator<=(iterator_vector const & lhs, iterator_vector const & rhs)
		{
			return lhs._ptr <= rhs._ptr;
		};
		bool operator>(iterator_vector const & lhs, iterator_vector const & rhs)
		{
			return lhs._ptr > rhs._ptr;
		};
		bool operator>=(iterator_vector const & lhs, iterator_vector const & rhs)
		{
			return lhs._ptr >= rhs._ptr;
		};

		iterator_vector & operator+=(difference_type n)
		{
			_ptr += n;
			return *this;
		}

		iterator_vector & operator-=(difference_type n)
		{
			_ptr -= n;
			return *this;
		}

		reference operator[](int n) const
		{
			return (*(_ptr + n));
		};
		private:
		//Empty	
		protected:
		//Empty
	};


	class const_iterator_vector : public ft::iterator<ft::random_access_tag, T, T*, pt>
	{
		typedef const T					value_type;
		typedef std::ptrdiff_t			difference_type;
		typedef const T*				pointer;
		typedef const T&				reference;
		typedef ft::random_access_tag	iterator_category;
	
		//		****Attribut****
		pointer		_ptr;
		//Constructor
		const_iterator_vector(){};

		const_iterator_vector(pointer ptr) : _ptr(ptr) {};
		
		const_iterator_vector(const_iterator_vector const & src) : _ptr(src._ptr) {};
		
		const_iterator_vector(iterator_vector<T> const & src) : _ptr(src._ptr) {};
		
		const_iterator_vector & operator=(const_iterator_vector const &src)
		{
			if (*this != &src)
				this->_ptr = src._ptr;
			return *this;
		};

		virtual ~const_iterator_vector() {};

		// **Incrementation**
			//++T
			const_iterator_vector & operator++()
			{
				_ptr++;
				return *this;
			};
			
			//T++
			const_iterator_vector & operator++(T);
			{
				const_iterator_vector tmp(*this);
				_ptr++;
				return tmp;
			};

		// **Equality**
	
		//changer pour (ft::const_iterator_vector<T> const & src) ?
		bool operator==(const_iterator_vector const & src)
		{
			return (_ptr == src._ptr);
		};
		
		bool operator!=(const_iterator_vector const & src)
		{
			return (_ptr != src._ptr);
		};


		// **Dereferencement **
	
		reference operator*(const_iterator_vector const & src)
		{
			return (*_ptr);
		};	
	
		pointer operator->(const_iterator_vector const & src)
		{
			return (_ptr);
		};
		
		const_iterator_vector &operator--()
		{
			_ptr--;
			return *this;
		};

		const_iterator_vector & operator--(T)
		{
			const_iterator_vector tmp(*this);
			_ptr--;
			return *this;
		};

		const_iterator_vector & operator+(difference_type n) const
		{
			return (this->_ptr + n);
		};

		const_iterator_vector & operator+(difference_type n, const_iterator_vector const & rhs)
		{
			return (n + rhs._ptr);
		};
	
		const_iterator_vector & operator-(difference_type n)
		{
			return (this->_ptr  - n);
		};

		difference_type  operator-(const_iterator_vector const & lhs, const_iterator_vector const & rhs)
		{
			return (lhs._ptr - rhs._ptr);
		};

		bool operator<(const_iterator_vector const & lhs, const_iterator_vector const & rhs)
		{
			return lhs._ptr < rhs._ptr;
		};	
		bool operator<=(const_iterator_vector const & lhs, const_iterator_vector const & rhs)
		{
			return lhs._ptr <= rhs._ptr;
		};
		bool operator>(const_iterator_vector const & lhs, const_iterator_vector const & rhs)
		{
			return lhs._ptr > rhs._ptr;
		};
		bool operator>=(const_iterator_vector const & lhs, const_iterator_vector const & rhs)
		{
			return lhs._ptr >= rhs._ptr;
		};

		const_iterator_vector & operator+=(difference_type n)
		{
			_ptr += n;
			return *this;
		}

		const_iterator_vector & operator-=(difference_type n)
		{
			_ptr -= n;
			return *this;
		}
	
		reference operator[](int n) const
		{
			return (*(_ptr + n));
		};
		private:
		//Empty	
		protected:
		//Empty	
	};
	class reverse_iterator_vector : public ft::iterator<ft::random_access_tag, T, T*, pt>
	{

	};
	class const_reverse_iterator_vector : public ft::iterator<ft::random_access_tag, T, T*, pt>
	{

	};
};
#endif
