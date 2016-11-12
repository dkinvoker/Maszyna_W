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


struct code_section
{
	string code;
	unsigned long long int begin_index;

	code_section(string code, unsigned long long int begin_index)
		:
		code(code), begin_index(begin_index)
	{

	}
};

class code_transformator
{
	ostream &log_output = cout;
	ifstream &input;
	string code;
	vector<array<unsigned long long int, 2>>box_index;
	vector<code_section>code_sections;

	//queue<unsigned long long int>box_open_index;
	//stack<unsigned long long int>box_close_index;

public:
	//reads code from input to string-buffer and deletes blank symbols
	void clear_blank_and_save();

	//checks syntax. return true if succesed, false if fail. Throw log to log_output
	bool check_syntax();

	//
	bool code_into_sections();

	
	code_transformator() = delete;
	code_transformator(ostream &log_output, ifstream &input);
	~code_transformator();
};

