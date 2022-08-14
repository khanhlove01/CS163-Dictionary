#include "Header1.h"

void function10_viewfavouritelist()
{
	string str;
	string path = "Data/Favourite_list/list.txt";
	ifstream fin;
	fin.open(path, ios::in);
	while (!fin.eof())
	{
		getline(fin, str);
		cout << str << endl;
	}
	

	fin.close();
}