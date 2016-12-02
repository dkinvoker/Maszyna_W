#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "const_regex.h"
#include <vector>
#include <array>
#include <map>
#include "Struct_header.h"
#include "Tag_menager.h"


using namespace std;

string Char_to_asci_code_as_string(char arg_char);


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

	

	//queue<unsigned long long int>box_open_index;
	//stack<unsigned long long int>box_close_index;

public:

	Tag_menager tag_menager;

	//reads code from input to string-buffer and deletes blank symbols
	void clear_blank_and_save();

	//checks syntax. return true if succesed, false if fail. Throw log to log_output
	bool check_syntax();

	//Divides code into box-sections
	bool code_into_sections();

	//catches_consts_from_code
	//void catch_consts();

	//no wiadomo po nazwie, ju¿ mi sie nie chce pisaæ po angielsku
	Tag_menager &get_tag_menager_ref();


	//copy argument Assembler_Section to global-transformator-container
	void adapt_section(Assembler_section section_to_add)
	{
		for (int i = 0; i < section_to_add.program_assembler_vector.size(); i ++)
		{
			program.push_back(section_to_add.program_assembler_vector[i]);
		}
		for (int i = 0; i < section_to_add.data_assembler_vector.size(); i++)
		{
			data.push_back(section_to_add.data_assembler_vector[i]);
		}
	}
	
	code_transformator() = delete;
	code_transformator(ostream &log_output, ifstream &input, ofstream &output);
	~code_transformator();
};

