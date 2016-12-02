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


//chiñskoœæ 100%
string ITOS(int a);


class Command
{
protected:
	string command_string;
	Tag_menager *tag_menager_ptr = nullptr;

public:

	virtual Assembler_section expand() = 0;
	virtual void Load_sring_into(string&);

	Command(string code, code_transformator &CT_to_ref);
	//Command(Tag_menager &ref, string code);

	Command();
	~Command();
};

