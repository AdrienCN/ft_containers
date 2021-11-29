#include "test_utils.hpp"
#include "common.hpp"
#include <map>

#define NAMESPACE ft

//# define NAMESPACE std


template <class Key, class T>
void	print(NAMESPACE::map<Key, T>& lst)
{
	for (typename NAMESPACE::map<Key, T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << it->first << " => " << it->second << '\n';
}

int main ()
{
	NAMESPACE::map<char,int> mymap;
	NAMESPACE::map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  mymap['b']=40;
  mymap['c']=60;
  mymap['d']=80;
  mymap['e']=100;

  itlow=mymap.lower_bound ('b');  // itlow points to b
  itup=mymap.upper_bound ('d');   // itup points to e (not d!)

  std::cout << "low : " << itlow->first << '\n';
  std::cout << "up : " << itup->first << '\n';

//  print(mymap);
  mymap.erase(itlow,itup);        // erases [itlow,itup)

  // print content:
  for (NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}

