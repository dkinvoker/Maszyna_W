#include "New_line_expression.h"

Assembler_section New_line_expression::translate()
{
	Assembler_section returner;

	if (tag_menager_ptr->add_const("10"))
	{
		returner.add_data(tag_menager_ptr->get_tag_by_const_value("10"), "RST", "10");
	}

	returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value("10"));
	returner.add_program("WYP", "2");

	*last_success_string_ptr = command_string;
	*was_last_success_if_ptr = false;
	return returner;
}

New_line_expression::New_line_expression(string code)
	:
	Command(code)
{
}


New_line_expression::~New_line_expression()
{
}
