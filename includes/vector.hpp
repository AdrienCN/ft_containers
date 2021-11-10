#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "iterator_vector.hpp"
#include "condition.hpp"
#include <stdexcept>
#include <memory>


//std::allocator

#define SPACE _size * 2		
#define MIN_SPACE 128


namespace ft
{

	template <typename T, class Alloc = std::allocator<T> >
		class vector 
		{
			public:

				//  ****TYPEDEF  *****
				typedef T											value_type;
				typedef Alloc										allocator_type;
				typedef	typename allocator_type::reference					reference;
				typedef typename allocator_type::const_reference				const_reference;
				typedef typename allocator_type::pointer						pointer;
				typedef typename allocator_type::const_pointer				const_pointer;
				typedef typename ft::iterator_vector<T>						iterator;
				typedef typename ft::const_iterator_vector<T>				const_iterator;
				typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
				typedef	std::ptrdiff_t								difference_type;
				typedef std::size_t									size_type;

			protected:
				//	****ATTRIBUTES****

				allocator_type	_allocator;
				size_type	_size;
				size_type	_capacity;
				pointer		_array;

			public:
				//	****Constructor*****
				//Default
				explicit vector(const allocator_type & alloc = allocator_type()) :  _allocator(alloc), _size(0), _capacity(0), _array(NULL) 
			{
				return;
			}
				//fill
				explicit vector (size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type()): _allocator(alloc), _size(n), _capacity(_size), _array(_allocator.allocate(_capacity))
			{
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(_array + i, val);
				return;
			}

				//range
				template <class InputIterator>
					vector (InputIterator first, InputIterator last,
							const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type =true) : _allocator(alloc), _size(0), _capacity(0), _array(NULL)
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
				vector (const vector & x) : _allocator(x._allocator), _size(x._size), _capacity(x._capacity), _array(NULL)
			{
				if (x.size() == 0)
					return;
				_array = _allocator.allocate(_capacity);
				for (size_type i = 0; i < x._size; i++)
				{
					_allocator.construct(_array + i, x._array[i]);
				}
				return;
			}

				//operator=	
				vector& operator=(vector const & x)
				{
					if (*this == x)
						return (*this);
					this->~vector();
					vector tmp(x);
					this->swap(tmp);
					return (*this);
				}

				//Destructor
			virtual	~vector()
				{
					this->clear();
					if (_capacity != 0)
						_allocator.deallocate(_array, _capacity);
				}

				//	****MEMBER FUNCTION ****
				//iterator
				iterator begin()
				{
					return iterator(_array);
				}

				const_iterator begin() const
				{
					return const_iterator(_array);
				}

				iterator end()
				{
					return iterator(_array + _size);
				}

				const_iterator end() const
				{
					return const_iterator(_array + _size);
				}

				reverse_iterator rbegin()
				{
					return reverse_iterator(this->end());// - 1);
				}

				const_reverse_iterator rbegin() const
				{
					return const_reverse_iterator(this->end());// - 1);
				}

				reverse_iterator rend()
				{
					return reverse_iterator(this->begin());// - 1);
				}

				const_reverse_iterator rend() const
				{
					return const_reverse_iterator(this->begin()); //- 1 );
				}



				//Capacity
				size_type size() const
				{
					return (_size);
				}

				size_type max_size() const
				{
					return (_allocator.max_size());
				}

				void	resize(size_type n, value_type val = value_type())
				{
					if (n < _size)
					{
						for (size_type i = n; i < _size; i++)
						{
							_allocator.destroy(_array + i);
							_allocator.deallocate(_array + i, 1);
						}
						_size = n;
						// _allocator.deallocate(_array + n, (n - _size));
						//reduce size;
						return;
					}
					if (n > _size)
					{
						//add capacity first
						if (n > _capacity)
							this->reserve(SPACE + n);
						//add new element
						while (_size < n)
						{
							_allocator.construct(_array + _size, val);
							_size++;
						}
					}
				}

				size_type	capacity() const
				{
					return (_capacity);
				}

				bool		empty() const
				{
					return (_size == 0 ? true : false);
				}

				void	reserve(size_type n)
				{
					if (n > _capacity)
					{
						pointer newarray;
						newarray = _allocator.allocate(n);
						for (size_type i = 0; i < _size; i++)
							_allocator.construct(newarray + i, _array[i]);
						this->~vector();
						_capacity = n;
						_array = newarray;
					}
				}
				//Element access
				reference	operator[](size_type n)
				{
					return _array[n];
				}

				const_reference		operator[](size_type n) const
				{
					return _array[n];
				}

				reference at(size_type n)
				{
					if (n < 0 || n >= _size)
						throw std::out_of_range("out_of_range");
					return _array[n];
				}

				const_reference at(size_type n) const
				{
					if (n < 0 || n >= _size)
						throw std::out_of_range("out_of_range");
					return _array[n];
				}

				reference front()
				{
					return _array[0];
				}
				const_reference front() const
				{
					return _array[0];
				}
				reference back()
				{
					return _array[_size - 1];
				}
				const_reference back() const
				{
					return _array[_size - 1];
				}

				//Modifiers
				template <typename InputIterator>
					void	assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type =true)
					{
						this->clear();
						size_type new_size = 0;
						for (InputIterator tmp = first; tmp != last; tmp++)
							new_size++;
						this->reserve(new_size);
						_size = 0;
						while (first != last)
						{
							_allocator.construct(_array + _size, *first);
							first++;
							_size++;
						}
					}
				void assign(size_type n, const value_type &val)
				{
					this->clear();
					this->reserve(n);
					for (size_type i = 0; i < n; i++)
						_allocator.construct(_array + i, val);
					_size = n;
				}

				void	push_back(const value_type& val)
				{
					if (_capacity == 0)
						this->reserve(1);
					if (_size + 1 >= _capacity)
						this->reserve(SPACE);
					_allocator.construct(_array + _size, val);
					_size++;
				}
				void	pop_back()
				{
					/*if (_size == 0)
					  return;
					  */
					_allocator.destroy(_array + _size);
					_size--;
				}
				iterator insert (iterator position, const value_type &val)
				{
					size_type pos = position._ptr - _array;
					this->insert(position, 1, val);
					return (iterator(this->begin() + pos));
				}

				void insert (iterator position , size_type n, const value_type &val)
				{
					if (n == 0)
						return;
					size_type index = position._ptr - _array; //emplacement de la position ?
					if (_size + n >= _capacity)
						this->reserve(SPACE + n);
					vector tmp_array(iterator(_array + index), iterator(this->end()));
					//detruire tout les elements depuis index
					for (size_type i = index; i < _size; i++)
					{
						_allocator.destroy(_array + i);
					}
					//Insere les new elements
					for (size_type i = 0; i < n; i++)
						this->push_back(val);
					//Reinsere les elements detruits APRES les new elements
					for (iterator it = tmp_array.begin(); it != tmp_array.end(); it++)
						this->push_back(*it);
					_size += n;
				}

				template <typename InputIterator>
					void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true)
					{
						// nbr d'element a inserer
						size_type n = 0;

						for (InputIterator it = first; it != last; it++)
							n++;
						if (n == 0)
							return;

						//position a partir de laquelle il faut inserer
						size_type index = position._ptr - _array; 

						//Vector qui retient tout apres "position"
						vector tmp_array(iterator(_array + index), iterator(this->end()));
						if (_size + n >= _capacity)
							this->reserve(SPACE + n);
						for (size_type i = index; i < _size; i++)
						{
							_allocator.destroy(_array + i);
						}
						while (first != last)
						{
							_allocator.construct(_array + index, *first);
							first++;
							index++;
						}
						for (iterator it = tmp_array.begin(); it != tmp_array.end(); it++)
							this->push_back(*it);
						_size +=n;
					}


				iterator erase (iterator position)
				{
					if (this->empty() || position == this->end())
						return (this->end());

					if ((position + 1) == this->end())
					{
						this->pop_back();
						return (this->end());
					}

					_allocator.destroy(position._ptr);
					for (iterator pos = position; pos + 1 != this->end(); pos++)
					{
						_allocator.construct(pos._ptr, *(pos._ptr + 1));
						_allocator.destroy(pos._ptr + 1);
					}
					_size--;
					return (position);
				}

				iterator erase (iterator first, iterator last)
				{
					if (this->empty() || first == this->end())
						return (this->end());
					if (first == last)
						return (first);
					size_type count = last._ptr - first._ptr;
					for (size_type i = 0; i < count; i++)
					{
						_allocator.destroy(first._ptr + i);
						_allocator.construct(first._ptr + i, *(last._ptr + i));
						_allocator.destroy(last._ptr + i);
					}
					_size -= count;
					return (first);
				}

				void swap(vector& x)
				{
					allocator_type	tmp_alloc	= _allocator;
					size_type		tmp_size	= _size;
					size_type		tmp_cap		= _capacity;
					pointer			tmp_array	= _array;

					_array = x._array;
					_capacity = x._capacity;
					_size = x._size;
					_allocator = x._allocator;

					x._array = tmp_array;
					x._allocator = tmp_alloc;
					x._size = tmp_size;
					x._capacity = tmp_cap;
				}

				void	clear()
				{
					while (_size > 0)
					{
						_allocator.destroy(_array + (_size - 1));
						_size--;
					}
				}
				//Allocator
				allocator_type get_allocator() const
				{
					return _allocator;
				}

			private:

				//end of class vector
		};
	template <class T, class Alloc>
		bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

	template <class T, class Alloc>
		bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (!(lhs == rhs));
		}

	template <class T, class Alloc>
		bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

	template <class T, class Alloc>
		bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (!(rhs < lhs));
		}

	template <class T, class Alloc>
		bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (rhs < lhs);
		}


	template <class T, class Alloc>
		bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (!(lhs < rhs));
		}

	template <class T, class Alloc>
		void swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
		{
			x.swap(y);
		}
	//End of namespace
};

#endif
