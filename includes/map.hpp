#ifndef MAP_HPP
#define MAP_HPP

//std::less
#include <functional>

namespace ft
{
	template <class value_type > 
		class node
		{
			public:
				//constructeur
				node (void) : _parent(NULL), _left(NULL), _right(NULL) {}
				node (const value_type & pr) : _parent(NULL), _left(NULL), _right(NULL), _pr(pr) {}
				node (const node &src) : _parent(src._parent), _left(src._left), _right(src._right), _pr(src._pr) {};
				node & operator=(const node &src)
				{
					if (*this == src)
						return *this;
					_parent = src._parent;
					_left = src._left;
					_right = src._right;
					_pr = src._pr;
					return *this;
				}

				//**Attribut
				node			*parent;
				node			*left;
				node			*right;
				value_type			_pr;

				//Function membre

				node* findMinChild(const node & subtree)
				{
					node *current = subtree;
					while (current->left)
						current = current->left;
					return current;
				}

				node* findMaxChild(const node & subtree)
				{
					node* current = subtree;
					while (current->right)
						current = current->right;
					return current;
				}
				//end of node class
		};


	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
		class map
		{
			public:
				
				typedef Key		key_type;
				typedef T		mapped_type;
				typedef typename ft::pair<const key_type, mapped_type>	value_type;
				typedef	Compare											key_compare;
				typedef Alloc											allocator_type;	
				typedef allocator_type::reference						reference;
				typedef	allocator_type::const_reference					const_reference;
				typedef allocator_type::pointer							pointer	;
				typedef allocator_type::const_pointer					const_pointer;

				typedef iterator_map<value_type>						iterator;
				typedef const_iterator_map<value_type>					const_iterator;

				typedef ft::reverse_iterator<iterator>					reverse_iterator;
				typedef ft::const_reverse_iterator<iterator>			const_reverse_iterator;
				typedef ft::iterator_traits<iterator>::difference_type	difference_type;
				typedef	std::size_t										size_type;

				class value_compare
				{
					protected:
						//Objet de type std::less<key_type>
						Compare					_comp;

						//Constructeur
						value_compare (Compare c) : _comp(c) {};
					public:

						//value_type = pair<Key, Map>
						bool operator()(const value_type &x, const value_type, &y) const
						{
							//std::less()(Key x, Key y)
							return _comp(x.first, y.first);
						}
				}
				
			protected:
				//Attribut
				t_node *		_root;
				key_compare		_comp;
				allocator_type	_allocator;


			public:

				//Constructor



				//Iterator

				
				//Capacity
				empty
				size
				max_size

				//Element Access
				operator[]
				

				//Modifiers
				insert
				erase
				swap
				clear

				//Observer
				key_comp
				value_comp


				//Operation
				find
				count
				lower_bound
				upper_bound
				equal_range

				//Allocator
				

			private :
				//Mes fonctions utils perso

				//fin de class map
		};
	//end of ft namespace
};
#endif
