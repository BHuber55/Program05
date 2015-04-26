#include "AVLTree.h"

template < class T >
class PQAVL
{
	private: 

		AVLTree<T>* avl;

	public:

		PQAVL(bool min_or_max, int(*compare_item) (T* item_1, T* item_2));	//constructor
		~PQAVL();															//destructor
		bool pqIsEmpty();
		void pqInsert(T* item);
		T* pqRemove();														//removes and returns the smallest or largest item in the priority queue
};

template < class T >
PQAVLT<T>::PQAVL(bool min_or_max, int(*compare_item) (T* item_1, T* item_2)) //constructor
{
	//I like local variables.
	bool allow_duplicates = true;
	bool duplicates_on_left = true;

	avl = new AVLTree<T>*(in_max, allow_duplicates, duplicates_on_left, comp_items, comp_keys);

}

template < class T >
PQAVLT<T>::~PQAVL() //destructor
{
	delete avl;
}

template < class T >
PQAVLT<T>::bool pqIsEmpty()
{
	return avl->isEmpty();
}

template < class T >
PQAVLT<T>::void pqInsert(T* item)
{
	avl->insert(item);
}

template < class T >
PQAVLT<T>::T* pqRemove() //removes and returns the smallest or largest item in the priority queue
{
	return avl->remove();
}