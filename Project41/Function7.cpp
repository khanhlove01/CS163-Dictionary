#include "Header1.h"

void function7_remove(unordered_map<string, string>& mymap10)
{
	string str;
	cout << "Input word you want to remove: ";
	cin.ignore();
	getline(cin, str);
	if (mymap10.find(str) != mymap10.end())
	{
		mymap10.erase(str);
	}
	else cout << "Word doesn't exist!!!";
}