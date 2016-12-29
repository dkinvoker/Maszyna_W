#pragma once
#include "Command.h"
class Output_expression :
	public Command
{
	string ID_or_string_to_output;

	void extract_ID();
	void extract_string();

public:

	Assembler_section translate();

	Output_expression(string code);
	Output_expression() = delete;
	~Output_expression();
};

