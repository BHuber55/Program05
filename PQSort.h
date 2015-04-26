#include 

template < class T >
class PQSort
{
	private:
		//sorts the array using PQAVL
		static void _pqSort(T** items, int num_items, bool min_or_max, int(*compare_item) (T* one, T* two));
	public:
		//public method to create and return a new, sorted array in case the original unsorted array must be kept, calls the private method below
		static T** pqSort(T** items, int num_items, bool min_or_max, int(*compare_item) (T* one, T* two));
};
template < class T >
static T** PQSort<T>::pqSort(T** items, int num_items, bool min_or_max, int(*compare_item) (T* one, T* two))
{
	T** sorted = new = T*[num_items];

	for (int i = 0; i < num_items; i++)
	{
		sorted[i] = items[i];
	}

	_pqSort(sorted, num_items, min_or_max, compare_items);

	return sorted;
}

template < class T >
static void PQSort<T>::_pqSort(T** items, int num_items, bool min_or_max, int(*compare_item) (T* one, T* two))
{
	int count = 0;

	PQAVL<T>* pqavl = new PQAVL<T>(min_or_max, compare_items);
	
	for (int i = 0; i < num_items; i++)
	{
		pqavl->insert(items[i]);
	}

	while (!pqavl->isEmpty())
	{
		items[count] = pqavl->remove();
		count++;
	}

}