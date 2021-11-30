#ifndef MAP_HPP
#define MAP_HPP
//std::less
#include <functional>
//std::cout  to print if necessary for correction
#include <iostream>
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
					: _root(_newNode()),_end(_newNode()), _preRoot(_newNode()),_comp(comp), _allocator(alloc), _size(0) 
				{
					// begin <-- root R-->end
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
				while (first != last)
				{
					this->insert(*first);
					++first;
				}

			}

				map (const map& x) : _root(_newNode()), _end(_newNode()), _preRoot(_newNode()), _comp(x._comp), _allocator(x._allocator), _size(x._size)
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
				_root = this->_metamorph(_root, _root, x._root);
				_updatePosition();
			}

				map & operator=(const map& x)
				{
					map tmp(x);
					this->swap(tmp);
					return *this;
				}


				virtual ~map()
				{
					//detruit tout sauf _preRoot et _end
					this->_deletePostOrder(_root);
					_freeNode(_preRoot);
					_freeNode(_end);
				}

				//Iterator most left child
				iterator begin()
				{
					if (this->empty() == false)
						return (this->_findMinChild(_root));
					else
						return (_end);
				}

				const_iterator begin() const
				{
					if (this->empty() == false)
						return (this->_findMinChild(_root));
					else
						return (_end);
				}

				// empty right child of most right node
				iterator end()
				{
					return (this->_end);
				}
				const_iterator end() const
				{
					return (this->_end);
				}

				//end()-->parent ou  
				reverse_iterator rbegin()
				{
					return (reverse_iterator(this->end()));
				}
				const_reverse_iterator rbegin() const
				{
					return (const_reverse_iterator(this->end()));
				}

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
					value_type val = ft::make_pair(k, mapped_type());
					iterator it = this->insert(val).first;
					return (it->second);
				}

				//Modifiers
				pair<iterator, bool>	insert(const value_type &val) 
				{
					//Cherche si la key est deja presente
					node *needle = this->_findVal(_root, val);

					//Noeud absent. On l'insere
					if (needle == NULL)
					{	
						//Insere ET balance
						//deal with root case. Only for the first insertion
						if (_root->is_init == false && _root->left == NULL && (_root->right == NULL || _root->right == _end))
							_root = _initTree(_root, val);
						else
							_root = this->_myInsert(_root, _root, val);
						//update les iterator de pos
						this->_updatePosition();
						this->_size += 1;
						iterator it(_findVal(_root, val));

						return (ft::make_pair<iterator, bool> (it, true));
					}
					else
					{
						iterator it(needle);
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
							++first;
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
						if (_size > 0)
							_size -= 1;
						return (1);
					}
					else
						return (0);
				}

				void erase (iterator first, iterator second)
				{
						key_type k_second = second->first;
						while (first != second)
						{
							iterator next = first;
							next++;
							key_type k_next = next->first;

							this->erase(first);
							first = this->find(k_next);
							second = this->find(k_second);
						}
						return ;
				}

				void swap(map & x)
				{


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
				}

				void clear() 
				{
					this->_deletePostOrder(_root);
					_root = NULL;
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
						return (this->end());
				}

				const_iterator find (const key_type &k) const
				{
					node *needle = this->_findVal(_root, ft::make_pair(k, mapped_type()));
					if (needle)
						return (needle);
					else
						return (this->end());
				}

				size_type count(const key_type &k) const
				{
					//present
					if (this->find(k) != this->end())
						return (1);
					else
						return (0);
				}

				iterator lower_bound(const key_type& k)
				{   
					iterator it = begin();
					iterator ite = end();
					while (it != ite)
					{
						if (it->first == k || _comp(it->first, k) == false)
							return it;
						it++;
					}
					return end();
				}

				const_iterator lower_bound(const key_type& k) const
				{
					const_iterator it = begin();
					const_iterator ite = end();
					while (it != ite)
					{
						if (it->first == k || _comp(it->first, k) == false)
							return const_iterator(it);
						it++;
					}
					return const_iterator(end());
				}

				iterator upper_bound(const key_type& k)
				{   
					iterator it = begin();
					iterator ite = end();
					while (it != ite)
					{
						if (it->first != k && _comp(it->first, k) == false)
							return it;
						it++;
					}
					return end();
				}

				const_iterator upper_bound(const key_type& k) const
				{
					const_iterator it = begin();
					const_iterator ite = end();
					while (it != ite)
					{
						if (it->first != k && _comp(it->first, k) == false)
							return const_iterator(it);
						it++;
					}
					return const_iterator(end());
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

				private :

				node* _metamorph(node *parent, node *root, node *src)
				{
					if (src == NULL)
						return (NULL);
					else if (src->is_end == true)
						return (_end);
					//creer le noeud
					node *new_node;
					if (root == _root && _root->is_init == false)
					{
						new_node =_initTree(root, src->pr);
					}
					else
						new_node = _newNode(parent, src->pr);
					new_node->left = _metamorph(new_node, new_node->left, src->left);
					new_node->right = _metamorph(new_node, new_node->right, src->right);
					return (new_node);
				}

				void	_deletePostOrder(node *root)
				{
					if (root == NULL || root == _end)
						return;
					this->_deletePostOrder(root->left);
					this->_deletePostOrder(root->right);
					_freeNode(root);
				}

				void	_updatePosition(void)
				{
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
					if (_end == NULL)
						_end = _newNode();

					_preRoot->right = _root;
					_preRoot->left = _root;
					_root->parent = _preRoot;

					_end->parent = max_child;
					_end->is_end = true;
					max_child->right = _end;
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
					return current;
				}


				node* _myErase(node *subroot, const value_type &val)
				{
					if (subroot == NULL || subroot == _preRoot || subroot == _end)
						return (NULL);

					key_type new_key = val.first;
					key_type subroot_key = subroot->pr.first;
					if (new_key == subroot_key)
					{
						node *tmp = NULL;
						//Un fils ou aucun fils
						if ((subroot->right == NULL || subroot->right == _end) || subroot->left == NULL)
						{
							tmp = subroot;
							//leaf case
							if ((subroot->right == NULL && subroot->left == NULL) || (subroot->left == NULL && subroot->right == _end))
							{
								subroot = NULL;
							}
							else
							{
								if (subroot->right == NULL || subroot->right->pr == _end->pr)
									subroot = subroot->left;
								else
									subroot = subroot->right;
								subroot->parent = tmp->parent;
							}
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
							else 
								tmp->parent->left = tmp;
							//Etapte 3 kill subroot
							_freeNode(subroot);

							//Etape 4 fait pointer subroot sur le remplacant
							subroot = tmp;

							//kill my child
							subroot->right = this->_myErase(subroot->right, subroot->pr);
						}
					}
					else if (_comp(new_key, subroot_key) == true)
						subroot->left = this->_myErase(subroot->left, val);
					else
						subroot->right = this->_myErase(subroot->right, val); 

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
					{
						return this->_rightRotate(node);
					}
					if (balance > 1 && _isBalanced(node->left) < 0)
					{
						node->left = this->_leftRotate(node->left);
						return this->_rightRotate(node);
					}
					if (balance < -1 &&	_isBalanced(node->right) <= 0)
					{
						return this->_leftRotate(node);

					}
					if (balance < -1 &&	_isBalanced(node->right) > 0)
					{
						node->right = this->_rightRotate(node->right);
						return this->_leftRotate(node);
					}
					return (NULL);
				}


				node* _myInsert(node *subroot, node *parent, const value_type &val)
				{

					if (subroot == NULL || subroot == _end) 
					{
						node *ret = _newNode(parent, val);
						return (ret);
					}

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
					subroot->height = _max(_getHeight(subroot->right), _getHeight(subroot->left)) + 1;

					//balancer l'arbre apres l'insertion
					int balance = _isBalanced(subroot);

					//Tree is NOT balanced
					if (balance < -1 || balance > 1)
						subroot = this->_doRotation(subroot, val, balance);
					return (subroot); // Subtree is balanced return unchanged subroot
				}

				node* _doRotation(node *node, const value_type &val, int scenario)
				{
					if (node == NULL)
						return (NULL);
					key_type new_key = val.first;

					//left branch is heavy
					if (scenario > 1)
					{
						key_type node_left_key = node->left->pr.first;
						//left left case
						if (_comp(new_key, node_left_key) == true)
							return (_rightRotate(node));
						//left right case
						else
						{
							node->left = _leftRotate(node->left);
							return (_rightRotate(node));
						}
					}
					//Right branch is heavy
					else 
					{
						key_type node_right_key = node->right->pr.first;
						if (_comp(new_key, node_right_key) == false)
							return (_leftRotate(node));
						else
						{
							node->right = _rightRotate(node->right);
							return (_leftRotate(node));
						}
					}
				}

				int _isBalanced(node *node)
				{
					if (node == NULL || node == _end)
						return (0);
					return (_getHeight(node->left) - _getHeight(node->right));
				}

				size_t _max(int a, int b)
				{
					return ((a > b) ? a : b);
				}

				size_t _getHeight(node *node)
				{
					if (node == NULL || node == _end)
						return (0);
					return (node->height);
				}

				node* _rightRotate(node *y)
				{
					node	*x = y->left;
					node	*z = x->right;
					x->parent = y->parent;
					y->parent = x;
					x->right = y;
					y->left = z;

					if (z)
						z->parent = y;

					y->height = _max(_getHeight(y->left),
							_getHeight(y->right)) + 1;
					x->height = _max(_getHeight(x->left),
							_getHeight(x->right)) + 1;
					return (x);
				}

				node* _leftRotate(node *y)
				{
					node	*x = y->right;
					node	*z = x->left;

					x->parent = y->parent;
					y->parent = x;
					x->left = y;
					y->right = z;
					if (z)
						z->parent = y;

					y->height = _max(_getHeight(y->left),
							_getHeight(y->right)) + 1;
					x->height = _max(_getHeight(x->left),
							_getHeight(x->right)) + 1;

					return (x);
				}

				node*	_findVal(node* node, const value_type &val) const 
				{
					if (node == NULL || node == _end || _root->is_init == false)
						return (NULL);
					key_type new_key = val.first;
					key_type node_key = node->pr.first;

					if (node_key == new_key)
						return (node);
					else if (_comp(new_key, node_key) == true)
						return (this->_findVal(node->left, val));
					else
						return (this->_findVal(node->right, val));
				}

				node* _initTree(node *root, const value_type &val)
				{

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

				//Fonction d'impression si besoin durant la correction
/*
			void	_printFromRoot(node *root)
				{
					if (root == NULL)
						return;
					else if (root->pr == _end->pr)
					{
						std::cout << "Node id [END_NODE]" << std::endl;
						return;
					}
					//	if (root == _root && root->is_init)
					std::cout << "\n**Node id [";
					_printPair(root->pr);
					std::cout << "]**" << std::endl;

					std::cout << "-Parent : ";
					if (root->parent == _preRoot)
						std::cout << " (PREROOT_NODE) ";
					else
						_printPair(root->parent->pr);
					std::cout << std::endl;

					std::cout << "-Left : ";
					if (root->left)
						_printPair(root->left->pr);
					else
						std::cout << "(NULL)";
					std::cout << std::endl;

					std::cout << "**-Right : "; 
					if (root->right && root->right->pr != _end->pr)
						_printPair(root->right->pr);
					else if (root->right == NULL)
						std::cout << "(NULL)";
					else
						std::cout << "(END_NODE)";
					std::cout << "**"<< std::endl;
					
					if (root->left)
					{
						_printFromRoot(root->left);
					}
					if (root->right)
					{
						_printFromRoot(root->right);
					}
					return;
				}

				void _printPos()
				{
					std::cout << "\n\t[[___**POSITION**__]]" << std::endl;
					std::cout << "_preRoot->left : ";
					if (_preRoot->left)
						_printPair(_preRoot->left->pr);
					else
						std::cout << "NULL";
	
					
					std::cout << "_preRoot->right : ";
					if (_preRoot->right)
						_printPair(_preRoot->right->pr);
					else
						std::cout << "NULL";

					
					std::cout << "\nRoot->pr: ";
					if (_root)
						_printPair(_root->pr);
					else
						std::cout << "NULL";

					std::cout << "\nRoot->left : ";
					if (_root->left)
						_printPair(_root->left->pr);
					else
						std::cout << "NULL";

					std::cout << "\nRoot->right : ";
					if (_root->right)
						_printPair(_root->right->pr);
					else
						std::cout << "NULL";

					std::cout << "\n_end parent: ";
					if (_end->parent)
						_printPair(_end->parent->pr);
					else
						std::cout << "NULL" << std::endl;
					std::cout << "\n\t[[___**POSITION----------END**__]]" << std::endl;
				}



				void _printPair(value_type &pr)
				{
					std::cout << "(" << pr.first << ")-(" << pr.second << ")";
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
				*/
					//Fin de class map
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
