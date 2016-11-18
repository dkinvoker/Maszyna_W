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
#include <map>

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

struct W_Assembler_line
{

	string tag;
	string W_command;
	string argument;

	W_Assembler_line(string tag, string W_command, string argument)
		:
		tag(tag), W_command(W_command), argument(argument)
	{
	}


};

class code_transformator
{
	ostream &log_output = cout;
	ofstream &assembler_prg_output_file;
	ifstream &input;
	string code;
	vector<array<unsigned long long int, 2>> box_index;
	vector<code_section> code_sections;

	vector<W_Assembler_line> program;
	vector<W_Assembler_line> data;

	map<int, W_Assembler_line&> const_ID;

	vector<string> expression_with_consts;

	//queue<unsigned long long int>box_open_index;
	//stack<unsigned long long int>box_close_index;

public:
	//reads code from input to string-buffer and deletes blank symbols
	void clear_blank_and_save();

	//checks syntax. return true if succesed, false if fail. Throw log to log_output
	bool check_syntax();

	//Divides code into box-sections
	bool code_into_sections();

	//catches_consts_from_code
	void catch_consts();

	
	code_transformator() = delete;
	code_transformator(ostream &log_output, ifstream &input, ofstream &output);
	~code_transformator();
};

