#pragma once
#include "Command.h"
class Return_expression :
	public Command
{
public:
	Assembler_section translate();

	Return_expression(string code);
	Return_expression() = delete;
	~Return_expression();
};

