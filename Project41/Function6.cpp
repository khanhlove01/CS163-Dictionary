#include "Header1.h"

void function6_edit_definition(unordered_map<string, string>& mymap10)
{
	string str, str1;
	cout << "Input word and definition you want to edit: " << endl;
	cout << "Input word you want to edit the definition: ";
	cin.ignore();
	getline(cin, str);
	cout << "Input definition you want to edit: ";
	//cin.ignore();
	getline(cin, str1);
	if (mymap10.find(str) != mymap10.end())
	{
		mymap10[str] = str1;
	}
	else cout << "Word doesn't exist!!!";
}