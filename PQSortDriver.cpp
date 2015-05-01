#include "PQSort.h"
#include "PQAVL.h"
#include "AVLTree.h"

#include "ListArray.h"
using CSC2110::ListArray;
#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;
#include "CD.h"
using CSC2110::CD;
#include "Text.h"
using CSC2110::String;

#include <iostream>
using namespace std;

//CD** could be the sorted or unsorted. It will work regardless. It just displays it.
void DisplayAll(CD** sorted, int num_items)
{
	for (int i = 0; i < num_items; i++)
	{
		CD* cd = sorted[i];
		String* title = cd->getKey();
		title->displayString();
		cout << ", ";
	}
}


int main()
{
	int count = 0;
	CD** sorted;
	bool min_or_max = true;
	bool allow_duplicates = false;

	//write the iterator
	ListArray<CD>* list = CD::readCDs("cds.txt");
	int num_items = list->size();

	CD** cds = new CD*[num_items];

	ListArrayIterator<CD>* iter = list->iterator();
	while (iter->hasNext())
	{
		CD* cd = iter->next();
		cds[count] = cd;
		count++;
	}
	delete iter;


	DisplayAll(cds, num_items);
	cout << endl << endl << "^^ That is the oringina list" << endl;
	cout << "Hit enter to continue:";
	cin.get();
	cout << endl << endl;

	sorted = PQSort<CD>::pqSort(cds, num_items, min_or_max, &CD::compare_items);

	DisplayAll(sorted, num_items);
	cout << endl << endl << "^^ That is ascending" << endl;
	cout << "Hit enter to continue:";
	cin.get();
	cout << endl << endl;

	//bool is now false
	min_or_max = false;
	sorted = PQSort<CD>::pqSort(cds, num_items, min_or_max, &CD::compare_items);

	DisplayAll(sorted, num_items);
	cout << endl << endl << "^^ That is descending" << endl;
	cout << "Hit enter to continue:";
	cin.get();
	cout << endl << endl;

	//with min max being true this time.
	min_or_max = true;
	allow_duplicates = true;
	sorted = PQSort<CD>::pqSort(cds, num_items, min_or_max, &CD::compare_items);

	DisplayAll(sorted, num_items);
	cout << endl << endl << "^^ That is ascending with duplicates" << endl;


	delete[] cds;
	delete[] sorted;
	delete cds;
	delete sorted;

	return 0;
}