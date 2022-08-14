#include "Header1.h"

void function9_viewrandom(unordered_map<string, string>& mymap10, vector<string>& v)
{
 int n, random;
 n = rand() % 1000 + 1;
 cout << "Random Word: " << v[n] << endl;
 cout << "Random Word's definition: " << mymap10[v[n]] << endl;
 system("pause");
}