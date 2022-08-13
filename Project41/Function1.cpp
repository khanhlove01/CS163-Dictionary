#include "Header1.h"

void input_data_slang(unordered_map<string, string>& mymap10, ifstream& fin)
{
	fin.open("slang.txt");
	string str10;
	while (!fin.eof())
	{
		getline(fin, str10);
		int tmp = 0;
		bool check = true;
		string s1 = "", s2 = "";
		while (tmp < str10.size())
		{
			if (str10[tmp] == '`')	check = false;
			if (check == true)
			{
				s1 = s1 + str10[tmp];
			}
			if (str10[tmp] != '`' && check == false)
			{
				s2 = s2 + str10[tmp];
			}
			/*if (str[tmp] == ' ' && check == true)
				check = true;*/
			tmp++;
		}
		//while (s2[0] == '\t') s2.erase(0, 1);
		//cout << s1 << " " << s2 << endl;
		mymap10[s1] = s2;
	}

	fin.close();

	
}
void input_data_emotional(unordered_map<string, string>& mymap, ifstream& fin)
{
	fin.open("emotional.txt");
	string str;
	while (!fin.eof())
	{
		getline(fin, str);
		int tmp = 0;
		bool check = true;
		string s1 = "", s2 = "";
		while (tmp < str.size())
		{
			if (str[tmp] == '\t')	check = false;
			if (check == true)
			{
				s1 = s1 + str[tmp];
			}
			if (check == false)
			{
				s2 = s2 + str[tmp];
			}
			/*if (str[tmp] == ' ' && check == true)
				check = true;*/
			tmp++;
		}
		while (s2[0] == '\t') s2.erase(0, 1);
		//cout << s1 << " " << s2 << endl;
		mymap[s1] = s2;
	}
	//unordered_map<string, string>::iterator it;
	/*cin >> str;
	if (mymap.find(str) != mymap.end())
	{
		cout << mymap[str];
	}
	else cout << 1;*/

	fin.close();
}