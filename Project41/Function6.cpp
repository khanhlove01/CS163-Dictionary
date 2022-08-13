#include "Header1.h"

void function6_edit_definition(unordered_map<string, string>& mymap10, vector<string>& v,int dataset)
{
	string path = "";
	if (dataset == 4) path = "Data/slang.txt";
	if (dataset == 5) path = "Data/emotional.txt";
	string str, str1;
	cout << "Input word and definition you want to edit: " << endl;
	cout << "Input word you want to edit the definition: ";
	cin.ignore();
	getline(cin, str);
	cout << "Input definition you want to edit: ";
	//cin.ignore();
	ofstream fout;
	fout.open(path);
	getline(cin, str1);
	bool check = false;
	for (auto u : v)
	{
		fout << u << endl << mymap10[u] << endl;
		if (u == str)
		{
			check = true;
			fout << u << endl << str1 << endl;
			mymap10[str] = str1;
		}
	}
	fout.close();
	if (check == false) cout << "Word doesn't exist!!!";
}