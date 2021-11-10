#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "iterator_vector.hpp"

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
								const allocator_type & alloc = allocator_type()): _allocator(alloc), _size(n), _capacity(_size), _array(alloc.allocate(_capacity)
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
				
				const_iterator end()
				{
					return const_iterator(_array + _size);
				};

				reverse_iterator rbegin()
				{
					return reverse_iterator(end());// - 1);
				};
				
				const_reverse_iterator rbegin() const
				{
					return const_reverse_iterator(end());// - 1);
				}
				
				reverse_iterator rend()
				{
					return reverse_iterator(begin());// - 1);
				}
				
				const_reverse_iterator rend() const
				{
					return const_reverse_iterator(begin()); //- 1 );
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
							reserver(n);
						//add new element
						while (_size < n)
						{
							_allocator.construct(_array + _size, val)
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
							_allocator.construct(newarrray + i, _array[i]);
						~vector();
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
						throw std::out_of_range();
					return _array[n];
				}

				const_reference at(size_type n) const
				{
					if (n < 0 || n >= _size)
						throw std::out_of_range();
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
					void	assign(InputIterator firt, InputIterator last)
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
					_allocator.destroy(this->end() - 1);
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
					while (_size + n >= _capacity)
						this->reserve(SPACE);
					vector tmp_array(iterator(_array + index), iterator(this->end()));
					//detruire tout les elements depuis index
					for (size_type i = index; i < _size; i++)
					{
						_allocator.destroy(_array + i);
						_size--;
					}
					//Insere les new elements
					for (size_type i = 0; i < n; i++)
						this->push_back(val);
					//Reinsere les elements detruits APRES les new elements
					for (iterator it = tmp_array.begin(); it != tmp_array.end(); it ++)
						this->push_back(*it);
				}

				template <typename InputIterator>
					void insert (iterator position, InputIterator first, InputIterator last)
					{
					   	// nbr d'element a inserer
						size_type n;
						
						for (InputIterator it = first; it != last; it++)
							n++;
						if (n == 0)
							return;
						
						//position a partir de laquelle il faut inserer
						size_type index = position._ptr - _array; 

						//Vector qui retient tout apres "position"
						vector tmp_array(iterator(_array + index), iterator(this->end()));
						while (_size + n >= _capacity)
							this->reserve(SPACE);
						
						for (size_type i = index; i < _size; i++)
						{
							_allocator.destroy(_array + i);
							_size--;
						}
						while (first != last)
						{
							_allocator.construst(_array + index, *first);
							first++;
							index++;
							_size++;
						}
						for (iterator it = tmp_array.begin(); it != tmp_array.end(); it++)
						{
							this->push_back(*it);
							_size++;
						}
					}


				erase;
				
				swap (vector& x)
				{
					allocator_type	tmp_alloc	= _allocator;
					size_type		tmp_size	= _size;
					size_type		tmp_cap		= _capacity;
					pointer			tmp_array	= _array;
					
					_array = x._array;
					_capacity = x.capacity;
					_size = x.size;
					_allocator = x.get_allocator;

					x._array = tmp_array;
					x._allocator = tmp_alloc;
					x._size = tmp_size;
					x.capacity = tmp_capacity;
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

			protected:
		};
	relational operators(){};
	swap(){};
};
#endif
