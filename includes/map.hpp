#ifndef MAP_HPP
#define MAP_HPP


// std::cout for degub --> To remove before push
#include <iostream> 

//std::less
#include <functional>

//std::allocator
#include <memory>
#include "iterator.hpp"
#include "condition.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "iterator_map.hpp"
#include "node.hpp"
namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
		class map
		{
			public:

				typedef Key		key_type;
				typedef T		mapped_type;
				typedef typename ft::pair<const key_type, mapped_type>	value_type;
				typedef	Compare											key_compare;
				typedef Alloc											allocator_type;	
				typedef typename allocator_type::reference						reference;
				typedef	typename allocator_type::const_reference					const_reference;
				typedef typename allocator_type::pointer							pointer	;
				typedef typename allocator_type::const_pointer					const_pointer;

				typedef ft::iterator_map<value_type>						iterator;
				typedef ft::const_iterator_map<value_type>					const_iterator;

				typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
				typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
				typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
				typedef	std::size_t										size_type;
				typedef ft::node<value_type>								node;
				typedef typename std::allocator<node>			allocator_type_node;

				class value_compare
				{
					protected:
						//Objet de type std::less<key_type>
						Compare					_comp;
						//Constructeur
						value_compare (Compare c) : _comp(c) {};
					public:
						//value_type = pair<Key, Map>
						bool operator()(const value_type &x, const value_type &y) const
						{
							//std::less()(Key x, Key y)
							//true --> left < right 
							return _comp(x.first, y.first);
						}
				};

			protected:
				//Attribut
				node*				_root; // root node
				node*				_end; //EMPTY right child of the most right node ---->  end
				node*				_preRoot; // PREroot node ---> rend
				key_compare			_comp;
				allocator_type		_allocator;
				allocator_type_node	_allocator_node;
				size_type			_size;


			public:

				//Constructor
				explicit map (const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type())
					: _root(NULL), _comp(comp), _allocator(alloc), _size(0) 
				{
					_preRoot = _new_node();
					_end = _new_node();

					// begin <-- root R-->end
					// pbm si ROOT = NULL
					_root->parent = _preRoot; 
					_root->right = _end;

					//begin L--> root | R -->root
					_preRoot->left = _root;
					_preRoot->right = _root;
					_preRoot->parent = NULL;

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
					this->insert(*it, _root);
			}

				map (const map& x) : _root(NULL), _comp(x._comp), _allocator(x._allocator), _size(0)
			{
				for (iterator it = x.begin(); it != x.end(); it++)
					this->insert(*it, _root);
			}

				map & operator=(const map& x)
				{
					if (*this == x)
						return *this;
					map tmp(x);
					this->swap(tmp);
					return *this;
				}


				virtual ~map()
				{
					//detruit branche gauche puis droite
					this->clear();
					//detruire root
					this->_freeNode(_root);
				}

				//Iterator
				//begin == root
				iterator begin()
				{
					return (_findMinChild(_root));
				}
				const_iterator begin() const
				{
					return (_findMinChild(_root));
				}

				// empty right child of most right node
				iterator end()
				{
					if (this->empty()) // defini dans cplusplus
						return (this->begin());
					return (this->_end);
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
					return (this->end()); //selon moi ajouter - 1);
				}
				const_iterator rbegin() const
				{
					return (this->end()); // selon moi ajouter - 1);
				}
				//rend() == Preroot
				iterator rend()
				{
					return (this->_preRoot);
				}

				const_iterator rend() const
				{
					return (this->_preRoot);
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
					node *needle = _findKey(_root);
					if (needle)
						return (needle->_pr.second);
					else
					{
						node *new_node = _newNode(value_type (k, mapped_type()));
						this->insert(new_node);
						return mapped_type();
					}
				}

				//Modifiers
				pair<iterator, bool>	insert(const value_type &val) 
				{
					//Cherche si la key est deja presente
					node *needle = _findKey(_root, val.first);

					//Noeud absent. On l'insere
					if (needle == NULL)
					{	
						//Insere ET balance
						//return new balanced tree ROOT
						_root = this->myInsert(_root, val, 0);
						//update les iterator de pos
						this->_updatePosition(_root);
						iterator it(_findKey(_root, val.first));
						this->_size += 1;
						return (ft::make_pair<iterator, bool> (it, true));
					}
					//Noeud deja present
					else
					{
						iterator it(needle);
						return (ft::make_pair<iterator, bool> (it, false));
					}
				}


		}

	iterator insert(const iterator it, const value_type &val) 
	{
		return (this->insert(val).first);
	}


	template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				this->insert(*first);
				first++;
			}
		}

	/*	erase
		swap
		*/	void clear() {}

	/*	//Observer
		key_comp
		value_comp


	//Operation
	find
	count
	lower_bound
	upper_bound
	equal_range

	//Allocator


	//autes
	*/	void swap(const value_type & x)
	{
		(void)x;
	}

	private :

	void	_updatePosition(void)
	{
		node *max_child = findMaxChild(_root);

		_preRoot->right = _root;
		_preRoot->left = _root;
		_root->parent = _preRoot;

		_end->parent = max_child;
		max_child->right = _end;
	}

	node* _findMinChild(const node & subtree)
	{
		node *current = subtree;
		while (current->left)
			current = current->left;
		return current;
	}

	node* _findMaxChild(const node & subtree)
	{
		node* current = subtree;
		while (current->right)
			current = current->right;
		return current;
	}

	node* _myInsert(node *node, const value_type &val, int side)
	{
		typedef val.first		new_key;
		typedef node->pr.first	node_key;

		// side : 0 = root | 1 = left | 2 = right	
		//base case one
		if (node == NULL)
			return (_newNode(node, val, side));
		//base case two
		//if (new_key == node_key)
		//return (node);

		// new_key < node_key. Insertion gauche
		if (_comp(new_key, node_key) == true)
			node->left = this->_myInsert(node->left, val, 1);
		// new_key > node_key .  Insertion droite
		else if (_comp(new_key, node_key) == false)
			node->right = this->_myInsert(node->right, val, 2); 
		//Key == cur_key. Deja present . Pas d'insertion
		else
			return (node);

		//calculer la nouvelle height
		node->height = _getHeight(node);

		//balancer l'arbre apres l'insertion
		int balance = _isBalanced(node, val);

		//Tree is NOT balanced
		//rotate for balancing and return new subroot
		if (balance != 0)
			return (this->_doRotation(node, balance));
		else
			return (node); // Subtree is balanced return unchanged subroot
	}

	node* _doRotation(node *node, int scenario)
	{
		//left branch is heavy
		if (scenario < - 1)
		{
			//if new_key < node->left->key
			//left left case
			if (_comp(new_key, node->left->key) == true)
				return (_rightRotate(node));
			//left right case
			else
			{
				node->left = _leftRotate(node->left);
				return (_rightRotate(node));
			}
		}
		//Right branch is heavy
		else if (scenario > 1)
		{
			if (_comp(new_key, node->right->key) == false)
				return (_leftRotate(node));
			else
			{
				node->right = _rightRotate(node->right);
				return (_leftRotate(node));
			}
		}
		else
		{
			std::cout << "There is a problem in DO_ROTATION" << std::endl;
		}
		return (NULL);
	}

	int _isBalanced(node *node, const value_type &val)
	{
		return (_getHeight(node->right) - _getHeight(node->left));
	}


	size_t _getHeight(node *node)
	{
		if (node == NULL)
			return (0);
		size_t right = _getHeight(node->right);
		size_t left = _getHeight(node->left);

		return ((right > left ? right : left) + 1);
	}

	node* _rightRotate(node *y)
	{
		node	*x = y->left;
		node	*x_right = x->right;

		x->right = y;
		y->left = x_right;
		return (x);
	}

	node* _leftRotate(node *y)
	{
		node	*x = y->right;
		node	*x_left = x->left;

		x->left = y;
		y->right = x_left;
		return (x);
	}

	//Mes fonctions utils perso
	node*	_findKey(node* node, const value_type &val) 
	{
		typedef val.first		new_key;
		typedef node->pr.first	node_key;

		if (node == NULL)
			return (NULL);

		if (_comp(new_key, node_key) == true)
			return (this->_findKey(node->left, val));
		else if (_comp(new_key, node_key) == false)
			return (this->_findKey(node->right, val));
		else
			return (node);
	}

	// side : 0 = root | 1 = left | 2 = right
	node*	_newNode(node *parent, const value_type & val, int side)
	{
		node *new_node = _allocator_node.allocate(1);
		_allocator.construct(new_node, node(val));
		if (side == 0) // root case
		{
			//free_root (si on avait alloue un null_node a root)
			return (new_node);
		}
		else
		{
			new_node->parent = parent;
			if (side == 1)
				parent->left = new_node;
			else
				parent->right = new_node;
		}
		return (new_node);
	}
	node*	_newNode(const value_type & val)
	{
		node *new_node = _allocator_node.allocate(1);

		_allocator_node.construct(new_node, node(val));
		return (new node(val));
	}

	void	_freeNode(node *subtree) 
	{
		(void)subtree;
	}

	//fin de class map
};
//end of ft namespace
};
#endif
