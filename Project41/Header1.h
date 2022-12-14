#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <string>
#include <algorithm>
#include<direct.h>
#include <cstring>
#include <cstdlib>

using namespace std;

void input_data_slang(unordered_map<string, string>& mymap10, ifstream& fin, vector<string>& v);
void input_data_emotional(unordered_map<string, string>& mymap, ifstream& fin, vector<string>& v);
//void input_data_slang_origin(unordered_map<string, string>& mymap10, ifstream& fin);
//void input_data_emotional_origin(unordered_map<string, string>& mymap, ifstream& fin);

void inter_face();
void function2_create_favouritelist(unordered_map<string, string>& mymap10);
void function3_search_definition(unordered_map<string, string>& mymap10);
void function5_edit_definition(unordered_map<string, string>& mymap10, vector<string>& v,int dataset);
void function6_edit_definition(unordered_map<string, string>& mymap10, vector<string>& v,int dataset);
void function7_remove(unordered_map<string, string>& mymap10, vector<string>& v, int dataset);
void function8_reset(unordered_map<string, string>& mymap10,int dataset, vector <string>& v);
void function9_viewrandom(unordered_map<string, string>& mymap10, vector<string>& v);
void function10_viewfavouritelist();
