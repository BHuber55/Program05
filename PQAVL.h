#if !defined (PQAVL_H)
#define PQAVL_H

#include "AVLTree.h"


/*
	PQAVL Overview:
		This classes is a priority queue. 
		This will allow duplicates, and will pull the greatest and least
		values from the tree depending on location.


	Function is O(logn) for insert and remove function.
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
		//Post: Deletes the priority queue.
		~PQAVL();
		//Pre:  No pre-conditions.
		//Post: Returns true if the priority queue is empty, else will return false.
		bool pqIsEmpty();
		//Pre:  Must pass non-null value to be inserted.
		//Post: Adds the item to the priority queue. O(logn) time complexity.
		void pqInsert(T* item);
		//Pre:  No pre-conditions.
		//Post: Will return the minimum or maxiumum value. O(logn) time complexity.
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