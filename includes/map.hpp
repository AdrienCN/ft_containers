#ifndef MAP_HPP
#define MAP_HPP

namespace ft
{
	template <class value_type > 
		class node
		{
			public:
			//attribut
			struct node			*parent;
			struct node			*left;
			struct node			*right;
			value_type			_pr;
			//constructeur
			

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
		};


	template <class Key, class T, class Compare = ft::less<key>, class Alloc = std::allocator<pair<const Key, T> > >
		class map
		{
			public:

				//typedef de merde
				typedef Key		key_type;
				typedef T		mapped_type;
				typedef typename ft::pair<const key_type, mapped_type> value_type;
				typedef class compare
				{
					//compare code here
				}				value_compare;
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

				//Attribut
				t_node *_root;




				//fin de class map
		};
	//end of ft namespace
};
#endif
