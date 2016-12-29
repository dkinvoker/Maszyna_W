#include "For_expression.h"
#include "equation.h"
#include "translate_string.h"


void For_expression::extract_for_expression_steps()
{
	string buffer;
	string cut_buffer;

	//first bracket always czwarty!
	unsigned int first_bracket_symbol_index = 4;
	unsigned int second_bracket_symbol_index;
	bool first_semicolon_caught = false;
	bool secound_semicolon_caught = false;

	for (unsigned int i = 0; command_string.size(); i++)
	{
		if (command_string[i] == ')')
		{
			second_bracket_symbol_index = i;
			break;
		}
	}

	buffer = command_string.substr(first_bracket_symbol_index, second_bracket_symbol_index - 4);

	//+2 bo... cza omin¹æ "{"
	code_to_execute = command_string.substr(second_bracket_symbol_index + 2, command_string.size() - 3 - second_bracket_symbol_index);

	for (unsigned int i = 0; i < buffer.size(); i++)
	{
		if (buffer[i] == ';')
		{
			if (!first_semicolon_caught)
			{
				initialization_equation_string = cut_buffer + ';';
				first_semicolon_caught = true;
				cut_buffer.clear();
			}
			else if (!secound_semicolon_caught)
			{
				conditional_expression = cut_buffer;
				step_equation_string = buffer.substr(i + 1, buffer.size() - i - 1) + ';';
				break;
			}
		}
		else
		{
			cut_buffer += buffer[i];
		}
		
	}

}


Assembler_section For_expression::translate()
{
	Assembler_section returner;

	string retuning_tag;
	string if_end_jumping_tag;
	
	this->extract_for_expression_steps();

	Equation initialization_equation{ initialization_equation_string };
	Equation step_equation{ step_equation_string };
	If_expression main_box{ "if(" + conditional_expression + "){" + code_to_execute +"}" };

	adapt_section(returner, initialization_equation.translate());
	tag_menager_ptr->add_next_jump_tag();
	retuning_tag = tag_menager_ptr->get_last_jump_tag();
	returner.add_program(retuning_tag, "", "");
	adapt_section(returner, main_box.translate());

	//geting importand tag O_o
	if_end_jumping_tag = returner.program_assembler_vector[returner.program_assembler_vector.size() - 1].tag.substr(0, returner.program_assembler_vector[returner.program_assembler_vector.size() - 1].tag.size() - 1);

	returner.add_meta_command("DELETE_UP");
	adapt_section(returner, step_equation.translate());
	returner.add_program("SOB", retuning_tag);
	returner.add_program(if_end_jumping_tag, "", "");


	*last_success_string_ptr = command_string;
	*was_last_success_if_ptr = false;
	return returner;
}

For_expression::For_expression(string code)
	:
	If_expression(code)
{
}

//For_expression::For_expression()
//{
//}


For_expression::~For_expression()
{
}
