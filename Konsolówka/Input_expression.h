#pragma once
#include "Command.h"
class Input_expression :
	public Command
{

	string ID;
	void extract_ID();

public:

	Assembler_section translate();

	Input_expression(string code);
	Input_expression() = delete;
	~Input_expression();
};

