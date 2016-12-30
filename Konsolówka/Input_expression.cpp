#include "Input_expression.h"

void Input_expression::extract_ID()
{
	ID = command_string.substr(6, command_string.size() - 8);
}

Assembler_section Input_expression::translate()
{
	Assembler_section returner;

	extract_ID();


	if (tag_menager_ptr->get_type_by_name(ID) == Tag_type::variable_char)
	{
		returner.add_program("WPR", "1");
		returner.add_program("£AD", tag_menager_ptr->get_tag_by_name(ID));
	}
	//czyli, ¿e int 
	else
	{
		returner.add_meta_command("GENERATE_INPUT");
		returner.add_program("SDP", "mII");
		returner.add_program("PZS", "");
		returner.add_program("£AD", tag_menager_ptr->get_tag_by_name(ID));

	}



	*last_success_string_ptr = command_string;
	*was_last_success_if_ptr = false;
	return returner;
}

Input_expression::Input_expression(string code)
	:
	Command(code)
{
}

Input_expression::~Input_expression()
{
}
