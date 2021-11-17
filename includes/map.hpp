#ifndef MAP_HPP
#define MAP_HPP

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
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
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
				typedef node<value_type>								node;

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
							return _comp(x.first, y.first);
						}
				};

			protected:
				//Attribut
				node*		_root; // root node
				node*		_end; //EMPTY right child of the most right node ---->  end
				node*		_preRoot; // PREroot node ---> rend
				key_compare		_comp;
				allocator_type	_allocator;
				size_type		_size;


			public:

				//Constructor
				explicit map (const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type())
					: _root(NULL), _comp(comp), _allocator(alloc), _size(0) 
				{
					_root = _new_node();
					_preRoot = _new_node();
					_end = _new_node();

					// begin <-- root R-->end
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
					node *needle = _find_node_key(_root);
					if (needle)
						return (needle->_pr.second);
					else
					{
						node *new_node = create_node(value_type (k, mapped_type()));
						this->insert(new_node);
						return mapped_type();
					}
				}

					//Modifiers
					void insert(const iterator it, node *node) 
					{
						(void)it;
						(void)node;
					}
					void insert(node *node) 
					{
						(void)node;
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
					//Mes fonctions utils perso
					node*	_find_node_by_key() 
					{
						return (NULL);
					}
					node*	_new_node()
					{
						return (NULL);
					}
					node*	_new_node(const value_type & x)
					{
						(void)x;
						return (NULL);
					}
					void	_free_node(node *subtree) 
					{
						(void)subtree;
					}

					//fin de class map
		};
	//end of ft namespace
};
#endif
