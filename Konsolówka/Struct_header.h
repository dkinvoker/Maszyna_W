#pragma once


#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "const_regex.h"
#include <vector>
#include <array>
#include <sstream>

using namespace std;

inline string Char_to_asci_code_as_string(char arg_char)
{
	int buffer = arg_char;
	return to_string(buffer);
}

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

	void add_data(string tag, string command, string argument)
	{
		data_assembler_vector.push_back(W_Assembler_line{ tag + ":", command, argument });
	}
	void add_data(string command, string argument)
	{
		data_assembler_vector.push_back(W_Assembler_line{ "", command, argument });
	}


	void add_program(string tag, string command, string argument)
	{
		program_assembler_vector.push_back(W_Assembler_line{ tag + ":", command, argument });
	}
	void add_program(string command, string argument)
	{
		program_assembler_vector.push_back(W_Assembler_line{ "", command, argument });
	}

};


enum Tag_type
{
	constant,
	variable_int,
	variable_char,
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

enum int_symbolic_vbalue_to_operators
{
	divid_symbol,
	add_symbol,
	subtract_symbol,
	multiplication_symbol
};


