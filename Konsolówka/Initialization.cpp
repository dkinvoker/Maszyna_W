#include "Initialization.h"

Assembler_section Initialization::translate()
{
	Assembler_section returner;

	string value;
	string name;

	//int/cha(r)
	name = command_string.substr(0,3);

	if (name == "int")
	{
		//get ID
		int eq_mark_index = command_string.find('=');
		name = command_string.substr(3, eq_mark_index - 3);
		tag_menager_ptr->add(name, variable_int);
		returner.add_data(tag_menager_ptr->get_last_tag(), "RPA", "");
		//Get Initialization value
		value = command_string.substr(eq_mark_index + 1, command_string.size() - eq_mark_index - 2);
		//Adding initialization value
		if (tag_menager_ptr->add_const(value))
		{
			returner.add_data(tag_menager_ptr->get_tag_by_const_value(value), "RST", value);
		}
		
		//Initializing
		returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(value));
		returner.add_program("£AD", tag_menager_ptr->get_tag_by_name(name));

	}
	else
	{
		//get ID
		int eq_mark_index = command_string.find('=');
		name = command_string.substr(4, eq_mark_index - 4);
		tag_menager_ptr->add(name, variable_char);
		returner.add_data(tag_menager_ptr->get_last_tag(), "RPA", "");
		//Get Initialization value
		value = Char_to_asci_code_as_string(command_string[command_string.size() - 3]);
		//Adding initialization value
		if (tag_menager_ptr->add_const(value))
		{
			returner.add_data(tag_menager_ptr->get_tag_by_const_value(value), "RST", value);
		}

		//Initializing
		returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(value));
		returner.add_program("£AD", tag_menager_ptr->get_tag_by_name(name));

	}


	*last_success_string_ptr = command_string;
	*was_last_success_if_ptr = false;
	return returner;
}


Initialization::Initialization(string code)
	:
	Declaration(code)
{
}


//Initialization::Initialization()
//{
//}


Initialization::~Initialization()
{
}
