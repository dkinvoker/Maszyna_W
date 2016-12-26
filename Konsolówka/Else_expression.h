#pragma once
#include "Command.h"
class Else_expression :
	public Command
{
	string code_to_execute;

public:

	Assembler_section translate();

	Else_expression(string code);
	Else_expression() = delete;
	~Else_expression();
};

