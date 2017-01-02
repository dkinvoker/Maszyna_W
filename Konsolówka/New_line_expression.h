#pragma once
#include "Command.h"
class New_line_expression :
	public Command
{
public:

	Assembler_section translate();

	New_line_expression(string code);
	New_line_expression() = delete;
	~New_line_expression();
};

