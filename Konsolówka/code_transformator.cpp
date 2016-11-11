#include "code_transformator.h"


void code_transformator::clear_blank_and_save(ifstream &input)
{
	string IN_buffer;
	while (input >> IN_buffer)
	{
		code = code + IN_buffer;
	}
}



bool code_transformator::check_syntax(ostream &log_output)
{
	string section;
	if (!regex_match(code, const_regex::regex_syntax))
	{
		log_output << "Blok glowny zawiera blad skladniowy";
		return false;
	}
	for (unsigned long long int i = 0; i < code.size(); i ++)
	{
		if (code[i] == '{')
		{
			box_open_index.push(i);
		}
		if (code[i] == '}')
		{
			box_close_index.push(i);
		}
	}




	return true;
}

code_transformator::code_transformator()
{
}


code_transformator::~code_transformator()
{
}
