#ifndef ITERATOR_MAP
#define ITERATOR_MAP
#include  "node.hpp"
#include  "iterator.hpp"
//for debug to remove
#include <iostream>
namespace ft
{
	template<typename T>
	class const_iterator_map;

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

			iterator_map (node *ptr) : _ptr(ptr) {};
			iterator_map (const iterator_map &src) : _ptr(src._ptr) {};
			iterator_map & operator=(const iterator_map & src)
			{
				if (*this == src)
					return *this;
				_ptr = src._ptr;
				return *this;
			}

			virtual ~iterator_map() {};

			bool operator==(const const_iterator_map<T> & rhs) const
			{
				return (_ptr == rhs._ptr);
			}

			bool operator!=(const const_iterator_map<T> & rhs) const
			{
				return (_ptr != rhs._ptr);
			}

			reference operator*() const
			{
				return (_ptr->pr);
			}

			pointer operator->() const
			{
				return (&(_ptr->pr));
			}

			iterator_map & operator++()
			{
				node	*current = _ptr;
				//Trouve la plus petite valeur de ma branche droite
				if (current->right != NULL)
					_ptr = findMinChild(current->right);
				else
				{

					node	*parent = current->parent;
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

			iterator_map & operator--()
			{
				if (_ptr->left)
					_ptr = findMaxChild(_ptr->left);
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
		private:
		node* findMinChild(node *subtree)
				{
					if (subtree == NULL)
						return (NULL);
					node *current = subtree;
					while (current->left)
						current = current->left;
					return current;
				}

				node* findMaxChild(node *subtree)
				{
					if (subtree == NULL)
						return (NULL);
					node *current = subtree;
					while (current->right && current->right)
						current = current->right;
					return current;
				}
			//end of iterator_map
	};

	template <typename T>
		class const_iterator_map : public ft::iterator<ft::bidirectional_tag, T>
	{
		public:
			typedef std::ptrdiff_t					difference_type;
			typedef const T							value_type;
			typedef const T&						reference;
			typedef const T*						pointer;
			typedef ft::bidirectional_tag	iterator_category;
			typedef node<T>					node;

			//Attribut
			node*	_ptr;
			//Constructors
			const_iterator_map () : _ptr(NULL) {};
			const_iterator_map (node *ptr) : _ptr(ptr) {};
			const_iterator_map (const const_iterator_map &src) : _ptr(src._ptr) {};
			const_iterator_map (const iterator_map<T> &src) : _ptr(src._ptr) {};
			const_iterator_map & operator=(const const_iterator_map & src)
			{
				if (*this == src)
					return *this;
				_ptr = src._ptr;
				return *this;
			}

			virtual ~const_iterator_map() {};

			bool operator==(const const_iterator_map & rhs) const
			{
				return (_ptr == rhs._ptr);
			}

			bool operator!=(const const_iterator_map & rhs) const
			{
				return (_ptr != rhs._ptr);
			}

			reference operator*() const
			{
				return (_ptr->pr);
			}

			pointer operator->() const
			{
				return (&(_ptr->pr));
			}

			const_iterator_map & operator++()
			{
				/*node *cur = _ptr;
				if (cur->right)
				{
					std::cout << "it->right exist" << std::cout;
					cur = cur->right;
					while (cur->left)
						cur = cur->left;
					_ptr = cur;
					return (_ptr);
				}
				std::cout << "it->right == NULL" << std::cout;

				while (cur != cur->parent->left)
				{
					if (cur->is_root == true)
						cur = cur->right;
					else
						cur = cur->parent;
				}
				_ptr = cur;
				return (_ptr);
			}

*/


				
				std::cout << "it++ start" << std::endl;
				node	*current = _ptr;
				//Trouve la plus petite valeur de ma branche droite
				if (current->right)
				{
					std::cout << "it->right exist" << std::endl;
					_ptr = findMinChild(current->right);
				}//Trouve mon premier parent > moi
				else
				{
					std::cout << "_ptr->first == " <<  _ptr->pr.first << std::endl;
					std::cout << "_ptr->left->first == " <<  _ptr->left->pr.first << std::endl;
					std::cout << "_ptr->right->first == " <<  _ptr->right->pr.first << std::endl;
					std::cout << "it->right == NULL" << std::endl;
					node	*parent = _ptr->parent;
					
					//Remonter l'arbre:
					//Tant que j'ai un parent ET que je suis son fils droit
					while (parent && parent->right == current)
					{
						
						std::cout << "parent->first == " << parent->pr.first << std::endl;
						if (parent->left)
							std::cout << "parent->left->first == " << parent->left->pr.first << std::endl;
						if (parent->right)
							std::cout << "parent->right->first == " << parent->right->pr.first << std::endl;
						if (parent->is_root == true)
							std::cout << "ERROR : probing _preRoot" << std::endl;
						current = parent;
						parent = parent->parent;
					}
					_ptr = parent;
				}
				std::cout << "it++ end" << std::endl;
				return (*this);
				
			}

			const_iterator_map	operator++(int)
			{
				const_iterator_map tmp(*this);
				++(*this);
				return tmp;
			}

			const_iterator_map & operator--()
			{
				if (_ptr->left)
					_ptr = findMaxChild(_ptr->left);
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

			const_iterator_map	operator--(int)
			{
				const_iterator_map tmp(*this);
				--(*this);
				return tmp;
			}
			//end of const_iterator_map
		private:
		node* findMinChild(node *subtree)
				{
					if (subtree == NULL)
						return (NULL);
					node *current = subtree;
					while (current->left)
						current = current->left;
					return current;
				}

				node* findMaxChild(node *subtree)
				{
					if (subtree == NULL)
						return (NULL);
					node *current = subtree;
					while (current->right)
						current = current->right;
					return current;
				}
	};
	//end of namespace
};
#endif
