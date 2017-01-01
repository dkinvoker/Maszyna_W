#include "Stop_expression.h"

Assembler_section Stop_expression::translate()
{
	Assembler_section returner;

	returner.add_program("STP", "");

	*last_success_string_ptr = command_string;
	*was_last_success_if_ptr = false;
	return returner;
}

Stop_expression::Stop_expression(string code)
	:
	Command(code)
{
}


Stop_expression::~Stop_expression()
{
}
