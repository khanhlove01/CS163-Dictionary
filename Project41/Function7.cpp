#include "Header1.h"

void function7_remove(unordered_map<string, string>& mymap10, vector<string>& v, int dataset)
{
	string str,path;
	cout << "Input word you want to remove: ";
	cin.ignore();
	getline(cin, str);
	ifstream fin;
	if (dataset == 4)
	{
		input_data_slang(mymap10, fin,v);
		path = "Data/slang.txt";

	}
	if (dataset == 5)
	{
		input_data_emotional(mymap10, fin, v);
		path = "Data/emotional.txt";
	}
	bool check = false;
	ofstream fout;
	fout.open(path);
	for (auto u : v)
	{
		if (u == str)
		{
			mymap10.erase(u);
			check = true;
			continue;
		}
		fout << u << endl << mymap10[u];
	}
	fout.close();
	if (check == false) cout << "Word doesn't exist!!!!!";
}