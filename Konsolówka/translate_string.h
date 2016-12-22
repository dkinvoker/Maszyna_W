#pragma once


#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "const_regex.h"
#include <vector>
#include "Struct_header.h"


using namespace std;




inline int which_command(string &arg_string)
{
	for (unsigned int i = 0; i < const_regex::all_regex.size(); i ++)
	{
		if (regex_match(arg_string, const_regex::all_regex[i]))
		{
			return i;
		}
	}

	//incorrect command
	return -1;

}

inline void adapt_section(Assembler_section &adaptiong_section, Assembler_section &section_to_adapt)
{
	for (unsigned int i = 0; i < section_to_adapt.program_assembler_vector.size(); i++)
	{
		adaptiong_section.program_assembler_vector.push_back(section_to_adapt.program_assembler_vector[i]);
	}
	for (unsigned int i = 0; i < section_to_adapt.data_assembler_vector.size(); i++)
	{
		adaptiong_section.data_assembler_vector.push_back(section_to_adapt.data_assembler_vector[i]);
	}
}


Assembler_section translate_string(const string &arg_string);