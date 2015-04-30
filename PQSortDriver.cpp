#include "PQSort.h"
#include "PQAVL.h"
#include "AVLTree.h"

#include "ListArray.h"
using CSC2110::ListArray;
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
		CD* cd = cds[i];
		cout << cd->getKey() << ", ";
	}
}


int main()
{
	int compare_item = &CD::compare_item;
	bool min_or_max = true;

	ListArray<CD>* cds = CD::readCDs("cds.txt");
	int num_items = cds->size();
	cout << num_items << endl;

	DisplayAll(cds, num_items);
	
	cout << "^^ That is the OG" << endl;
	cout << "Hit enter to continue:";
	cin.get();
	cout << endl << endl;

	CD** sorted = PQSort<CD>::pqSort(cds, num_items, min_or_max, compare_item);

	DisplayAll(sorted, num_items);

	cout << "^^ That is ascending" << endl;
	cout << "Hit enter to continue:";
	cin.get();
	cout << endl << endl;

	DisplayAll(cds, num_items);

	cout << "^^ That is the OG" << endl;
	cout << "Hit enter to continue:";
	cin.get();
	cout << endl << endl;

	//bool is now false
	min_or_max = false;
	sorted = PQSort<CD>::pqSort(cds, num_items, min_or_max, compare_item);

	DisplayAll(sorted, num_items);

	cout << "^^ That is descending" << endl;
	cout << "Hit enter to continue:";
	cin.get();
	cout << endl << endl;

	//with min max being true this time.
	min_or_max = true;
	sorted = PQSort<CD>::pqSort(cds, num_items, min_or_max, compare_item);

	DisplayAll(sorted, num_items);

	cout << "^^ That is ascending with duplicates" << endl;


	delete[] cds;
	delete[] sorted;
	delete cds;

	return 0;
}