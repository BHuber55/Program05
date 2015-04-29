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

int main()
{
	ListArray<CD>* cds = CD::readCDs("cds.txt");
	int num_items = cds->size();
	cout << num_items << endl;
	/*
	ListArrayIterator<CD>* iter = avl->iterator();
	int count = 0;
	while (iter->hasNext())
	{
		CD* cd = iter->next();
		cds[count] = cd;
		count++;

		cout << cd->getKey() << ", " << endl;
	}
	delete iter;
	*/

	//============================================================================================================================
	CD** cdArr = cds->toArray();

	for (int i = 0; i < cds->size(); i++) {
		CD* cd = cdArr[i];
		cd->getKey();
	}
	cout << "Before" << endl;
	cout << "Hit <Enter> to continue...";
	cin.get();
	cout << endl << endl;

	CD** sortedArr = PQSort<CD>::pqSort(cdArr, cds->size(), true, &CD::compare_item);

	for (int i = 0; i < cds->size(); i++) {
		CD* cd = sortedArr[i];
		cd->getKey();
	}
	cout << "After (Ascending)" << endl;
	cout << "Hit <Enter> to continue...";
	cin.get();
	cout << endl << endl;

	for (int i = 0; i < cds->size(); i++) {
		CD* cd = cdArr[i];
		cd->getKey();
	}
	cout << "OG" << endl;
	cout << "Hit <Enter> to continue...";
	cin.get();
	cout << endl << endl;

	sortedArr = PQSort<CD>::pqSort(cdArr, cds->size(), false, &CD::compare_item);

	for (int i = 0; i < cds->size(); i++) {
		CD* cd = sortedArr[i];
		cd->getkey();
	}
	cout << "After (Descending)" << endl;
	cout << "Hit <Enter> to continue...";
	cin.get();
	cout << endl << endl;

	for (int i = 0; i < 5; i++) {
		cds->add(sortedArr[0]);
	}
	cdArr = cds->toArray();

	sortedArr = PQSort<CD>::pqSort(cdArr, cds->size(), true, &CD::compare_item);

	for (int i = 0; i < cds->size(); i++) {
		CD* cd = sortedArr[i];
		cd->getKey();
	}
	cout << "After (Ascending with Duplicates)" << endl;
	cout << "Hit <Enter> to continue...";
	cin.get();
	cout << endl << endl;

	delete[] cdArr;
	delete[] sortedArr;

	delete cds;

	return 0;
}