#pragma once
#include "Command.h"


class If_expression :
	public Command
{
protected: 
	string code_to_execute;

private:
	string expression_1;
	string expression_2;
	int logic_operator;

	void extract_logic_symbol_and_indexes(string &arg_string, int &logic_operator, unsigned int &logic_symbol_start_index, unsigned int &logic_symbol_end_index);

	//obvious
	void extract_logic_expresions_and_execute_code();

	//returns assembler code doing good things ^^
	Assembler_section make_calculations(string first_expression, bool is_first_const, bool is_first_FullType_expression, string secound_expression, bool is_secound_const, bool is_secound_FullType_expression);


	//obvious; true if it is necessary to add RPA command
	bool register_slot_for_expression_1_result();
	bool register_slot_for_expression_2_result();


public:
	virtual Assembler_section translate();
	If_expression(string code);
	If_expression() = delete;
	~If_expression();
};

