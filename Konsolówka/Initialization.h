#pragma once



#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "const_regex.h"
#include <vector>
#include "Declaration.h"



class Initialization:
	public Declaration
{
public:

	virtual Assembler_section translate();

	Initialization(string code);
	Initialization() = delete;
	~Initialization();
};


