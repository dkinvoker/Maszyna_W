#pragma once



#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "const_regex.h"
#include <vector>
#include "Struct_header.h"
#include "Tag_menager.h"
#include "Sub_menager.h"




//extern code_transformator Code_Transormator;


//chiñskoœæ 100%
string Int_TO_String(int a);


class Command
{
protected:
	string command_string;
	static Tag_menager *tag_menager_ptr;
	static Sub_menager *sub_menager_ptr;
	static string *last_success_string_ptr;
	static bool *was_last_success_if_ptr;
	static bool *inside_sub_declaration;

public:

	virtual Assembler_section translate() = 0;
	virtual void Load_sring_into(string&);

	static void set_is_inside_sub_declaration(bool *ptr);
	static void set_static_tag_menager_ptr (Tag_menager *ptr);
	static void set_last_success_string_ptr (string *ptr);
	static void set_was_last_success_if_ptr (bool *ptr);
	static void set_sub_menager_ptr (Sub_menager *ptr);

	Command(string code);
	//Command(Tag_menager &ref, string code);

	Command() = delete;
	~Command();
};


