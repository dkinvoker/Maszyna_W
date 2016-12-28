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

enum Assembler_type
{
	program_type,
	data_type
};

enum Tag_type
{
	constant,
	variable_int,
	variable_char,
	sub,
	meta_tag
};

enum int_symbolic_value_to_operators
{
	divid_symbol,
	add_symbol,
	subtract_symbol,
	multiplication_symbol
};

enum int_symbolic_logic_operators
{
	less,
	greater,
	equal_to,
	not_equal_to,
	less_or_equal_to,
	greater_or_equal_to
};

enum meta_command_ID
{
	no_meta,
	REVERSE,
	DELETE_UP
};

inline string Char_to_asci_code_as_string(char arg_char)
{
	int buffer = arg_char;
	return to_string(buffer);
}

inline string return_without_last_symbol (string a)
{
	return a.substr(0, a.size() - 1);
}

inline int command_to_meta_ID(string a)
{
	if (a == "REVERSE")
	{
		return meta_command_ID::REVERSE;
	}
	else if (a == "DELETE_UP")
	{
		return meta_command_ID::DELETE_UP;
	}
	else
	{
		return meta_command_ID::no_meta;
	}
}

struct tag_swaps
{
	string swaped_tag;
	string swaper;

	tag_swaps(string swaped, string swaper)
		:
		swaped_tag(swaped), swaper(swaper)
	{
	}
};

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


	bool is_just_tag()
	{
		if (tag != "" && W_command == "" && argument == "")
		{
			return true;
		}
		return false;
	}

	W_Assembler_line return_with_swaped_tag(string swaper_tag)
	{
		return W_Assembler_line{this->tag, this->W_command, swaper_tag};
	}

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

	void add_meta_command(string meta_command)
	{
		program_assembler_vector.push_back(W_Assembler_line{ "", meta_command, "" });
	}

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


