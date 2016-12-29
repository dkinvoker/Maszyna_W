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


class Tag_menager
{

	vector<Tag_and_its_name> Tags_vector;
	vector<unsigned int> Const_tags_vector;
	unsigned int number_of_jump_meta_tags = 0;

public:

	Tag_and_its_name* find_by_tag(string tag_to_find);
	Tag_and_its_name* find_by_name(string tag_to_name);

	const string get_tag_by_name( string name );
	void add(Tag_and_its_name);
	void add(string name, int type);
	Tag_and_its_name* find_const_by_value(string value);
	const string get_tag_by_const_value(string value);
	//returns true if added, false if not
	bool add_const(string value);
	const string get_last_tag();
	const string get_last_constant_tag();
	int how_many_tags();
	//Adds new jump tag, and returns its name
	const string add_next_jump_tag();
	const string get_last_jump_tag();
	const string get_last_jump_name();
	const string get_LAST_BUT_ONE_jump_tag();
	const int get_type_by_name(string name);

	Tag_menager();
	~Tag_menager();
};

