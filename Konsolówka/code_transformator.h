#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "const_regex.h"
#include <vector>

using namespace std;


static class code_transformator
{
public:
	//reads code from input to string-buffer and deletes blank symbols
	static void clear_blank_and_save(ifstream &input, string &buffer);
	code_transformator();
	~code_transformator();
};

