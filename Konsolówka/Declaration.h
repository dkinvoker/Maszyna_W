#pragma once




#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "const_regex.h"
#include <vector>
#include "Command.h"


class Declaration:
	public Command
{

public:

	virtual Assembler_section translate();

	Declaration(string code);
	Declaration() = delete;
	~Declaration();
};

