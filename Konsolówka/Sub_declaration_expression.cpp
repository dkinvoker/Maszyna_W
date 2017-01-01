#include "Sub_declaration_expression.h"
#include "translate_string.h"



void Sub_declaration_expression::extract_code_to_execute()
{
	unsigned int first_box_symbol;
	for (unsigned int i = 0; i < command_string.size(); i++)
	{
		if (command_string[i] == '{')
		{
			first_box_symbol = i;
			break;
		}
	}

	code_to_execute = command_string.substr(first_box_symbol + 1, command_string.size() - first_box_symbol - 2);
}

void Sub_declaration_expression::extract_name()
{
	unsigned int starting_index = 3;
	for (unsigned int i = starting_index; i < command_string.size(); i++)
	{
		if (command_string[i] == '(')
		{
			break;
		}
		name += command_string[i];
	}
}


void Sub_declaration_expression::extract_variables()
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


Assembler_section Sub_declaration_expression::translate()
{
	
	Assembler_section returner;
	extract_variables();
	extract_code_to_execute();
	extract_name();
	sub_menager_ptr->register_variables(name, input_variables, output_variables);

	string returning_memory_tag = "0" + name + "PWR";

	if (*inside_sub_declaration == true)
	{
		throw string("Nie mo¿na deklarowaæ podprogramów, w innych podprogramach");
	}
	*inside_sub_declaration = true;
	sub_menager_ptr->set_translating_now(name);

	tag_menager_ptr->add(name, Tag_type::sub);
	returner.add_program(tag_menager_ptr->get_tag_by_name(name), "", "");
	tag_menager_ptr->add( returning_memory_tag, Tag_type::meta_tag);
	returner.add_data(tag_menager_ptr->get_tag_by_name(returning_memory_tag), "RPA", "");
	returner.add_program("PZS", "");
	returner.add_program("£AD", tag_menager_ptr->get_tag_by_name(returning_memory_tag));


	for (unsigned int i = 0; i < input_variables.size(); i ++)
	{
		if (tag_menager_ptr->find_by_name(input_variables[i]) == nullptr)
		{
			tag_menager_ptr->add(input_variables[i], Tag_type::variable_int);
			returner.add_data(tag_menager_ptr->get_tag_by_name(input_variables[i]), "RPA", "");


			
		}
	}

	for (unsigned int i = 0; i < output_variables.size(); i ++ )
	{
		if (tag_menager_ptr->find_by_name(output_variables[i]) == nullptr)
		{
			tag_menager_ptr->add(output_variables[i], Tag_type::variable_int);
			returner.add_data(tag_menager_ptr->get_tag_by_name(output_variables[i]), "RPA", "");

			
		}
	}

	for (unsigned int i = 0; i < input_variables.size(); i ++)
	{
		returner.add_program("PZS", "");
		returner.add_program("£AD", tag_menager_ptr->get_tag_by_name(input_variables[input_variables.size() - 1 - i]));
	}



	returner.add_program("POB", tag_menager_ptr->get_tag_by_name(returning_memory_tag));
	returner.add_program("DNS", "");

	adapt_section(returner, translate_string(code_to_execute));

	*inside_sub_declaration = false;
	*last_success_string_ptr = command_string;
	*was_last_success_if_ptr = false;
	return returner;
}


Sub_declaration_expression::Sub_declaration_expression(string code)
	:
	Command(code)
{
}


Sub_declaration_expression::~Sub_declaration_expression()
{
}
