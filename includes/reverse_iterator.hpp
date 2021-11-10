#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator.hpp"

namespace ft
{
	template <class Iterator>
		class reverse_iterator
		{

			public:

				// ********** MEMBER TYPES ********** 
				// inherited from iterator_traits + add iterator_type

				typedef Iterator iterator_type;           
				typedef typename iterator_traits<Iterator>::difference_type difference_type;            
				typedef typename iterator_traits<Iterator>::value_type value_type;
				typedef typename iterator_traits<Iterator>::pointer pointer;
				typedef typename iterator_traits<Iterator>::reference reference;
				typedef typename iterator_traits<Iterator>::iterator_category iterator_category; 


				// ********** MEMBER FUNCTIONS ********** 

				//---> Constructeurs, Destructeur et operateur=

				reverse_iterator(void) : _current() {} //constructeur par défaut

				explicit reverse_iterator(iterator_type it) : _current(it) {} //explicit pour eviter les conversion implicit

				template <class Src>
					reverse_iterator(const reverse_iterator<Src> & src) : _current(src.base()) {} //constructeur par copie

				template <class Src>
					reverse_iterator & operator=(const reverse_iterator<Src> & src)
					{
						_current = src.base();
						return *this;
					}

				virtual ~reverse_iterator() {}

				//---> Other member functions

				//___________ base() : Return the base iterator
				iterator_type base() const
				{
					return this->_current;
				}

				//____________ operators
				// La majorité des opération sont -n car c'est un reverse it donc reverse order

				reverse_iterator operator+(difference_type n) const
				{
					return reverse_iterator(base() - n); //_current -n possible
				}

				reverse_iterator& operator+=(difference_type n) //on modifie egalement current
				{
					_current -= n;
					return *this;
				}

				reverse_iterator& operator++()
				{
					_current--;
					return *this;
				}           

				reverse_iterator operator++(int)
				{
					reverse_iterator tmp = *this;
					++(*this);
					//_current--;
					return tmp;
				}

				reverse_iterator operator-(difference_type n) const
				{
					return reverse_iterator(base() + n);
				}

				reverse_iterator& operator-=(difference_type n) //on modifie egalement current
				{
					_current += n;
					return *this;
				}

				reverse_iterator& operator--()
				{
					_current++;
					return *this;
				}

				reverse_iterator operator--(int)
				{
					reverse_iterator tmp = *this;
					--(*this);
					// _current++;
					return tmp;
				}

				reference operator*() const // A RECHECKER retour function
				{
					iterator_type tmp(_current);
					tmp--;
					return *tmp; //return a reference to the element previous to current
				}

				pointer operator->() const // A RECHECKER retour function
				{
					return &(this->operator*());
				}

				reference operator[](difference_type n) const
				{
					return base()[-n -1]; //brunet != 
				}

			protected: //or private?
				iterator_type _current;
		};

	//  ********** NON MEMBER FUNCTIONS OVERLOADS ********** 

	//---> Relational operators

	template <class Iterator1, class Iterator2>
		bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.base() == rhs.base();
		}

	template <class Iterator1, class Iterator2>
		bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.base() != rhs.base();
		}

	template <class Iterator1, class Iterator2>
		bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.base() > rhs.base();
		}

	template <class Iterator1, class Iterator2>
		bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.base() < rhs.base();
		}

	template <class Iterator1, class Iterator2>
		bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.base() >= rhs.base();
		}

	template <class Iterator1, class Iterator2>
		bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.base() <= rhs.base();
		}

	//---> Operator + et - ===> A RECHECKER LES retours des functions

	template <class Iterator>
		reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it)
		{
			return it + n;
		}

	template <class Iterator1, class Iterator2>
		typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2>& rhs)
		{
			return rhs.base() - lhs.base();
		}
}
#endif
