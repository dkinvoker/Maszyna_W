#pragma once
#include "Command.h"
class Equation :
	public Command
{

	string equation_head;
	string expression;
	vector<string> operands_vector;
	vector<int> operators_vector;

	//Divide command_string to head nd expression
	void extract_components();
	//Divide expression_string into operands_vector and operators_vector
	void get_all_expression_information();



public:

	virtual Assembler_section translate();
	Equation(string code, code_transformator &CT_to_ref);
	Equation() = delete;
	~Equation();
};

