#pragma once
#include "Command.h"
class If_expression :
	public Command
{

	string expression_1;
	string expression_2;
	int logic_operator;
	string code_to_execute;

	//obvious
	void extract_logic_expresions();

public:


	virtual Assembler_section translate();
	If_expression(string code);
	If_expression() = delete;
	~If_expression();
};

