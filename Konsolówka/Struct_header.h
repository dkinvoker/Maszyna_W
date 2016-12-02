#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "const_regex.h"
#include <vector>
#include <array>
#include <map>
#include <sstream>

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

	W_Assembler_line(string tag, string W_command, char* argument)
		:
		tag(tag), W_command(W_command), argument((string)argument)
	{
	}

	W_Assembler_line(string tag, string W_command, char argument)
		:
		tag(tag), W_command(W_command)
	{
	 	this->argument = string{ argument };
	}

};

struct Const_expresion
{
	string expression_code;
	int expression_type;

	Const_expresion(string expression_code, int expression_type)
		:
		expression_code(expression_code), expression_type(expression_type)
	{
	}
};

enum Assembler_type
{
	program_type,
	data_type
};

struct Assembler_section
{
	vector<W_Assembler_line> program_assembler_vector;
	vector<W_Assembler_line> data_assembler_vector;
};


enum Tag_type
{
	constant,
	variable,
	sub
};

struct Tag_and_its_name
{
	string name;
	string tag;
	int type;

	Tag_and_its_name(string name, string tag, int type)
		:
		name(name),
		tag(tag),
		type(type)
	{
	}


};