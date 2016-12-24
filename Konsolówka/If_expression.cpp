#include "If_expression.h"
#include "equation.h"
#include "translate_string.h"

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
				break;
			}
			else
			{
				logic_operator = int_symbolic_logic_operators::less;
				logic_symbol_start_index = i;
				logic_symbol_end_index = i;
				break;
			}
		}
		else if (arg_string[i] == '!')
		{
			logic_operator = not_equal_to;
			logic_symbol_start_index = i;
			logic_symbol_end_index = i + 1;
			break;
		}
		else if (arg_string[i] == '>')
		{
			if (arg_string[i + 1] == '=')
			{
				logic_operator = greater_or_equal_to;
				logic_symbol_start_index = i;
				logic_symbol_end_index = i + 1;
				break;
			}
			else
			{
				logic_operator = int_symbolic_logic_operators::greater;
				logic_symbol_start_index = i;
				logic_symbol_end_index = i;
				break;
			}
		}
		else if (arg_string[i] == '=')
		{
			logic_operator = int_symbolic_logic_operators::equal_to;
			logic_symbol_start_index = i;
			logic_symbol_end_index = i + 1;
			break;
		}
	}
}

void If_expression::extract_logic_expresions_and_execute_code()
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

	expression_1 = buffer.substr(0, logic_symbol_start_index);
	expression_2 = buffer.substr(logic_symbol_end_index + 1, buffer.size() - logic_symbol_end_index);

	//+2 bo... cza omin¹æ "{"
	code_to_execute = command_string.substr(second_bracket_symbol_index + 2, command_string.size() -3 - second_bracket_symbol_index);

}

const string string_meta_expression1{ "0Expression1" };
const string string_meta_expression2{ "0Expression2" };

bool If_expression::register_slot_for_expression_1_result()
{
	if (tag_menager_ptr->find_by_name(string_meta_expression1) == nullptr)
	{
		tag_menager_ptr->add(string_meta_expression1, meta_tag);
		return true;
	}
	return false;
}

bool If_expression::register_slot_for_expression_2_result()
{
	if (tag_menager_ptr->find_by_name(string_meta_expression2) == nullptr)
	{
		tag_menager_ptr->add(string_meta_expression2, meta_tag);
		return true;
	}
	return false;
}

Assembler_section If_expression::make_calculations(string first_expression, bool is_first_const, bool is_first_FullType_expression, string secound_expression, bool is_secound_const, bool is_secound_FullType_expression)
{
	Assembler_section returner;
	string first_component = first_expression;
	string secound_component = secound_expression;

	//adding const
	if (is_first_const)
	{
		if (tag_menager_ptr->add_const(first_expression))
		{
			returner.add_data("RST", first_expression);
		}
	}
	if (is_secound_const)
	{
		if (tag_menager_ptr->add_const(secound_expression))
		{
			returner.add_data("RST", secound_expression);
		}
	}

	//register
	if (is_first_FullType_expression)
	{
		if (this->register_slot_for_expression_1_result())
		{
			returner.add_data(tag_menager_ptr->get_tag_by_name(string_meta_expression1), "RPA", "");
		}
		first_component = string_meta_expression1 + "=" + first_expression + ";";
		adapt_section(returner, Equation{ first_component }.translate());
	}
	if (is_secound_FullType_expression)
	{
		if (this->register_slot_for_expression_2_result())
		{
			returner.add_data(tag_menager_ptr->get_tag_by_name(string_meta_expression2), "RPA", "");
		}
		secound_component = string_meta_expression2 + "=" + secound_expression + ";";
		adapt_section(returner, Equation{ secound_component }.translate());
	}

	//calctualtins ^^
	switch (logic_operator)
	{
	case int_symbolic_logic_operators::less:

		if (is_first_const)
		{
			returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(first_component));
		}
		else if (is_first_FullType_expression)
		{
			returner.add_program("POB", tag_menager_ptr->get_tag_by_name(string_meta_expression1));
		}
		else
		{
			returner.add_program("POB", tag_menager_ptr->get_tag_by_name(first_component));
		}

		if (is_secound_const)
		{
			returner.add_program("ODE", tag_menager_ptr->get_tag_by_const_value(secound_component));
		}
		else if (is_secound_FullType_expression)
		{
			returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(string_meta_expression2));
		}
		else
		{
			returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(secound_component));
		}

		tag_menager_ptr->add_next_jump_tag();
		returner.add_program("SOM", tag_menager_ptr->get_last_jump_tag());
		tag_menager_ptr->add_next_jump_tag();
		returner.add_program("SOB", tag_menager_ptr->get_last_jump_tag());
		returner.add_program(tag_menager_ptr->get_LAST_BUT_ONE_jump_tag(), "", "");
		adapt_section(returner, translate_string(code_to_execute));
		returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");


		break;
	case int_symbolic_logic_operators::greater:

		if (is_secound_const)
		{
			returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(secound_component));
		}
		else if (is_secound_FullType_expression)
		{
			returner.add_program("POB", tag_menager_ptr->get_tag_by_name(string_meta_expression2));
		}
		else
		{
			returner.add_program("POB", tag_menager_ptr->get_tag_by_name(secound_component));
		}

		if (is_first_const)
		{
			returner.add_program("ODE", tag_menager_ptr->get_tag_by_const_value(first_component));
		}
		else if (is_first_FullType_expression)
		{
			returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(string_meta_expression1));
		}
		else
		{
			returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(first_component));
		}

		tag_menager_ptr->add_next_jump_tag();
		returner.add_program("SOM", tag_menager_ptr->get_last_jump_tag());
		tag_menager_ptr->add_next_jump_tag();
		returner.add_program("SOB", tag_menager_ptr->get_last_constant_tag());
		returner.add_program(tag_menager_ptr->get_LAST_BUT_ONE_jump_tag(), "", "");
		adapt_section(returner, translate_string(code_to_execute));
		returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");


		break;
	case int_symbolic_logic_operators::equal_to:

		if (is_first_const)
		{
			returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(first_component));
		}
		else if (is_first_FullType_expression)
		{
			returner.add_program("POB", tag_menager_ptr->get_tag_by_name(string_meta_expression1));
		}
		else
		{
			returner.add_program("POB", tag_menager_ptr->get_tag_by_name(first_component));
		}

		if (is_secound_const)
		{
			returner.add_program("ODE", tag_menager_ptr->get_tag_by_const_value(secound_component));
		}
		else if (is_secound_FullType_expression)
		{
			returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(string_meta_expression2));
		}
		else
		{
			returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(secound_component));
		}
		tag_menager_ptr->add_next_jump_tag();
		returner.add_program("SOZ", tag_menager_ptr->get_last_jump_tag());
		tag_menager_ptr->add_next_jump_tag();
		returner.add_program("SOB", tag_menager_ptr->get_last_jump_tag());
		returner.add_program(tag_menager_ptr->get_LAST_BUT_ONE_jump_tag(), "", "");
		adapt_section(returner, translate_string(code_to_execute));
		returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");

		break;
	case int_symbolic_logic_operators::greater_or_equal_to:

		if (is_first_const)
		{
			returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(first_component));
		}
		else if (is_first_FullType_expression)
		{
			returner.add_program("POB", tag_menager_ptr->get_tag_by_name(string_meta_expression1));
		}
		else
		{
			returner.add_program("POB", tag_menager_ptr->get_tag_by_name(first_component));
		}

		if (is_secound_const)
		{
			returner.add_program("ODE", tag_menager_ptr->get_tag_by_const_value(secound_component));
		}
		else if (is_secound_FullType_expression)
		{
			returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(string_meta_expression2));
		}
		else
		{
			returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(secound_component));
		}
		tag_menager_ptr->add_next_jump_tag();
		returner.add_program("SOM", tag_menager_ptr->get_last_jump_tag());
		adapt_section(returner, translate_string(code_to_execute));
		returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");

		break;
	case int_symbolic_logic_operators::less_or_equal_to:

		if (is_secound_const)
		{
			returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(secound_component));
		}
		else if (is_secound_FullType_expression)
		{
			returner.add_program("POB", tag_menager_ptr->get_tag_by_name(string_meta_expression2));
		}
		else
		{
			returner.add_program("POB", tag_menager_ptr->get_tag_by_name(secound_component));
		}

		if (is_first_const)
		{
			returner.add_program("ODE", tag_menager_ptr->get_tag_by_const_value(first_component));
		}
		else if (is_first_FullType_expression)
		{
			returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(string_meta_expression1));
		}
		else
		{
			returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(first_component));
		}
		tag_menager_ptr->add_next_jump_tag();
		returner.add_program("SOM", tag_menager_ptr->get_last_jump_tag());
		adapt_section(returner, translate_string(code_to_execute));
		returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");

		break;
	case int_symbolic_logic_operators::not_equal_to:

		if (is_first_const)
		{
			returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(first_component));
		}
		else if (is_first_FullType_expression)
		{
			returner.add_program("POB", tag_menager_ptr->get_tag_by_name(string_meta_expression1));
		}
		else
		{
			returner.add_program("POB", tag_menager_ptr->get_tag_by_name(first_component));
		}

		if (is_secound_const)
		{
			returner.add_program("ODE", tag_menager_ptr->get_tag_by_const_value(secound_component));
		}
		else if (is_secound_FullType_expression)
		{
			returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(string_meta_expression2));
		}
		else
		{
			returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(secound_component));
		}
		tag_menager_ptr->add_next_jump_tag();
		returner.add_program("SOZ", tag_menager_ptr->get_last_jump_tag());
		adapt_section(returner, translate_string(code_to_execute));
		returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");

		break;
	default:
		throw string("Dziwny BUG w If-ach obczaj kod");
		break;
	}


	return returner;
}



Assembler_section If_expression::translate()
{

	this->extract_logic_expresions_and_execute_code();


	if (regex_match(expression_1, const_regex::regex_ID_or_number))
	{
		//1 - simple expression; 2 - simple expression
		if (regex_match(expression_2, const_regex::regex_ID_or_number))
		{
			//1 - const
			if (regex_match(expression_1, const_regex::regex_number))
			{
				//1 - const ; 2 - const
				if (regex_match(expression_2, const_regex::regex_number))
				{
					return this->make_calculations(expression_1, true, false, expression_2, true, false);
				}
				//1 - const ; 2 - variable
				else
				{
					return this->make_calculations(expression_1, true, false, expression_2, false, false);
				}
			}
			//1 - variable
			else
			{
				//1 - variable ; 2 - const
				if (regex_match(expression_2, const_regex::regex_number))
				{
					return this->make_calculations(expression_1, false, false, expression_2, true, false);
				}
				//1 - variable ; 2 - variable
				else
				{
					return this->make_calculations(expression_1, false, false, expression_2, false, false);
				}
			}
		}
		// 1 - simple expression; 2 - full expression
		else
		{
			//1 - const
			if (regex_match(expression_1, const_regex::regex_number))
			{
				return this->make_calculations(expression_1, true, false, expression_2, false, true);
			}
			//1- variable
			else
			{

				return this->make_calculations(expression_1, false, false, expression_2, false, true);
			}
		}
	}
	//1 - full expression; 2 - simple expression
	else if (regex_match(expression_2, const_regex::regex_ID_or_number))
	{
		//2 - const
		if (regex_match(expression_2, const_regex::regex_number))
		{
			return this->make_calculations(expression_1, false, true, expression_2, true, false);
		}
		//2 - variable
		else
		{
			return this->make_calculations(expression_1, false, true, expression_2, false, false);
		}
	}
	//1 - full expression; 2 - full expression
	else
	{
		return this->make_calculations(expression_1, false, true, expression_2, false, true);
	}



	*last_success_string_ptr = command_string;
	*was_last_success_if_ptr = true;
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
