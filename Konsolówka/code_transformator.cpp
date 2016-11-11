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
	log_output << "Sprawdzanie skladni:\n";

	if (!regex_match(code, const_regex::regex_syntax))
	{
		log_output << "\tBlok glowny zawiera blad skladniowy\n";
		return false;
	}
	for (unsigned long long int i = 0; i < code.size(); i ++)
	{
		if (code[i] == '{')
		{
			box_index.push_back({i,0});
		}
		if (code[i] == '}')
		{
			for (int j = box_index.size() - 1; j > -1; j--)
			{
				if (box_index[j][1] == 0)
				{
					box_index[j][1] = i;
					break;
				}
			}
		}

	}


	for (int i = 0; i < box_index.size(); i ++)
	{
		section = code.substr(box_index[i][0] + 1, box_index[i][1] - box_index[i][0] - 1);
		if (!regex_match(section,const_regex::regex_syntax)) 
		{
			log_output << "\tBlok "<< i + 1 << " zawiera blad skladniowy\n";
			return false;
		}
	}

	for (int i = 0; i < box_index.size(); i++)
	{
		if (box_index[i][1] == 0)
		{
			log_output << "\tNierowna liczba klamerek zamykajacych i otwierajacych\n";
			return false;
		}
	}

	log_output << "\t OK \n";
	return true;
}

code_transformator::code_transformator()
{
}


code_transformator::~code_transformator()
{
}
