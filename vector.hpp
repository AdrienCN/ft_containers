#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace ft
{
	class <typename T> vector 
	{
		public:
			//Constructor
				//Default
						
				//fill
				
				//range
				
				//copy
			
			//operator=	
				vector& operator=(const & vector x);
			//Destructor
				~vector();
			

			//iterator
				begin;
				end;
				rbegin;
				rend;
			
			//Capacity
				size;
				max_size;
				resize;
				capacity;
				empty;
				reserve;
			//Element access
				operator[];
				at;
				front;
				back;
			
			//Modifiers
				assign;
				push_back;
				pop_back;
				insert;
				erase;
				swap;
				clear;
			//Allocator
				get_allocator;

		private:

		protected:
	};
	relational operators(){};
	swap(){};
};
#endif
