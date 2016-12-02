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
//#include "Command.h"


class Tag_menager
{
	vector<Tag_and_its_name> Tags_vector;

public:

	Tag_and_its_name* find_by_tag(string tag_to_find);
	Tag_and_its_name* find_by_name(string tag_to_name);
	void add(Tag_and_its_name);
	void add(string name, int type);
	const string get_last_tag();
	int how_many_tags();

	Tag_menager();
	~Tag_menager();
};

