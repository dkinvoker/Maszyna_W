#pragma once
#include "Command.h"
class Sub_declaration_expression :
	public Command
{
	vector<string> input_variables;
	vector<string> output_variables;

	string code_to_execute;
	string name;

	void extract_name();
	void extract_variables();
	void extract_code_to_execute();

public:

	Assembler_section translate();

	Sub_declaration_expression(string code);
	Sub_declaration_expression() = delete;
	~Sub_declaration_expression();
};

