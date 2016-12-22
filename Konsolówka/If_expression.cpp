#include "If_expression.h"
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

void If_expression::register_slot_for_expression_1_result()
{
	if (tag_menager_ptr->find_by_name("0Expression1") == nullptr)
	{
		tag_menager_ptr->add("0Expression1", meta_tag);
	}
}

void If_expression::register_slot_for_expression_2_result()
{
	if (tag_menager_ptr->find_by_name("0Expression2") == nullptr)
	{
		tag_menager_ptr->add("0Expression2", meta_tag);
	}
}


Assembler_section If_expression::translate()
{
	Assembler_section returner;

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
					//Adding const value
					if (tag_menager_ptr->add_const(expression_1))
					{
						returner.add_data(tag_menager_ptr->get_tag_by_const_value(expression_1), "RST", expression_1);
					}
					if (tag_menager_ptr->add_const(expression_2))
					{
						returner.add_data(tag_menager_ptr->get_tag_by_const_value(expression_2), "RST", expression_2);
					}

					//calculations
					switch (logic_operator)
					{
					case int_symbolic_logic_operators::less:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(expression_1));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_const_value(expression_2));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOM", tag_menager_ptr->get_last_jump_tag());
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOB", tag_menager_ptr->get_last_jump_tag());
						returner.add_program(tag_menager_ptr->get_LAST_BUT_ONE_jump_tag(), "", "");
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");


						break;
					case int_symbolic_logic_operators::greater:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(expression_2));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_const_value(expression_1));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOM", tag_menager_ptr->get_last_jump_tag());
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOB", tag_menager_ptr->get_last_constant_tag());
						returner.add_program(tag_menager_ptr->get_LAST_BUT_ONE_jump_tag(), "", "");
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");


						break;
					case int_symbolic_logic_operators::equal_to:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(expression_1));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_const_value(expression_2));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOZ", tag_menager_ptr->get_last_jump_tag());
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOB", tag_menager_ptr->get_last_jump_tag());
						returner.add_program(tag_menager_ptr->get_LAST_BUT_ONE_jump_tag(), "", "");
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");

						break;
					case int_symbolic_logic_operators::greater_or_equal_to:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(expression_1));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_const_value(expression_2));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOM", tag_menager_ptr->get_last_jump_tag());
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");

						break;
					case int_symbolic_logic_operators::less_or_equal_to:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(expression_2));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_const_value(expression_1));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOM", tag_menager_ptr->get_last_jump_tag());
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");

						break;
					case int_symbolic_logic_operators::not_equal_to:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(expression_1));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_const_value(expression_2));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOZ", tag_menager_ptr->get_last_jump_tag());
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");

						break;
					default:
						throw string("Dziwny BUG w If-ach obczaj kod");
						break;
					}

				}
				//1 - const ; 2 - variable
				else
				{
					//Adding const value
					if (tag_menager_ptr->add_const(expression_1))
					{
						returner.add_data(tag_menager_ptr->get_tag_by_const_value(expression_1), "RST", expression_1);
					}

					switch (logic_operator)
					{
					case int_symbolic_logic_operators::less:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(expression_1));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(expression_2));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOM", tag_menager_ptr->get_last_jump_tag());
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOB", tag_menager_ptr->get_last_jump_tag());
						returner.add_program(tag_menager_ptr->get_LAST_BUT_ONE_jump_tag(), "", "");
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");


						break;
					case int_symbolic_logic_operators::greater:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_name(expression_2));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_const_value(expression_1));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOM", tag_menager_ptr->get_last_jump_tag());
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOB", tag_menager_ptr->get_last_constant_tag());
						returner.add_program(tag_menager_ptr->get_LAST_BUT_ONE_jump_tag(), "", "");
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");


						break;
					case int_symbolic_logic_operators::equal_to:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(expression_1));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(expression_2));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOZ", tag_menager_ptr->get_last_jump_tag());
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOB", tag_menager_ptr->get_last_jump_tag());
						returner.add_program(tag_menager_ptr->get_LAST_BUT_ONE_jump_tag(), "", "");
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");

						break;
					case int_symbolic_logic_operators::greater_or_equal_to:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(expression_1));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(expression_2));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOM", tag_menager_ptr->get_last_jump_tag());
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");

						break;
					case int_symbolic_logic_operators::less_or_equal_to:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_name(expression_2));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_const_value(expression_1));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOM", tag_menager_ptr->get_last_jump_tag());
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");

						break;
					case int_symbolic_logic_operators::not_equal_to:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(expression_1));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(expression_2));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOZ", tag_menager_ptr->get_last_jump_tag());
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");

						break;
					default:
						throw string("Dziwny BUG w If-ach obczaj kod");
						break;
					}

				}
			}
			//1 - variable
			else
			{
				//1 - variable ; 2 - const
				if (regex_match(expression_2, const_regex::regex_number))
				{

					//Adding const value
					if (tag_menager_ptr->add_const(expression_2))
					{
						returner.add_data(tag_menager_ptr->get_tag_by_const_value(expression_2), "RST", expression_2);
					}

					switch (logic_operator)
					{
					case int_symbolic_logic_operators::less:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_name(expression_1));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_const_value(expression_2));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOM", tag_menager_ptr->get_last_jump_tag());
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOB", tag_menager_ptr->get_last_jump_tag());
						returner.add_program(tag_menager_ptr->get_LAST_BUT_ONE_jump_tag(), "", "");
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");


						break;
					case int_symbolic_logic_operators::greater:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(expression_2));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(expression_1));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOM", tag_menager_ptr->get_last_jump_tag());
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOB", tag_menager_ptr->get_last_constant_tag());
						returner.add_program(tag_menager_ptr->get_LAST_BUT_ONE_jump_tag(), "", "");
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");


						break;
					case int_symbolic_logic_operators::equal_to:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_name(expression_1));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_const_value(expression_2));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOZ", tag_menager_ptr->get_last_jump_tag());
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOB", tag_menager_ptr->get_last_jump_tag());
						returner.add_program(tag_menager_ptr->get_LAST_BUT_ONE_jump_tag(), "", "");
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");

						break;
					case int_symbolic_logic_operators::greater_or_equal_to:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_name(expression_1));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_const_value(expression_2));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOM", tag_menager_ptr->get_last_jump_tag());
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");

						break;
					case int_symbolic_logic_operators::less_or_equal_to:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(expression_2));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(expression_1));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOM", tag_menager_ptr->get_last_jump_tag());
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");

						break;
					case int_symbolic_logic_operators::not_equal_to:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_name(expression_1));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_const_value(expression_2));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOZ", tag_menager_ptr->get_last_jump_tag());
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");

						break;
					default:
						throw string("Dziwny BUG w If-ach obczaj kod");
						break;
					}


				}
				//1 - variable ; 2 - variable
				else
				{
					switch (logic_operator)
					{
					case int_symbolic_logic_operators::less:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_name(expression_1));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(expression_2));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOM", tag_menager_ptr->get_last_jump_tag());
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOB", tag_menager_ptr->get_last_jump_tag());
						returner.add_program(tag_menager_ptr->get_LAST_BUT_ONE_jump_tag(), "", "");
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");


						break;
					case int_symbolic_logic_operators::greater:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_name(expression_2));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(expression_1));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOM", tag_menager_ptr->get_last_jump_tag());
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOB", tag_menager_ptr->get_last_constant_tag());
						returner.add_program(tag_menager_ptr->get_LAST_BUT_ONE_jump_tag(), "", "");
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");


						break;
					case int_symbolic_logic_operators::equal_to:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_name(expression_1));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(expression_2));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOZ", tag_menager_ptr->get_last_jump_tag());
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOB", tag_menager_ptr->get_last_jump_tag());
						returner.add_program(tag_menager_ptr->get_LAST_BUT_ONE_jump_tag(), "", "");
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");

						break;
					case int_symbolic_logic_operators::greater_or_equal_to:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_name(expression_1));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(expression_2));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOM", tag_menager_ptr->get_last_jump_tag());
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");

						break;
					case int_symbolic_logic_operators::less_or_equal_to:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_name(expression_2));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(expression_1));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOM", tag_menager_ptr->get_last_jump_tag());
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");

						break;
					case int_symbolic_logic_operators::not_equal_to:

						returner.add_program("POB", tag_menager_ptr->get_tag_by_name(expression_1));
						returner.add_program("ODE", tag_menager_ptr->get_tag_by_name(expression_2));
						tag_menager_ptr->add_next_jump_tag();
						returner.add_program("SOZ", tag_menager_ptr->get_last_jump_tag());
						adapt_section(returner, translate_string(code_to_execute));
						returner.add_program(tag_menager_ptr->get_last_jump_tag(), "", "");

						break;
					default:
						throw string("Dziwny BUG w If-ach obczaj kod");
						break;
					}
				}
			}
		}
		// 1 - simple expression; 2 - full expression
		else
		{
			//1 - const
			if (regex_match(expression_1, const_regex::regex_number))
			{
				//!!!!!!!!!!!!!!!!!!
				//!!!!!!!!!!!!!!!!!!
				//!!!!!!!!!!!!!!!!!!
				//!!!!!!!!!!!!!!!!!!
				//!!!!!!!!!!!!!!!!!!
				//!!!!!!!!!!!!!!!!!!
				//!!!!!!!!!!!!!!!!!!
				//!!!!!!!!!!!!!!!!!!
				//!!!!!!!!!!!!!!!!!!
				//!!!!!!!!!!!!!!!!!!
				//!!!!!!!!!!!!!!!!!!
				//!!!!!!!!!!!!!!!!!!
				//!!!!!!!!!!!!!!!!!!
				//!!!!!!!!!!!!!!!!!!
				//!!!!!!!!!!!!!!!!!!
			}
			//1- variable
			else
			{

			}
		}
	}
	//1 - full expression; 2 - simple expression
	else if (regex_match(expression_2, const_regex::regex_ID_or_number))
	{
		//2 - const
		if (regex_match(expression_2, const_regex::regex_number))
		{

		}
		//2 - variable
		else
		{

		}
	}
	//1 - full expression; 2 - full expression
	else
	{

	}




	*last_success_string_ptr = command_string;
	*was_last_success_if_ptr = true;
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
