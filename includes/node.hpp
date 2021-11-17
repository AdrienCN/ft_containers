#ifndef NODE_HPP
#define NODE_HPP
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
				node			*_parent;
				node			*_left;
				node			*_right;
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
};
#endif
