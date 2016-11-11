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

	if (box_close_index.size() != box_open_index.size())
	{
		log_output << "inna liczba klamer zamykajacych i otwierajacych";
		return false;
	}


	int size_memory = box_open_index.size();
	for (int i = 0; i < size_memory; i ++)
	{
		section = code.substr(box_open_index.front() + 1 , box_close_index.top() - box_open_index.front() - 1);
		if (!regex_match(section,const_regex::regex_syntax)) 
		{
			log_output << "Blok "<< i << "zawiera blad skladniowy";
			return false;
		}
		box_open_index.pop();
		box_close_index.pop();
	}



	return true;
}

code_transformator::code_transformator()
{
}


code_transformator::~code_transformator()
{
}
