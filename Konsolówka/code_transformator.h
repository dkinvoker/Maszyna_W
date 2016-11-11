#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "const_regex.h"
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <array>

using namespace std;


class code_transformator
{
	string code;
	vector<array<unsigned long long int, 2>>box_index;
	//queue<unsigned long long int>box_open_index;
	//stack<unsigned long long int>box_close_index;

public:
	//reads code from input to string-buffer and deletes blank symbols
	void clear_blank_and_save(ifstream &input);

	//checks syntax. return true if succesed, false if fail. Throw log to log_output
	bool check_syntax(ostream &log_output = cout);

	
	code_transformator();
	~code_transformator();
};

