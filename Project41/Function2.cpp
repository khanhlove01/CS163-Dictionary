#include "Header1.h"

void function2_create_favouritelist(unordered_map<string, string>& mymap10)
{
	string path = "Data/Favourite_list";
	/*_mkdir(path.c_str());*/
	ofstream fout;
	path = "Data/Favourite_list/list.txt";
	fout.open(path, ios::app);
	cout << "Input word: ";
	string str;
	cin >> str;
	if (mymap10.find(str) != mymap10.end())
	{
		//fout << str << endl;
		//fout << str << endl;
		fout << str << endl;
		cout << "Add successfully !!!";
		system("pause");
	}
	else
	{
		cout << " Can't find the word you need !!!";
		system("pause");
	}
	fout.close();
}