#if !defined (LISTARRAY_H)
#define LISTARRAY_H

#include "ListArrayIterator.h"

namespace CSC2110
{
template < class T >
class ListArray
{
   private:
      int max_size;
      T** items;
      int sz;

      void arrayResize(int new_max_size);

   public:
      ListArray();
      ~ListArray();

      bool isEmpty();
      int size();
      void removeAll();

      //pre: index is between 1 and the number of items in the list inclusive
      //post: the item at the specified index is returned
      T* get(int index);

      //pre: index is between 1 and the number of items in the list + 1 inclusive
      //post: the item is added to the list at the specified index
      //      the indices of the items already in the list are adjusted
      //      true is returned if the add was successful, false otherwise
      void add(int index, T* item);


      //pre: index is between 1 and the number of items in the list inclusive
      //post: the item is removed from the specified index
      //      the indices of the items remaining in the list are adjusted
      //      true is returned if the remove was successful, false otherwise
      void remove(int index);

      ListArrayIterator<T>* iterator();
      T** toArray();

      //convenience methods
      void add(T* item);
      void set(int index, T* item);
};

template < class T >
ListArray<T>::ListArray()
{
   max_size = 10;
   items = new T*[max_size];
   sz = 0;
}

template < class T >
ListArray<T>::~ListArray()
{
   delete[] items;  //the items themselves are not deleted
}

template < class T >
bool ListArray<T>::isEmpty()
{
   return (sz == 0);
}

template < class T >
int ListArray<T>::size()
{
   return sz;
}

template < class T >  //1-based
T* ListArray<T>::get(int index)
{
   T* item = NULL;

   if (index >= 1 && index <= sz) 
   {  
      item = items[index - 1];
   }

   return item;
}

template < class T >
void ListArray<T>::add(T* item)
{
   add(sz + 1, item);  //add the item to the end of the array list
}

template < class T >
void ListArray<T>::add(int index, T* item)
{
   if (index < 1 || index > sz + 1)
   {
      return;
   }

   //need more room in the array list
   if (sz == max_size) 
   {
      arrayResize(2*max_size);
   }  
 
   for (int i = sz; i >= index; i--)
   { 
      items[i] = items[i - 1];
   }

   items[index - 1] = item;
   sz++;
}

template < class T >
void ListArray<T>::remove(int index)
{
   if (index < 1 || index > sz)
   {
      return;
   }

   for (int i = index; i < sz; i++)
   {
      items[i - 1] = items[i];
   }

   items[sz - 1] = NULL;
   sz--;

/*
   if (sz < max_size/2 - 1) //halve the size of the array, smallest size of max_size should be 2
   {
      arrayResize(max_size/2);
   }
*/
}

template < class T >
ListArrayIterator<T>* ListArray<T>::iterator()
{
   ListArrayIterator<T>* iter = new ListArrayIterator<T>(items, sz);
   return iter;
}

template < class T >
void ListArray<T>::set(int index, T* item)
{
   //could use other methods already written, but this is more efficient
   if (index >= 1 && index <= sz) 
   {
      items[index - 1] = item;  //overwrite contents at that location
   } 
}

template < class T >
void ListArray<T>::arrayResize(int new_max_size)
{
   max_size = new_max_size;
   T** temp = new T*[max_size];

   for (int i = 0; i < sz; i++)
   {
      temp[i] = items[i];
   }

   delete[] items;
   items = temp;
}

template < class T >
void ListArray<T>::removeAll()
{
   delete[] items;

   max_size = 10;
   items = new T*[max_size];
   sz = 0;
}

template < class T >
T** ListArray<T>::toArray()
{
   int num_items = size();
   T** to_array = new T*[num_items];
   for (int i = 0; i < num_items; i++)
   {
      to_array[i] = items[i];
   }
   return to_array;
}
}

#endif
