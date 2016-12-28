#include "While_expression.h"
#include "translate_string.h"



Assembler_section While_expression::translate()
{
	Assembler_section returner;
	string return_tag_string;

	//¿eby ucina³o literki...
	//while -> le (2 literki jak w if'ie, ¿eby sie dobrze translatowa³o)
	If_expression helper{ command_string.substr(3, command_string.size() - 3) };

	tag_menager_ptr->add_next_jump_tag();
	return_tag_string = tag_menager_ptr->get_last_jump_tag();
	returner.add_program(return_tag_string, "", "");
	
	adapt_section(returner, helper.translate());
	returner.add_meta_command("REVERSE");
	returner.add_program("SOB", return_tag_string);


	*last_success_string_ptr = command_string;
	*was_last_success_if_ptr = true;
	return returner;
}





While_expression::While_expression(string code)
	:
	If_expression(code)
{
}


While_expression::~While_expression()
{
}
