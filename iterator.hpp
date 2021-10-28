#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft
{
	struct input_iterator_tag{};
	struct output_iterator_tag{};
	struct forward_itrerator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	
	template	<typename Category, typename T,
				typename Distance = ptrdiff_t,
				typename Pointer = T*,
				typename Reference = &T
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
		typedef Iter::difference_type	difference_type;
		typedef Iter::value_type		value_type;
		typedef Iter::pointer			pointer;
		typedef Iter::iterator_category	iterator_category;
	}

	template <typename T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t		difference_type;
		typedef T					value_type;
		typedef T*					pointer;
		typedef T&					reference;
		typedef iterator_category	ft::random_access_iterator_tag;
	}

	template <typename T>
	struct iterator_trais<const T*>
	{
		typedef std::ptrdiff_t			difference_type;
		typedef T						value_type;
		typedef const T*				pointer;
		typedef const T&				reference;
		typedef iterator_category		ft::random_access_iterator_tag;
	}


};
#endif
