#if !defined (PQSORT_H)
#define PQSORT_H

#include "PQAVL.h"



//===========================functions are suppose to be static
#include <iostream>
using namespace std;



/*
PQSort overview:
Class that sorts items using a priority queue by means of an avl tree.
*/



template < class T >
class PQSort
{
private:
	//Pre:  Must pass non-null values, what is passed in should be a copy of the original array.
	//Post: modifies the sorted version of the array that was passed in.
	static void _pqSort(T** items, int num_items, bool min_or_max, int(*compare_item) (T* one, T* two));
public:
	//Pre:  Must pass non-null values, the array that is passed in will not be modifed.
	//Post: Returns a new sorted version of the array thatwas passed in, did not modify the original array passed in.
	static T** pqSort(T** items, int num_items, bool min_or_max, int(*compare_item) (T* one, T* two));
};
template < class T >
T** PQSort<T>::pqSort(T** items, int num_items, bool min_or_max, int(*compare_item) (T* one, T* two))
{
	//create a new array that is of size num_items.
	T** sorted = new T*[num_items];

	//copy the elements from the original array into the array we just created.
	for (int i = 0; i < num_items; i++)
	{
		sorted[i] = items[i];
	}

	//make a call to the private function.
	_pqSort(sorted, num_items, min_or_max, compare_item);

	//return the newly sorted array.
	return sorted;
}

template < class T >
void PQSort<T>::_pqSort(T** items, int num_items, bool min_or_max, int(*compare_items) (T* one, T* two))
{
	int count = 0;

	//create a new Priority queue avl tree.
	PQAVL<T>* pqavl = new PQAVL<T>(min_or_max, compare_items);

	//Inserting the items.
	for (int i = 0; i < num_items; i++)
	{
		pqavl->pqInsert(items[i]);
	}

	//then will remove the items and place them back into the array.
	while (!pqavl->pqIsEmpty())
	{
		items[count] = pqavl->pqRemove();
		count++;
	}

}

#endif