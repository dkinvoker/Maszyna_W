#pragma once
#include <iostream>
#include <string>
#include <regex>
#include "const_regex.h"

using namespace std;

class expression
{
	string expression_string_property;


public:

	virtual bool is_correct() = 0;

	//---------------------------
	expression() = default;
	expression(string);
	~expression();
};

