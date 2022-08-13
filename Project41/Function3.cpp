#include "Header1.h"

void function3_search_definition(unordered_map<string, string>& mymap10)
{
	string str;
	cout << "Input Key: " << endl;
	cin >> str;
	if (mymap10.find(str) != mymap10.end())
	{
		cout << mymap10[str] << endl;
		system("pause");
	}
	else
	{
		cout << "No existing!!!" << endl;
		system("pause");
	}
}