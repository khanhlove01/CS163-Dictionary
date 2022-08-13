#include "Header1.h"

void function5_edit_definition(unordered_map<string, string>& mymap10)
{
	string str, str1;
	cout << "Input word and definition you want to add: " << endl;
	cout << "Input word: ";
	cin.ignore();
	getline(cin, str);
	cout << "Input definition: ";
	//cin.ignore();
	getline(cin, str1);
	mymap10[str] = str1;
}