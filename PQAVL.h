#include "AVLTree.h"

template < class T >
class PQAVL
{
	private: 

		AVLTree<T>* avl;

	public:
		//constructor && destructor
		PQAVL(bool min_or_max, int(*compare_item) (T* item_1, T* item_2));
		~PQAVL();
		
		bool pqIsEmpty();
		void pqInsert(T* item);
		
		//removes and returns the smallest or largest item in the priority queue
		T* pqRemove();
};

template < class T >
PQAVLT<T>::PQAVL(bool min_or_max, int(*compare_item) (T* item_1, T* item_2)) //constructor
{
	//I like local variables.
	bool allow_duplicates = true;
	bool duplicates_on_left = true;

	avl = new AVLTree<T>*(min_or_max, allow_duplicates, duplicates_on_left, comp_items, comp_keys);
}

template < class T >
PQAVLT<T>::~PQAVL() //destructor
{
	delete avl;
}

template < class T >
PQAVLT<T>::bool pqIsEmpty()
{
	bool empty = avl->isEmpty();
	return empty;
}

template < class T >
PQAVLT<T>::void pqInsert(T* item)
{
	avl->insert(item);
}

template < class T >
PQAVLT<T>::T* pqRemove() //removes and returns the smallest or largest item in the priority queue
{
	T* item = avl->remove();
	return item;
}