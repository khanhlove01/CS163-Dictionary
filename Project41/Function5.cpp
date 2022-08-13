#include "Header1.h"

void function5_edit_definition(unordered_map<string, string>& mymap10, int dataset)
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
	if (dataset == 4)
	{
		ofstream fout;
		string path = "Data/slang.txt";
		fout.open(path, ios::app);
		fout << str << endl << str1 << endl;
		fout.close();
	}
	if (dataset == 5)
	{
		ofstream fout;
		string path = "Data/emotional.txt";
		fout.open(path, ios::app);
		fout << str << endl << str1 << endl;
		fout.close();
	}
}