#include "Declaration.h"





Assembler_section Declaration::translate()
{
	Assembler_section returner;

	string buffer;
	string tag;
	buffer = command_string.substr(0, 3);

	//int/cha(r)
	if (buffer == "int")
	{
		//get ID
		buffer = command_string.substr(3, command_string.size() -4);
		tag_menager_ptr->add(buffer, variable_int);
		returner.add_data(tag_menager_ptr->get_last_tag(), "RPA", "");

	}
	else
	{
		//get ID
		buffer = command_string.substr(4, command_string.size() - 5);
		tag_menager_ptr->add(buffer, variable_char);
		returner.add_data(tag_menager_ptr->get_last_tag(), "RPA", "");
	}



	*last_success_string_ptr = command_string;
	*was_last_success_if_ptr = false;
	return returner;
}

Declaration::Declaration(string code)
	:
	Command(code)
{
}

//Declaration::Declaration()
//{
//}

Declaration::~Declaration()
{
}



