#include "code_transformator.h"


void code_transformator::clear_blank_and_save()
{
	string IN_buffer;
	while (input >> IN_buffer)
	{
		code = code + IN_buffer;
	}
}





bool code_transformator::check_syntax()
{

	log_output << "Sprawdzanie sk³adni:\n";
	log_output.flush();


	for (int x = 0; x < code_sections.size(); x ++)
	{
		string code_selected = code_sections[x].code;
		string buffer;
		log_output << "\tBlok: "<< x << "\n";
		log_output.flush();
		unsigned long long int box_open = 0;
		unsigned long long int box_close = 0;
		for (int i = 0; i < code_selected.size(); i++)
		{
			if (code_selected[i] == '{')
			{
				box_open = i;
				for (int y = 0; y < box_index.size(); y++)
				{
					if (box_index[y][0] == box_open + code_sections[x].begin_index)
					{
						box_close = box_index[y][1] - code_sections[x].begin_index;
						break;
					}
				}
				buffer = buffer + code_selected.substr(box_open, box_close - box_open);
			}
			else
			{
				buffer = buffer + code_selected[i];
			}


			//if (regex_match(buffer, const_regex::regex_all_commands))
			//{

			//	if (box_open != 0)
			//	{
			//		i = box_close;
			//		box_open = 0;
			//	}

			//	buffer.clear();
			//	break;
			//}


			for (int j = 0; j < const_regex::all_regex.size(); j++)
			{

				if (regex_match(buffer, const_regex::all_regex[j]))
				{
					//log_output << "\t\t" << buffer << " -> " << j << "\n";
					log_output.flush();

					if (j == const_regex::index_char_declaration)
					{
						if (regex_match(buffer, const_regex::regex_char_declaration_and_init))
						{
							expression_with_consts.push_back(buffer);
						}
					}
					else if (j == const_regex::index_int_declaration)
					{
						if (regex_match(buffer, const_regex::regex_int_declaration_and_init))
						{
							expression_with_consts.push_back(buffer);
						}
					}

					if (box_open != 0)
					{
						i = box_close;
						box_open = 0;
					}

					buffer.clear();
					break;
				}
			}

		}

		if (!buffer.empty())
		{
			log_output << "\t\tBlok zawiera b³¹d sk³adniowy:\n\t" << buffer << "\n";
			log_output.flush();
			return false;
		}

		log_output << "\tOK\n\n";
		log_output.flush();
	}

	//---------------------------------------------------

	log_output << "\n Sk³adnia OK \n";
	return true;
}

bool code_transformator::code_into_sections()
{
	int open_number = 0;
	int close_number = 0;

	log_output << "Dzielenie kodu na sekcje\n";
	log_output.flush();

	for (int i = 0; i < code.size(); i++)
	{
		if (code[i] == '{')
		{
			open_number++;
		}
		if (code[i] == '}')
		{
			close_number++;
		}
	}

	if (open_number != close_number)
	{
		log_output << "\t\tNiepowodzenie: Liczba klamer otwierajacych nie jest równa liczbie klamer zamykajacych\n";
		log_output.flush();
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


	code_sections.push_back(code_section{code,0});
	for (int i = 0; i < box_index.size(); i ++)
	{
		code_sections.push_back(code_section{ code.substr(box_index[i][0] + 1, box_index[i][1] - box_index[i][0] - 1), box_index[i][0]} );
	}


	//Bez tej pêtli nie dzia³a... chuj wie dlaczego
	for (int i = 1; i < code_sections.size(); i++)
	{
		code_sections[i].begin_index++;
	}

	log_output << "\t\tOK\n\n";
	log_output.flush();

	return true;
}

void code_transformator::catch_consts()
{
	log_output << "\n Zbieranie Sta³ych:\n";
	log_output.flush();


}


code_transformator::code_transformator(ostream &log_output, ifstream &input, ofstream &output)
	:
	log_output(log_output), input(input), assembler_prg_output_file(output)
{
}


code_transformator::~code_transformator()
{
}
