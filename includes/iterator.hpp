#ifndef ITERATOR_HPP
#define ITERATOR_HPP

// std::ptrdiff_t
#include <cstddef> 

namespace ft
{
	struct input_tag{};
	struct output_tag{};
	struct forward_tag : public input_tag {};
	struct bidirectional_tag : public forward_tag {};
	struct random_access_tag : public bidirectional_tag {};

	template	<typename Category, typename T,
				typename Distance = std::ptrdiff_t,
				typename Pointer = T*,
				typename Reference = T&
					>
					struct iterator
					{
						typedef T         value_type;
						typedef Distance  difference_type;
						typedef Pointer   pointer;
						typedef Reference reference;
						typedef Category  iterator_category;
					};

	template <typename Iter>
		struct iterator_traits
		{
			typedef typename Iter::difference_type	difference_type;
			typedef typename Iter::value_type		value_type;
			typedef typename Iter::pointer			pointer;
			typedef typename Iter::iterator_category	iterator_category;
		};

	template <typename T>
		struct iterator_traits<T*>
		{
			typedef std::ptrdiff_t					difference_type;
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef ft::random_access_tag iterator_category;
		};

	template <typename T>
		struct iterator_traits<const T*>
		{
			typedef std::ptrdiff_t					difference_type;
			typedef T								value_type;
			typedef const T*						pointer;
			typedef const T&						reference;
			typedef ft::random_access_tag	iterator_category;
		};
}
#endif
