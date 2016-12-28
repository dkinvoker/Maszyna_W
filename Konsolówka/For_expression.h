#pragma once
#include "If_expression.h"
class For_expression :
	public If_expression
{
	string initialization_equation_string;
	string conditional_expression;
	string step_equation_string;

	//extracts string initialization_equation_string, string conditional_expression and string step_equation_string
	void extract_for_expression_steps();

public:

	Assembler_section translate();

	For_expression(string code);
	For_expression() = delete;
	~For_expression();
};

