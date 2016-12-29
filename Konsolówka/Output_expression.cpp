#include "Output_expression.h"
#include "Struct_header.h"

void Output_expression::extract_ID()
{
	ID_or_string_to_output = command_string.substr(7, command_string.size() - 9);
}

void Output_expression::extract_string()
{
	ID_or_string_to_output = command_string.substr(8, command_string.size() - 11);
}


Assembler_section Output_expression::translate()
{
	Assembler_section returner;
	

	if (regex_match(command_string, const_regex::output_ID))
	{
		extract_ID();
		if (tag_menager_ptr->get_type_by_name(ID_or_string_to_output) == Tag_type::variable_char)
		{
			returner.add_program("POB", tag_menager_ptr->get_tag_by_name(ID_or_string_to_output));
			returner.add_program("WYP", "2");
		}
		//czyli, ¿e INT
		else
		{
			returner.add_meta_command("GENERATE_OUTPUT");
			returner.add_program("POB", tag_menager_ptr->get_tag_by_name(ID_or_string_to_output));
			returner.add_program("DNS", "");
			returner.add_program("SDP", "mOI");
		}
	}
	else
	{
		string value;
		extract_string();

		for (int i = 0; i < ID_or_string_to_output.size(); i++)
		{
			value = Char_to_asci_code_as_string(ID_or_string_to_output[i]);
			if (tag_menager_ptr->add_const(value))
			{
				returner.add_data(tag_menager_ptr->get_tag_by_const_value(value), "RST", value);
			}
			returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(value));
			returner.add_program("WYP", "2");
		}
	}



	*last_success_string_ptr = command_string;
	*was_last_success_if_ptr = false;
	return returner;
}


Output_expression::Output_expression(string code)
	:
	Command(code)
{
}

Output_expression::~Output_expression()
{
}
