#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
	template <typename T1, typename T2>
		struct pair
		{
			public:
				typedef T1	first_type;
				typedef T2	second_type;

				first_type _first;
				second_type _second;

				pair() : _first(), _second() {}
				template<typename U, typename V>
					pair (const pair<U,V> &pr) : _first(pr._first), _second(pr._second) {}
				pair (const first_type &a, const second_type & b) : _first(a), _second(b) {}
				pair & operator=(const pair& pr)
				{
					if (pr == *this)
						return (*this);
					_first = pr._first;
					_second = pr._second;
					return (*this);
				}
				~pair() {}
		};

    template <typename T1, typename T2>
    bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return ((lhs._first == rhs._first) && (lhs._second == rhs._second));
    }

    template <typename T1, typename T2>
    bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return !(lhs == rhs);
    }
    
    template <typename T1, typename T2>
    bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return ((lhs._first < rhs._first) || (!(rhs._first < lhs._first) && lhs._second < rhs._second));
    }
    
    template <typename T1, typename T2>
    bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return rhs < lhs;
    }

    template <typename T1, typename T2>
    bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return !(lhs > rhs);
    }

    template <typename T1, typename T2>
    bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return !(lhs < rhs);
    }
	
	// MAKE PAIR
	template <typename T1, typename T2>
		pair<T1, T2> make_pair(T1 x, T2 y)
		{
			pair<T1, T2>	pr(x, y);
			return (pr);
		}
};
#endif
