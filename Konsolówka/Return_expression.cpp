#include "Return_expression.h"

Assembler_section Return_expression::translate()
{
	Assembler_section returner;

	if (*inside_sub_declaration == false)
	{
		throw string("S³owo kluczowe 'return' mo¿e wystêpowaæ jedynie wewn¹trz bloku 'sub'");
	}

	string name = sub_menager_ptr->get_translating_now();
	string returning_tag = "0" + name + "PWR";
	sub_and_parameters params = sub_menager_ptr->get_parmeters_by_name(name);

	returner.add_program("PZS", "");
	returner.add_program("£AD", tag_menager_ptr->get_tag_by_name(returning_tag));

	////!!!!!!!!!!!!!!!!!! store params 0
	//for (unsigned int i = 0; i < params.input_parameters.size(); i ++)
	//{
	//	returner.add_program("PZS", "");
	//	returner.add_program("£AD", tag_menager_ptr->get_tag_by_name("0" + params.input_parameters[params.input_parameters.size() -1 - i]));
	//}

	////!!!!!!!!!!!!!!!!!!



	for (unsigned int i = 0; i < params.output_parameters.size(); i ++)
	{
		returner.add_program("POB", tag_menager_ptr->get_tag_by_name(params.output_parameters[i]));
		returner.add_program("DNS", "");
	}

	////!!!!!!!!!!!!!!!!! Rzuæ output rzuæ params

	//for (unsigned int i = 0; i < params.input_parameters.size(); i++)
	//{
	//	returner.add_program("POB", tag_menager_ptr->get_tag_by_name("0" + params.input_parameters[params.input_parameters.size() - 1 - i]));
	//	returner.add_program("DNS", "");
	//	
	//}

	//for (unsigned int i = 0; i < params.input_parameters.size(); i++)
	//{
	//	returner.add_program("PZS", "");
	//	returner.add_program("£AD", tag_menager_ptr->get_tag_by_name(params.input_parameters[i]));

	//}

	////!!!!!!!!!!!!!!!!!

	returner.add_program("POB", tag_menager_ptr->get_tag_by_name(returning_tag));
	returner.add_program("DNS", "");
	returner.add_program("PWR", "");

	*last_success_string_ptr = command_string;
	*was_last_success_if_ptr = false;
	return returner;
}


Return_expression::Return_expression(string code)
	:
	Command(code)
{
}


Return_expression::~Return_expression()
{
}
