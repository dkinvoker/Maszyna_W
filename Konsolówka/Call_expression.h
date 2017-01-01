#pragma once
#include "Command.h"
class Call_expression :
	public Command
{
	vector<string> input_variables;
	vector<string> output_variables;

	string name;

	void extract_name();
	void extract_variables();

public:

	Assembler_section translate();

	Call_expression(string code);
	Call_expression() = delete;
	~Call_expression();
};

