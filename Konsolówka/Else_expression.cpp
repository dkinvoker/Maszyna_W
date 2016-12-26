#include "Else_expression.h"
#include "translate_string.h"

Assembler_section Else_expression::translate()
{
	Assembler_section returner;
	string tag_to_the_else_end;
	if (*was_last_success_if_ptr == false)
	{
		throw string("S³owo kluczowe 'else' nie mo¿e wystêpowaæ samodzielnie");
	}

	//Must to skip '{', '}' and 'else'
	code_to_execute = command_string.substr(5, command_string.size() - 6);

	returner.add_meta_command("REVERSE");
	tag_menager_ptr->add_next_jump_tag();
	tag_to_the_else_end = tag_menager_ptr->get_last_jump_tag();
	returner.add_program("SOB", tag_to_the_else_end);
	adapt_section(returner, translate_string(code_to_execute));
	returner.add_program(tag_to_the_else_end, "", "");

	*last_success_string_ptr = command_string;
	*was_last_success_if_ptr = false;
	return returner;
}

Else_expression::Else_expression(string code)
	:
	Command(code)
{
}

Else_expression::~Else_expression()
{
}
