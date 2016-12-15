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
#include "Struct_header.h"
#include "Tag_menager.h"
#include "code_transformator.h"

//extern code_transformator Code_Transormator;


//chi�sko�� 100%
string Int_TO_String(int a);


class Command
{
protected:
	string command_string;
	static Tag_menager *tag_menager_ptr;

public:

	virtual Assembler_section translate() = 0;
	virtual void Load_sring_into(string&);

	static void set_static_tag_menager_ptr (Tag_menager* ptr);

	Command(string code);
	//Command(Tag_menager &ref, string code);

	Command() = delete;
	~Command();
};