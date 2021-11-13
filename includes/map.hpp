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

				typedef ft::iterator_map<value_type>						iterator;
				typedef ft::const_iterator_map<value_type>					const_iterator;

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
				t_node*		_root; // root node
				t_node*		_end; //EMPTY right child of the most right node ---->  end
				t_node*		_begin; // PREroot node ---> rend
				key_compare		_comp;
				allocator_type	_allocator;
				size_type		_size;


			public:

				//Constructor
				explicit map (const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type())
					: _root(NULL), _comp(comp), _allocator(alloc), _size(0) 
				{
					_root = new_node();
					_begin = new_node();
					_end = new_node();

					// begin <-- root R-->end
					_root->parent = _begin; 
					_root->right = _end;

					//begin L--> root | R -->root
					_begin->left = _root;
					_begin->right = _root;
					_begin->parent = NULL;

					// root <-- end
					_end->parent = _root;
					_end->right = NULL;
					_end->left = NULL;
				}

				template <class InputIterator>
					map (InputIterator first, InputIterator last,
							const key_compare& comp = key_compare(),
							const allocator_type& alloc = allocator_type()) :_root(NULL), _comp(comp), _allocator(alloc), _size(0)
					{
						for (InputIterator it(first) ; it != last; it++)
							this->insert_node(*it, _root);
					}

				map (const map& x) : _root(NULL), _comp(x._comp), _allocator(x._allocator), _size(0)
				{
					for (iterator it = x.begin(); it != x.end(); it++)
						this->insert_node(*it, _root);
				}

				map & operator=(const map& x)
				{
					if (*this == x)
						return *this;
					map tmp(x);
					this.swap(tmp);
					return *this;
				}


				virtual ~map()
				{
					//detruit branche gauche puis droite
					this->clear();
					//detruire root
					this->_free_node(_root);
				}

				//Iterator
				//begin == root
				iterator begin()
				{
					return (_root->findMinChild(_root));
				}
				const_iterator begin() const
				{
					return (_root->findMinChild(_root));
				}

				// empty right child of most right node
				iterator end()
				{
					if (this->empty()) // defini dans cplusplus
						return (this->begin());
					return (this->_end)
				}
				const_iterator end() const
				{
					if (this->empty())
						return (this->begin());
					return (this->_end);
				}

				//end()-->parent ou  
				iterator rbegin()
				{
					return (_end->_parent);
				}
				const_iterator rbegin() const
				{
					return (_end->_parent);
				}
				//rend() == Preroot
				iterator rend()
				{
					return (this->_begin);
				}

				const_iterator rend() const
				{
					return (this->_begin);
				}

				//Capacity
				bool empty() const
				{
					return (this->_size == 0 ? true : false);
				}

				size_type size() const
				{
					return (this->_size);
				}

				size_type max_size() const
				{
					return (this->_allocator.max_size());
				}

				//Element Access
				mapped_type & operator[](const key_type &k)
				{
					node *needle = find_node_key(_root);
					if (needle)
						return (needle->_pr.second);
					else
					{
						node *new_node = create_node(value_type (k, mapped_type()));
						_insert(new_node);
						return mapped_type();
					}
				}

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
