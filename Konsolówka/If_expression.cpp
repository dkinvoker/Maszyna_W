#include "If_expression.h"

void extract_logic_symbol_and_indexes(string &arg_string, int &logic_operator, unsigned int &logic_symbol_start_index, unsigned int &logic_symbol_end_index)
{
	for (unsigned int i = 0; i < arg_string.size(); i ++)
	{
		if (arg_string[i] == '<')
		{
			if (arg_string[i+1] == '=')
			{
				logic_operator = less_or_equal_to;
				logic_symbol_start_index = i;
				logic_symbol_end_index = i + 1;
			}
			else
			{
				logic_operator = int_symbolic_logic_operators::less;
				logic_symbol_start_index = i;
				logic_symbol_end_index = i;
			}
		}
		else if (arg_string[i] == '!')
		{
			logic_operator = not_equal_to;
			logic_symbol_start_index = i;
			logic_symbol_end_index = i + 1;
		}
		else if (arg_string[i] == '>')
		{
			if (arg_string[i + 1] == '=')
			{
				logic_operator = greater_or_equal_to;
				logic_symbol_start_index = i;
				logic_symbol_end_index = i + 1;
			}
			else
			{
				logic_operator = int_symbolic_logic_operators::greater;
				logic_symbol_start_index = i;
				logic_symbol_end_index = i;
			}
		}
		else if (arg_string[i] == '=')
		{
			logic_operator = int_symbolic_logic_operators::equal_to;
			logic_symbol_start_index = i;
			logic_symbol_end_index = i + 1;
		}
	}
}

void If_expression::extract_logic_expresions()
{
	string buffer;

	//first bracket always third!
	unsigned int first_bracket_symbol_index = 3;
	unsigned int second_bracket_symbol_index;
	unsigned int logic_symbol_start_index;
	unsigned int logic_symbol_end_index;

	for (unsigned int i = 0; command_string.size(); i ++)
	{
		if (command_string[i] == ')')
		{
			second_bracket_symbol_index = i;
			break;
		}
	}

	buffer = command_string.substr(first_bracket_symbol_index, second_bracket_symbol_index - 3);

	extract_logic_symbol_and_indexes(buffer, logic_operator, logic_symbol_start_index, logic_symbol_end_index);

	//TERAZ BÊDZIESZ PISA TUTAJ!!!!!!!!!!
	//!!!!!!!!!!!
	//!!!!!!!!!!!
	//!!!!!!!!!!!
	//!!!!!!!!!!!
	//!!!!!!!!!!!
}



Assembler_section If_expression::translate()
{
	Assembler_section returner;

	this->extract_logic_expresions();

	return returner;
}



If_expression::If_expression(string code)
	:
	Command(code)
{
}


//If_expression::If_expression()
//{
//}


If_expression::~If_expression()
{
}
