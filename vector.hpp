#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "iterator_vector.hpp"

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
		class vector 
		{
			public:

			//  ****TYPEDEF  *****
				typedef T											value_type;
				typedef Alloc										allocator_type;
				typedef	allocator_type::reference					reference;
				typedef	allocator_type::const_reference				const_reference;
				typedef	allocator_type::pointer						pointer;
				typedef	allocator_type::const_pointer				const_pointer;
				typedef ft::iterator_vector<T>						iterator;
				typedef ft::const_iterator_vector<T>				const_iterator;
				typedef ft::reverse_iterator<iterator>				reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>		reverse_iterator;
				typedef	std::ptrdiff_t								difference_type;
				typedef std::size_t									size_type;

			//	****ATTRIBUTES****
				
				allocator_type	_allocator;
				size_type	_size;
				size_type	_capacity;
				pointer		_array;
			//	****Constructor*****
				//Default
				explicit vector(const allocator_type& alloc = allocator_type()) :  _allocator(alloc)_size(0), _array(NULL), _capacity(0) {};
				//fill
				explicit vector (size_type n, const value_type & val = value_type(),
								const allocator_type & alloc = allocator_type()): _allocator(alloc), _size(n), _capacity(n), _array(alloc.allocate(_capacity)
				{
					for (size_type i = 0; i < _size; i++)
						_allocator.construct(_array + i, val);
					return;
				}

				//range
				template <class InputIterator>
					vector (InputIterator first, InputIterator last,
							const allocator_type& alloc = allocator_type()) : _allocator(alloc), _size(0), _capacity(0), _array(NULL)
					{
						size_type n = 0;
						for (InputIterator it = first; it != last; it++)
						{
							n++;
						}
						if (n == 0)
							return;
						_capacity = n;
						_capacity = n;
						_array = _allocator.allocate(_capacity);
						while (first != last)
						{
							_allocator.construct(_array + _size, *first);
							_size++;
							first++;
						}
						return;
					}

				//copy
				vector (const vector & x) : _allocator(vector._allocator), _size(vector._size), _capacity(vector._capacity), _array(NULL)
			{
				if (vector.size == 0)
					return;
				_array = _allocator.allocate(_capacity);
				for (size_type i = 0; i < vector._size; i++)
				{
					_allocator.construct(_array + i, vector._array[i]));
				}
				return;
			}

				//operator=	
				vector& operator=(const & vector x);
				//Destructor
				~vector()
				{
					this->clear();
					if (_capacity != 0)
						_allocator.deallocate(_array, _capacity);
				}

				//	****MEMBER FUNCTION ****
				//iterator
				begin;
				end;
				rbegin;
				rend;

				//Capacity
				size;
				max_size;
				resize;
				capacity;
				empty;
				reserve;
				//Element access
				operator[];
				at;
				front;
				back;

				//Modifiers
				assign;
				push_back;
				pop_back;
				insert;
				erase;
				swap;
				clear;
				//Allocator
				get_allocator;

			private:

			protected:
		};
	relational operators(){};
	swap(){};
};
#endif
