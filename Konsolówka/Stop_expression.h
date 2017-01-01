#pragma once
#include "Command.h"
class Stop_expression :
	public Command
{
public:
	
	Assembler_section translate();

	Stop_expression(string code);
	Stop_expression() = delete;
	~Stop_expression();
};

