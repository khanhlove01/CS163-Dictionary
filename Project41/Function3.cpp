#include "Header1.h"

void function3_search_definition(unordered_map<string, string>& mymap10)
{
	string str;
	cout << "Input Key: " << endl;
	cin >> str;
	ofstream fout;
	string path = "Data/History/list.txt";
	fout.open(path, ios::app);
	fout << str << endl;
	fout.close();
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