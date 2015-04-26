#if !defined (NULL)
#define NULL 0
#endif

#if !defined (LISTARRAYITERATOR_H)
#define LISTARRAYITERATOR_H

namespace CSC2110
{
template < class T >
class ListArrayIterator
{
   private:
      int index;
      int sz;
      T** items;

   public:
      ListArrayIterator(T** items, int size);
      ~ListArrayIterator();
      bool hasNext();
      T* next();
};

template < class T >
ListArrayIterator<T>::ListArrayIterator(T** itms, int size)
{
   items = new T*[size];
   for (int i = 0; i < size; i++)
   {
      items[i] = itms[i];  //snapshot of the data
   }

   index = 1;
   sz = size;
}

template < class T >
ListArrayIterator<T>::~ListArrayIterator()
{
   delete[] items;
}

template < class T >
bool ListArrayIterator<T>::hasNext()
{
   return (index <= sz);
}

template < class T >
T* ListArrayIterator<T>::next()
{
   T* item = NULL;

   if (hasNext())
   {
      item = items[index - 1];
      index++;
   }

   return item;
}
}

#endif
