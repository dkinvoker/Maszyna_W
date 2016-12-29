#pragma once
#include "Command.h"
class Start_command :
	public Command
{
public:

	Assembler_section translate()
	{
		Assembler_section returner;
		returner.add_meta_command("START");

		*last_success_string_ptr = command_string;
		*was_last_success_if_ptr = false;
		return returner;
	}

	Start_command(string code)
		:
		Command(code)
	{
	}

	Start_command() = delete;

	~Start_command()
	{
	}
};

