#include "Call_expression.h"


void Call_expression::extract_variables()
{
	string buffer;
	string first_variable_string;
	string secound_variable_string;
	unsigned int first_index = find_first_braced(command_string) + 1;

	for (unsigned int i = first_index; i < command_string.size(); i++)
	{
		if (command_string[i] != ')')
		{
			buffer += command_string[i];
			continue;
		}
		first_index = i + 3;
		break;
	}

	first_variable_string = buffer;
	buffer.clear();

	for (unsigned int i = first_index; i < command_string.size(); i++)
	{
		if (command_string[i] != ')')
		{
			buffer += command_string[i];
			continue;
		}
		break;
	}
	secound_variable_string = buffer;
	buffer.clear();

	if (first_variable_string.size() != 0)
	{
		for (unsigned int i = 0; i < first_variable_string.size(); i++)
		{
			if (first_variable_string[i] == ',')
			{
				input_variables.push_back(buffer);
				buffer.clear();
				continue;
			}
			buffer += first_variable_string[i];
		}
		input_variables.push_back(buffer);
	}

	buffer.clear();

	if (secound_variable_string.size() != 0)
	{
		for (unsigned int i = 0; i < secound_variable_string.size(); i++)
		{
			if (secound_variable_string[i] == ',')
			{
				output_variables.push_back(buffer);
				buffer.clear();
				continue;
			}
			buffer += secound_variable_string[i];
		}
		output_variables.push_back(buffer);
	}
}

void Call_expression::extract_name()
{
	unsigned int starting_index = 4;
	for (unsigned int i = starting_index; i < command_string.size(); i++)
	{
		if (command_string[i] == '(')
		{
			break;
		}
		name += command_string[i];
	}
}

Assembler_section Call_expression::translate()
{
	Assembler_section returner;
	

	extract_name();
	extract_variables();
	sub_and_parameters params = sub_menager_ptr->get_parmeters_by_name(name);

	if (input_variables.size() != params.input_parameters.size())
	{
		throw string("Próba wywo³ania " + name + " z niew³aœciw¹ liczb¹ paramatrów wejœcia");
	}
	if (output_variables.size() != params.output_parameters.size())
	{
		throw string("Próba wywo³ania '" + name + "' z niew³aœciw¹ liczb¹ paramatrów wyjœcia");
	}

	//!!!!!!!!!!!!!!!!!!!!!! Rzucanie paramsów poprzedniego wywo³ania
	for (unsigned int i = 0; i < params.input_parameters.size(); i ++)
	{
		returner.add_program("POB", tag_menager_ptr->get_tag_by_name(params.input_parameters[i]));
		returner.add_program("DNS", "");
	}
	//!!!!!!!!!!!!!!!!!!!!!!

	for (unsigned int i = 0; i < input_variables.size(); i ++)
	{
		returner.add_program("POB", tag_menager_ptr->get_tag_by_name(input_variables[i]));
		returner.add_program("DNS", "");
	}


	returner.add_program("SDP", tag_menager_ptr->get_tag_by_name(name));

	for (unsigned int i = 0; i < output_variables.size(); i++)
	{
		returner.add_program("PZS", "");
		returner.add_program("£AD", tag_menager_ptr->get_tag_by_name(output_variables[output_variables.size() - 1 - i]));
	}

	*last_success_string_ptr = command_string;
	*was_last_success_if_ptr = false;
	return returner;
}


Call_expression::Call_expression(string code)
	:
	Command(code)
{
}


Call_expression::~Call_expression()
{
}
