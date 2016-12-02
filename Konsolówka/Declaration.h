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
#include "Command.h"

class Declaration:
	public Command
{

public:

	virtual Assembler_section translate();

	Declaration(string code, code_transformator &CT_to_ref);
	Declaration() = delete;
	~Declaration();
};

