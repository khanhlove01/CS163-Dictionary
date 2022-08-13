#include "Header1.h"

void function8_reset(unordered_map<string, string>& mymap10,int dataset,vector <string>& v)
{
	v.clear();
	mymap10.clear();
	ifstream fin;
	ofstream fout;
	if (dataset == 4)
	{
		string path = "Data/Origin/slang.txt";
		fin.open(path, ios::in);
		string str, str1;
		while (!fin.eof())
		{
			getline(fin, str);
			getline(fin, str1);
			mymap10[str] = str1;
			v.push_back(str);
		}
		fin.close();

		path = "Data/slang.txt";
		fout.open(path);
		for (auto u : v) fout << u << endl << mymap10[u] << endl;
		fout.close();

	}
	if (dataset == 5)
	{
		string path = "Data/Origin/emotional.txt";
		fin.open(path, ios::in);
		string str, str1;
		while (!fin.eof())
		{
			getline(fin, str);
			getline(fin, str1);
			mymap10[str] = str1;
			v.push_back(str);
		}
		path = "Data/emotional.txt";
		fout.open(path);
		for (auto u : v) fout << u << endl << mymap10[u] << endl;
		fin.close();
		fout.close();
	}
}