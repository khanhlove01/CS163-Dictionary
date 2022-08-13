#include "Header1.h"

//void input_data_slang_origin(unordered_map<string, string>& mymap10, ifstream& fin)
//{
//	fin.open("slang.txt");
//	string path = "Data/slang.txt";
//	ofstream fout;
//	fout.open(path);
//
//	string str10;
//	while (!fin.eof())
//	{
//		getline(fin, str10);
//		int tmp = 0;
//		bool check = true;
//		string s1 = "", s2 = "";
//		while (tmp < str10.size())
//		{
//			if (str10[tmp] == '`')	check = false;
//			if (check == true)
//			{
//				s1 = s1 + str10[tmp];
//			}
//			if (str10[tmp] != '`' && check == false)
//			{
//				s2 = s2 + str10[tmp];
//			}
//			/*if (str[tmp] == ' ' && check == true)
//				check = true;*/
//			tmp++;
//		}
//		//while (s2[0] == '\t') s2.erase(0, 1);
//		//cout << s1 << " " << s2 << endl;
//		mymap10[s1] = s2;
//		fout << s1 << endl << s2 << endl;
//	}
//
//	fin.close();
//	fout.close();
//
//	
//}
void input_data_slang(unordered_map<string, string>& mymap10, ifstream& fin, vector<string>& v)
{
	string path = "Data/slang.txt";
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
}

void input_data_emotional(unordered_map<string, string>& mymap10, ifstream& fin, vector<string>& v)
{
	string path = "Data/emotional.txt";
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
}
//void input_data_emotional_origin(unordered_map<string, string>& mymap, ifstream& fin)
//{
//	fin.open("emotional.txt");
//	string path = "Data/emotional.txt";
//	ofstream fout;
//	fout.open(path);
//	string str;
//	while (!fin.eof())
//	{
//		getline(fin, str);
//		int tmp = 0;
//		bool check = true;
//		string s1 = "", s2 = "";
//		while (tmp < str.size())
//		{
//			if (str[tmp] == '\t')	check = false;
//			if (check == true)
//			{
//				s1 = s1 + str[tmp];
//			}
//			if (check == false)
//			{
//				s2 = s2 + str[tmp];
//			}
//			/*if (str[tmp] == ' ' && check == true)
//				check = true;*/
//			tmp++;
//		}
//		while (s2[0] == '\t') s2.erase(0, 1);
//		//cout << s1 << " " << s2 << endl;
//		mymap[s1] = s2;
//		fout << s1 << endl << s2 << endl;
//	}
//	//unordered_map<string, string>::iterator it;
//	/*cin >> str;
//	if (mymap.find(str) != mymap.end())
//	{
//		cout << mymap[str];
//	}
//	else cout << 1;*/
//
//	fin.close();
//	fout.close();
//}