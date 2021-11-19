#ifndef NODE_HPP
#define NODE_HPP
namespace ft
{

	template <class value_type > 
		class node
		{
			public:
				//constructeur
				node (void) : parent(NULL), left(NULL), right(NULL), height(0) {}
				node (const value_type & pr) : parent(NULL), left(NULL), right(NULL), pr(pr), height(0) {}
				node (const node &src) : parent(src.parent), left(src.left), right(src.right), pr(src.pr), height(src.height) {};
				node & operator=(const node &src)
				{
					if (*this == src)
						return *this;
					parent = src.parent;
					left = src.left;
					right = src.right;
					pr = src.pr;
					height = src.height;
					return *this;
				}

				//**Attribut
				node			*parent;
				node			*left;
				node			*right;
				value_type			pr;
				size_t			height;

		//end of node class
		};
};
#endif
