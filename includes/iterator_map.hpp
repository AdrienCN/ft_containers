#ifndef ITERATOR_MAP
#define ITERATOR_MAP

namespace ft
{
	template <typename T>
		class iterator_map : public ft::iterator<ft::bidirectional_tag, T>
	{
		public:
			typedef std::ptrdiff_t			difference_type;
			typedef T						value_type;
			typedef T&						reference;
			typedef T*						pointer;
			typedef ft::bidirectional_tag	iterator_category;
			typedef node<T>					node;

			//Attribut
			node		*_ptr;
			//Constructors
			iterator_map () : _ptr(NULL) {};

			iterator_map (ptr *ptr) : _ptr(ptr) {};
			iterator_map (const iterator_map &src) : _ptr(src._ptr) {};

			iterator_map & operator=(const iterator_map<T> & src)
			{
				if (*this == src)
					return *this;
				_ptr = src._ptr;
				return *this;
			}

			virtual ~iterator_map() {};

			bool operator==(const iterator_map & rhs)
			{
				return (_ptr == rhs)
			}

			bool operator!=(const iterator_map & rhs)
			{
				return (_ptr != rhs)
			}

			reference operator*() const
			{
				return (_ptr->_pr);
			}

			pointer operator->() const
			{
				return (&(_ptr->_pr))
			}

			iterator_map	operator++()
			{
				node	*current = _ptr;
				//Trouve la plus petite valeur de ma branche droite
				if (current->right)
					_ptr = findMinChild(current->right);
				//Trouve mon premier parent > moi
				else
				{
					node	*parent = _ptr->parent;
					//Remonter l'arbre:
					//Tant que j'ai un parent ET que je suis son fils droit
					while (parent && parent->right == current)
					{
						current = parent;
						parent = parent->parent;
					}
					_ptr = parent;
				}
				return (*this);
			}

			iterator_map	operator++(int)
			{
				iterator_map tmp(*this);
				++(*this);
				return tmp;
			}

			iterator_map	operator--()
			{
				if (_ptr->left)
					_ptr = findMaxChild(ptr->left);
				else
				{
					node *parent = _ptr->parent;
					node *current = _ptr;
					while (parent && parent->left == current)
					{
						current = parent;
						parent = parent->parent;
					}
					_ptr = parent;
				}
				return (*this);
			}

			iterator_map	operator--(int)
			{
				iterator_map tmp(*this);
				--(*this);
				return tmp;
			}
			//end of iterator_map
	};

	//end of namespace
};
#endif
