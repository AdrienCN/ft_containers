#ifndef MAP_HPP
#define MAP_HPP


// std::cout for degub --> To remove before push
// exit for debug
#include <iostream> 
#include <stdlib.h>

#define GREEN "\033[0;32m" 
#define RED "\033[0;31m" 
#define RESET "\033[0;00m" 
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
					public:
						value_compare (Compare c) : _comp(c) {};
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
					: _root(_newNode()),_end(_newNode()), _preRoot(_newNode()), _comp(comp), _allocator(alloc), _size(0) 
				{
					// begin <-- root R-->end
					// pbm si ROOT = NULL
					_root->parent = _preRoot; 
					_root->right = _end;
					_root->is_root = true;

					//begin L--> root | R -->root
					_preRoot->left = _root;
					_preRoot->right = _root;
					_preRoot->parent = NULL;

					// root <-- end
					_end->parent = _root;
					_end->right = NULL;
					_end->left = NULL;
					_end->is_end = true;
				}

				template <class InputIterator>
					map (InputIterator first, InputIterator last,
							const key_compare& comp = key_compare(),
							const allocator_type& alloc = allocator_type()) :_root(_newNode()), _end(_newNode()), _preRoot(_newNode()), _comp(comp), _allocator(alloc), _size(0)
			{
				_root->parent = _preRoot; 
				_root->right = _end;
				_root->is_root = true;

				//begin L--> root | R -->root
				_preRoot->left = _root;
				_preRoot->right = _root;
				_preRoot->parent = NULL;

				// root <-- end
				_end->parent = _root;
				_end->right = NULL;
				_end->left = NULL;
				_end->is_end = true;
				//std::cout << "Before : _end - 1  = " << (--this->end())->first << "_begin = " << this->begin()->first <<  std::endl;
				/*std::cout << RED << "Range Construction start" << std::endl;
				std::cout << "iterator last = " << last->first << std::endl;
				std::cout << "\t//////" << std::endl;
			*/	while (first != last)
				{
			//		std::cout << "first = " << first->first << std::endl;
					this->insert(*first);
					first++;
					//this->_printNode(this->end());
				}
				//this->_printNode(this->end());
			//	std::cout << "Range Construction end " << RESET << std::endl;
				//std::cout << "After : _end - 1  = " << (--this->end())->first << "_begin = " << this->begin()->first <<  std::endl;

			}

				map (const map& x) : _root(_newNode()), _end(_newNode()), _preRoot(_newNode()), _comp(x._comp), _allocator(x._allocator), _size(0)
			{
				_root->parent = _preRoot; 
				_root->right = _end;
				_root->is_root = true;

				//begin L--> root | R -->root
				_preRoot->left = _root;
				_preRoot->right = _root;
				_preRoot->parent = NULL;

				// root <-- end
				_end->parent = _root;
				_end->right = NULL;
				_end->left = NULL;
				_end->is_end = true;

				for (const_iterator it = x.begin(); it != x.end(); it++)
				{
				//	std::cout << "test" << std::endl;
				//	std::cout << "- @) Copying key [" << it->first << "]" << std::endl;
					this->insert(*it);
				}
			}

				map & operator=(const map& x)
				{
					map tmp(x);
					this->swap(tmp);
					return *this;
				}


				virtual ~map()
				{
					//detruit tout sauf _preRoot 
					this->_deletePostOrder(_root);
					_freeNode(_preRoot);
				}

				//Iterator most left child
				iterator begin()
				{
					return (this->_findMinChild(_root));
				}

				const_iterator begin() const
				{
					return (this->_findMinChild(_root));
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
				reverse_iterator rbegin()
				{
					return (reverse_iterator(this->end())); //selon moi ajouter - 1) ? ;
				}
				const_reverse_iterator rbegin() const
				{
					return (const_reverse_iterator(this->end())); // selon moi ajouter - 1)?;
				}
				//rend() == Preroot
				reverse_iterator rend()
				{
					return (reverse_iterator(this->begin()));
				}

				const_reverse_iterator rend() const
				{
					return (const_reverse_iterator(this->begin()));
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
					/*
					   value_type val = make_pair(k, mapped_type());
					   node *needle = _findVal(_root, val);
					   if (needle)
					   return (needle->_pr.second);
					   else
					   {
					   this->insert(new_node);
					   return mapped_type();
					   }
					   */
					value_type val = ft::make_pair(k, mapped_type());
					iterator it = this->insert(val).first;
					return (it->second);
				}

				//Modifiers
				pair<iterator, bool>	insert(const value_type &val) 
				{
					//std::cout << "\t****insert : " << val.first << " ****" << std::endl;
					//Cherche si la key est deja presente
					node *needle = this->_findVal(_root, val);

					//Noeud absent. On l'insere
					if (needle == NULL)
					{	
					//	std::cout << "insert : needle == NULL (" << val.first <<") " << std::endl;
						//Insere ET balance
						//return new balanced tree ROOT

						//deal with root case. Only for the first insertion
						if (_root->is_init == false && _root->left == NULL && (_root->right == NULL || _root->right == _end))
							_root = _initTree(_root, val);
						else
							_root = this->_myInsert(_root, _root, val);
				//		std::cout << RED << "New ROOT = " << _root->pr.first << RESET <<  std::endl;
						//update les iterator de pos
						this->_updatePosition();
					//	this->_printInorder(_root);
					//	this->_printTest(_root);
						this->_size += 1;
						iterator it(_findVal(_root, val));

//						std::cout << "\t****insert terminated ****\n"  << std::endl;
						return (ft::make_pair<iterator, bool> (it, true));
					}
					else
					{
						iterator it(needle);
//						std::cout << "insert : needle == exist " << std::endl;
						return (ft::make_pair<iterator, bool> (it, false));
					}
				}


				iterator insert(const iterator it, const value_type &val) 
				{
					(void)it;
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

				void	erase(iterator position)
				{
					this->erase(position->first);
				}

				size_type erase(const key_type& k)
				{
					value_type val = ft::make_pair(k, mapped_type());
					node *needle = _findVal(_root, val);
					if (needle)
					{
						_root = this->_myErase(_root, val);
						this->_updatePosition();
						_size -= 1;
						return (1);
					}
					else
						return (0);
				}

				void erase (iterator first, iterator second)
				{
					while (first != second)
					{
						this->erase(first->first);
						first++;
					}
				}


				void swap(map & x)
				{

//					std::cout << GREEN << "SWAPING" << std::endl;

					node				*tmp_root = x._root;
					node				*tmp_end = x._end;
					node				*tmp_preRoot = x._preRoot;
					key_compare			tmp_comp = x._comp;
					allocator_type		tmp_allocator = x._allocator;
					allocator_type_node	tmp_allocator_node = x._allocator_node;
					size_type			tmp_size = x._size;

					x._root = _root;
					x._end = _end;
					x._preRoot = _preRoot;
					x._comp = _comp;
					x._allocator = _allocator;
					x._allocator_node = _allocator_node;
					x._size = _size;

					_root = tmp_root;
					_end = tmp_end;
					_preRoot = tmp_preRoot;
					_comp = tmp_comp;
					_allocator = tmp_allocator;
					_allocator_node = tmp_allocator_node;
					_size = tmp_size;
//					std::cout  << "SWAP_END " <<  RESET << std::endl;
				}

				void clear() 
				{
					this->_deletePostOrder(_root);
					_updatePosition();
					_size = 0;
				}

				//Observer
				key_compare key_comp() const
				{
					return (_comp);
				}

				value_compare value_comp() const
				{
					return (value_compare(_comp));
				}


				//Operation
				iterator find (const key_type &k)
				{
					node *needle = this->_findVal(_root, ft::make_pair(k, mapped_type()));
					if (needle)
						return (needle);
					else
						return (_end);
				}

				const_iterator find (const key_type &k) const
				{
					node *needle = this->_findVal(_root, ft::make_pair(k, mapped_type()));
					if (needle)
						return (needle);
					else
						return (_end);
				}

				size_type count(const key_type &k) const
				{
					//present
					if (this->find(k) != this->end())
						return (1);
					else
						return (0);
				}

				iterator lower_bound(const key_type &k)
				{
					iterator it(_root);
					while (_comp(it->first, k) == true && it != this->end())
						it++;
					return (it);
				}

				const_iterator lower_bound(const key_type &k) const
				{
					iterator it(_root);
					while (_comp(it->first, k) == true && it != this->end())
						it++;
					return (it);
				}

				iterator upper_bound(const key_type &k)
				{
					iterator it(_root);
					while (_comp(it->first, k) == false && it != this->end())
						it++;
					if (it->first == k && it != this->end())
						return (++it);
					else
						return (it);
				}

				const_iterator upper_bound(const key_type &k) const
				{
					iterator it(_root);
					while (_comp(it->first, k) == false && it != this->end())
						it++;
					if (it->first == k && it != this->end())
						return (++it);
					else
						return (it);
				}

				ft::pair<iterator, iterator> equal_range(const key_type &k)
				{
					return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
				}


				ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
				{
					return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
				}

				//Allocator

				allocator_type get_allocator() const
				{
					return this->_allocator;
				}


				void	_printNode(node *toprint)
				{	
					std::cout << "Parent (" << toprint->parent->pr.first << ") <--";
					std::cout << "Node id = ";
					if (toprint == _end)
						std::cout << "(END)" << std::endl;
					else
						std::cout << "(" << toprint->pr.first << ")" << std::endl;

					std::cout << "-Left : ";
					if (toprint->left)
						std::cout << "(" << toprint->left->pr.first << ")" << std::endl;
					else
						std::cout << "(NULL)" << std::endl;

					std::cout << "-Right : "; 
					if(toprint->right)
					{
						if (toprint->right == _end)
							std::cout << "(END)" << std::endl;
						else
							std::cout << "(" << toprint->right->pr.first << ")" << std::endl;
					}
					else
						std::cout << "(NULL)" << std::endl;
				}

				void _printNode(iterator it)
				{
					ft::node<value_type> node = *(it._ptr);

					std::cout << "Parent : ";
					if (node.parent)
						std::cout << "(" << node.parent->pr.first << ")  " ;
					else
						std::cout << "(NULL)  " ;

					if (node.pr == _end->pr)
						std::cout << " <--- Node = (END)" << std::endl;
					else	
						std::cout << " <--- Node id = (" << node.pr.first << ")" << std::endl;
					std::cout << "-Left : ";
					if (node.left)
						std::cout << "(" << node.left->pr.first << ")";
					else
						std::cout << "(NULL)";
					std::cout << "     | -Right : ";
					if(node.right)
						std::cout << "(" << node.right->pr.first << ")" << std::endl;
					else
						std::cout << "(NULL)" << std::endl;
					std::cout << std::endl;
				}



			private :

				void	_deletePostOrder(node *root)
				{
/*					if (root == _root)
						std::cout << "clear() DELETES \"_root\"" << std::endl;
					if (root == _end)
						std::cout << "clear() DELETES \"_end\"" << std::endl;
*/					if (root == NULL)
						return;
					this->_deletePostOrder(root->left);
					this->_deletePostOrder(root->right);
					_freeNode(root);
				}


				void	_updatePosition(void)
				{
//					std::cout << "Update postion : START" << std::endl;
					node *max_child;
					//l'arbre est vide et/ou Root a ete supprime
					if (_root == NULL)
					{
						_root = _newNode();
						_root->is_root = true;
						max_child = _root;
					}
					else
						max_child = _findMaxChild(_root);
					//suite a un clear par exemple ?
					if (_end == NULL)
						_end = _newNode();

					_preRoot->right = _root;
					_preRoot->left = _root;
					_root->parent = _preRoot;

					_end->parent = max_child;
					_end->is_end = true;
					max_child->right = _end;
//					std::cout << "Update postion : END " << std::endl;
				}

				node* _findMinChild(node *subtree) const
				{
					if (subtree == NULL)
						return (NULL);
					node *current = subtree;
					while (current->left)
						current = current->left;
					return current;
				}

				node* _findMaxChild(node *subtree) const
				{
					if (subtree == NULL)
						return (NULL);
					node *current = subtree;
					while (current->right && current->right != _end)
						current = current->right;
//					std::cout << "MaxChild = Node(" << current->pr.first << ")" << std::endl;
					return current;
				}


				node* _myErase(node *subroot, const value_type &val)
				{
					if (subroot == NULL)
						return (NULL);

					key_type new_key = val.first;
					key_type subroot_key = subroot->pr.first;


					if (_comp(new_key, subroot_key) == true)
						subroot->left = this->_myErase(subroot->left, val);
					else if (_comp(new_key, subroot_key) == false)
						subroot->right = this->_myErase(subroot->right, val); 
					else
					{
						node *tmp = NULL;
						//Un fils ou aucun fils
						if (subroot->right == NULL || subroot->left == NULL)
						{
							tmp = subroot;
							//leaf case
							if (subroot->right == NULL && subroot->left == NULL)
								subroot = NULL;
							else
								subroot = subroot->right ? subroot->right : subroot->left;
							_freeNode(tmp); // old subroot
						}
						//deux fils
						else
						{

							node *successor = this->_findMinChild(subroot->right);

							node *tmp = _newNode(successor->pr);
							//Etape 1
							tmp->parent = subroot->parent;
							tmp->left = subroot->left;
							tmp->right = subroot->right;

							//Etape 2
							tmp->right->parent = tmp;
							tmp->left->parent = tmp;
							if (tmp->parent->right == subroot)
								tmp->parent->right = tmp;
							else if (tmp->parent->left == subroot)
								tmp->parent->left = tmp;
							else
							{
								std::cout << "ERROR in ERASE ligne 645" << std::endl;
								exit(5);
							}
							//Etapte 3 kill subroot
							_freeNode(subroot);

							//Etape 4 fait pointer subroot sur le remplacant
							subroot = tmp;

							//kill my child
							subroot = this->_myErase(subroot->right, subroot->pr);
						}
					}
					//Si je n'existe pas je peux pas me balancer
					if (subroot == NULL)
						return (subroot);
					//calcul sa nouvelle hauteur
					subroot->height = _getHeight(subroot);
					int balance = _isBalanced(subroot);

					if (balance < -1 || balance > 1)
						subroot = this->_doEraseRotation(subroot, balance);
					return (subroot);
				}

				node* _doEraseRotation(node* node, int balance)
				{
					if (balance > 1 && _isBalanced(node->left) >= 0)
						return this->_rightRotate(node);
					if (balance > 1 && _isBalanced(node->left) < 0)
					{
						node->left = this->_leftRotate(node->left);
						return this->_rightRotate(node);
					}
					if (balance < -1 &&	_isBalanced(node->right) <= 0)
						return this->_leftRotate(node);
					if (balance < -1 &&	_isBalanced(node->right) > 0)
					{
						node->right = this->_rightRotate(node->right);
						return this->_leftRotate(node);
					}
					else
						std::cout << RED << "There is a problem in ERASE_DO_ROTATION line 690" << RESET  << std::endl;
					return (NULL);
				}


				node* _myInsert(node *subroot, node *parent, const value_type &val)
				{

					// side : 0 = root | 1 = left | 2 = right	
					//base case one
					//root case 
					//if (root->init = false && subroot == _root)
					//		return (_newNode
					if (subroot == NULL || subroot == _end) // || (_root->init == false && subroot == _root)
						return (_newNode(parent, val));
					//base case two
					//if (new_key == subroot_key)
					//return (subroot);
					key_type new_key = val.first;
					key_type subroot_key = subroot->pr.first;
					parent = subroot;
					// new_key < subroot_key. Insertion gauche
					if (_comp(new_key, subroot_key) == true)
						subroot->left = this->_myInsert(subroot->left, parent, val);
					// new_key > subroot_key .  Insertion droite
					else if (_comp(new_key, subroot_key) == false)
						subroot->right = this->_myInsert(subroot->right, parent, val); 
					//Key == cur_key. Deja present . Pas d'insertion
					else
						return (subroot);

					//calculer la nouvelle height
					subroot->height = _getHeight(subroot);

					//balancer l'arbre apres l'insertion
					int balance = _isBalanced(subroot);
					//std::cout << "Node ("<< subroot->pr.first<< ") height = " << subroot->height  << " |  balance =  " <<  balance << std::endl;

					//Tree is NOT balanced
					//rotate for balancing and return new subroot
					if (balance < -1 || balance > 1)
					{
				//		std::cout << RED << "_doRotation : node (" << subroot->pr.first <<") : " ;
						//subroot = this->_doRotation(subroot, val, balance);
						subroot = this->_doRotation(subroot, val, balance);
				//		std::cout << "Rotation : END" <<  RESET << std::endl;
					}
				//	std::cout << GREEN << "LEVEL Node [" << subroot->pr.first << "] | My parent is (" << subroot->parent->pr.first << ")" << RESET << std::endl;
					return (subroot); // Subtree is balanced return unchanged subroot
				}

				node* _doRotation(node *node, const value_type &val, int scenario)
				{
					if (node == NULL)
					{
						std::cout << "There is a problem at the START OF  DO_ROTATION" << std::endl;
						return (NULL);
					}
					key_type new_key = val.first;

					//left branch is heavy
					if (scenario > 1)
					{
				//		std::cout << "Left Heavy : ";
						key_type node_left_key = node->left->pr.first;
						//if new_key < node->left->key
						//left left case
						if (_comp(new_key, node_left_key) == true)
						{
				//			std::cout << "LL case" << std::endl;
							return (_rightRotate(node));
						}
						//left right case
						else
						{
				//			std::cout << "LR case" << std::endl;
							node->left = _leftRotate(node->left);
							return (_rightRotate(node));
						}
					}
					//Right branch is heavy
					else if (scenario < -1)
					{
				//		std::cout << "Right Heavy : ";
						key_type node_right_key = node->right->pr.first;
						if (_comp(new_key, node_right_key) == false)
						{
				//			std::cout << "RR case" << std::endl;
							return (_leftRotate(node));
						}
						else
						{
				//			std::cout << "RL case" << std::endl;
							node->right = _rightRotate(node->right);
							return (_leftRotate(node));
						}
					}
					else
					{
				//		std::cout << "There is a problem at the END OF  DO_ROTATION scenario = " << scenario << std::endl;
					}
					return (NULL);
				}

				int _isBalanced(node *node)
				{
					return (_getHeight(node->left) - _getHeight(node->right));
				}


				size_t _getHeight(node *node)
				{
					if (node == NULL || node == _end)
						return (0);
					size_t right = _getHeight(node->right);
					size_t left = _getHeight(node->left);

					return ((right > left ? right : left) + 1);
				}

				node* _rightRotate(node *y)
				{
					node	*x = y->left;
					node	*z = x->right;
					/*
					   node	*tmp = x->parent;
					   x->parent = y->parent;
					   y->parent = tmp->parent;
					   */				
					x->parent = y->parent;
					y->parent = x;
					x->right = y;
					y->left = z;
					//commenter = infinite loop. Uncomment = segF
					if (z)
						z->parent = y;
					return (x);
				}

				node* _leftRotate(node *y)
				{
					//e = y->parent
					//y = b
					//x = d
					node	*x = y->right;
					node	*z = x->left;

					x->parent = y->parent;
					y->parent = x;
					x->left = y;
					y->right = z;
					if (z)
						z->parent = y;
					return (x);
				}

				//Mes fonctions utils perso
				node*	_findVal(node* node, const value_type &val) const 
				{
					if (node == NULL || node == _end)
					{
				//		if (node == NULL)
				//			std::cout << "_findVal : Node = NULL" << std::endl;
				//		else
				//			std::cout << "_findVal : Node = _end" << std::endl;
						return (NULL);
					}
					key_type new_key = val.first;
					key_type node_key = node->pr.first;

					if (node_key == new_key)
					{
						//	std::cout << "_findVal : Node found!" << std::endl;
						return (node);
					}
					else if (_comp(new_key, node_key) == true)
						return (this->_findVal(node->left, val));
					else
						return (this->_findVal(node->right, val));
				}

				node* _initTree(node *root, const value_type &val)
				{

				//	std::cout << "ROOOOOOOT_ROOOOOOOT : _iniTree : Inserting _root value : " << val.first << " ROOOOOOOOOOT_ROOOOOOOOOOT" << std::endl;
					node *new_node = _allocator_node.allocate(1);
					_allocator_node.construct(new_node, node(val));

					new_node->is_root = true;
					new_node->is_init = true;
					new_node->parent = root->parent;
					new_node->right = root->right;
					new_node->left = root->left;
					_freeNode(root);
					return (new_node);
				}

				node*	_newNode(node *parent, const value_type & val)
				{
					node *new_node = _allocator_node.allocate(1);
					_allocator_node.construct(new_node, node(val));
					new_node->parent = parent;

				//	std::cout << GREEN << "My name is Node [" << new_node->pr.first << "] | My parent is (" << new_node->parent->pr.first << ")" << RESET << std::endl;
					return (new_node);
				}

				node*	_newNode(const value_type & val)
				{
					node *new_node = _allocator_node.allocate(1);

					_allocator_node.construct(new_node, node(val));
					return (new_node);
				}

				node* _newNode()
				{
					node *new_node = _allocator_node.allocate(1);
					_allocator_node.construct(new_node, node());
					return (new_node);
				}

				void	_freeNode(node *subtree) 
				{
					if (subtree)
					{
						_allocator_node.destroy(subtree);
						_allocator_node.deallocate(subtree, 1);
					}
				}
				void	_printInorder(node *root)
				{
					if (root == NULL)
						return;
					if (root == _end)
					{
						std::cout << " _end reached " << std::endl;
						return;
					}
					if (root->left)
						_printInorder(root->left);
					std::cout << " |"<< root->pr.first << "| ";
					if (root->right)
						_printInorder(root->right);
				}

				void	_printTest(node *root)
				{
					if (root == NULL)
					{
						std::cout << " NULL\n";
						return;
					}
					else if (root->pr== _end->pr)
					{
						std::cout << "(END_NODE)" << std::endl;
						return;
					}
					//	if (root == _root && root->is_init)
					std::cout << "Node (" << root->pr.first << ")" << std::endl;
					std::cout << "-Parent : ";
					if (root->parent == _preRoot)
						std::cout << " (PREROOT_NODE) " << std::endl;
					else
						std::cout << root->parent->pr.first << std::endl;
					if (root->left)
						std::cout << "-Left (" << root->left->pr.first << ")" << std::endl;
					if (root->right && root->right != _end)
						std::cout << "-Right (" << root->right->pr.first << ")" << std::endl;
					//std::cout << "left branch : ";
					_printTest(root->left);
					//std::cout << "right branch : ";
					_printTest(root->right);
					return;
				}



				//fin de class map
		};
	template< class Key, class T, class Compare, class Alloc >
		bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) 
		{
			if (lhs.size() != rhs.size()) {
				return false;
			}
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}

	template< class Key, class T, class Compare, class Alloc >
		bool operator!=(ft::map<Key,T,Compare,Alloc> const& lhs, ft::map<Key,T,Compare,Alloc> const& rhs)
		{
			return !(lhs == rhs);
		}

	template< class Key, class T, class Compare, class Alloc >
		bool operator<(ft::map<Key,T,Compare,Alloc> const& lhs, ft::map<Key,T,Compare,Alloc> const& rhs)
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

	template< class Key, class T, class Compare, class Alloc >
		bool operator<=(ft::map<Key,T,Compare,Alloc> const& lhs, ft::map<Key,T,Compare,Alloc> const& rhs)
		{
			return !(rhs < lhs);
		}

	template< class Key, class T, class Compare, class Alloc >
		bool operator>(ft::map<Key,T,Compare,Alloc> const& lhs, ft::map<Key,T,Compare,Alloc> const& rhs)
		{
			return rhs < lhs;
		}

	template< class Key, class T, class Compare, class Alloc >
		bool operator>=(ft::map<Key,T,Compare,Alloc> const& lhs, ft::map<Key,T,Compare,Alloc> const& rhs)
		{
			return !(lhs < rhs);
		}

	// --> Swap of vectors

	template< class Key, class T, class Compare, class Alloc >
		void swap(ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs)
		{
			lhs.swap(rhs);
			return;
		}
	//end of ft namespace
};
#endif
