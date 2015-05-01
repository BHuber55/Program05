#if !defined (PQAVL_H)
#define PQAVL_H

#include "AVLTree.h"


/*
	if allow duplicates is true, then that part works great, however it always allows duplicates,
	if allow duplicates is false, then the asending and decending part works great, however the part where it is suppose to allow it messes up at the end.
*/



/*
	PQAVL Overview:
		This classes is a priority queue using an AVL Tree. 
		This will allow duplicates, and will pull the greatest and least
		values from the tree depending on location in the tree.
*/



template < class T >
class PQAVL
{
	private: 
		AVLTree<T>* avl;

	public: 
		//Pre:  Must pass non-null values
		//Post: 
		PQAVL(bool min_or_max, int(*compare_item) (T* item_1, T* item_2));
		//Pre:  No pre-conditions.
		//Post: Deletes the AVL tree.
		~PQAVL();
		//Pre:  No pre-conditions.
		//Post: Returns true if the priority queue is empty, else will return false.
		bool pqIsEmpty();
		//Pre:  Must pass non-null value to be inserted.
		//Post: Adds the item to the priority queue AVL tree.
		void pqInsert(T* item);
		//Pre:  No pre-conditions.
		//Post: Will return the minimum or maxiumum value in the current AVL Tree.
		T* pqRemove();
};

template < class T >
PQAVL<T>::PQAVL(bool min_or_max, int(*compare_item) (T* item_1, T* item_2)) //constructor
{
	bool duplicates_on_left = true;
	bool allow_duplicates = true;

	//the actual constructor.
	avl = new AVLTree<T>(min_or_max, allow_duplicates, duplicates_on_left, compare_item);
}

template < class T >
PQAVL<T>::~PQAVL() //destructor
{
	//deletes the avl tree.
	delete avl;
}

template < class T >
bool PQAVL<T>::pqIsEmpty()
{
	//Delegates to AVLTree, if the tree is empty, will return true, else will return false.
	bool empty = avl->isEmpty();
	return empty;
}

template < class T >
void PQAVL<T>::pqInsert(T* item)
{
	//delegates to AVLTree to insert the item.
	avl->insert(item);
}

template < class T >
T* PQAVL<T>::pqRemove()
{
	//removes and returns the smallest or largest item in the priority queue
	//also delegates to AVLTree to remove an item.
	T* item = avl->remove();
	return item;
}

#endif