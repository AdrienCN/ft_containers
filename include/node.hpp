#ifndef NODE_HPP
#define NODE_HPP
namespace ft
{

	template <class value_type > 
		class node
		{
			public:
				//constructeur
				node (void) : parent(NULL), left(NULL), right(NULL), height(1), is_root(false), is_init(false), is_end(false) {}
				node (const value_type & pr) : parent(NULL), left(NULL), right(NULL), pr(pr), height(1), is_root(false), is_init(true), is_end(false) {}
				node (const node &src) : parent(src.parent), left(src.left), right(src.right), pr(src.pr), height(src.height), is_root(src.is_root), is_init(src.is_init), is_end(src.is_end) {};
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
				bool			is_root;
				bool			is_init;
				bool			is_end;

		//end of node class
		};
};
#endif
