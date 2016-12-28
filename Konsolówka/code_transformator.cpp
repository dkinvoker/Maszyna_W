#include "code_transformator.h"


//---------------------------
//OH KURNA to jest mistrzostwo chiñskiego programowania..... 
//string Char_to_asci_code_as_string(char arg_char)
//{
//	int buffer = arg_char;
//	return to_string(buffer);
//}
//---------------------------


void code_transformator::bind_commands()
{
	Command::set_static_tag_menager_ptr(&tag_menager);
	Command::set_last_success_string_ptr(&last_success);
	Command::set_was_last_success_if_ptr(&was_last_success_if);
}


const string code_transformator::get_last_successfully_translated_command()
{
	return last_success;
}

void code_transformator::clear_blank_and_save()
{
	string IN_buffer;
	while (input >> IN_buffer)
	{
		code = code + IN_buffer;
	}
}



void code_transformator::check_syntax()
{

	log_output << "Sprawdzanie sk³adni:\n";
	log_output.flush();


	for (unsigned int x = 0; x < code_sections.size(); x ++)
	{
		string code_selected = code_sections[x].code;
		string buffer;
		log_output << "\tBlok: "<< x << "\n";
		log_output.flush();
		unsigned int box_open = 0;
		unsigned int box_close = 0;
		for (unsigned int i = 0; i < code_selected.size(); i++)
		{
			if (code_selected[i] == '{')
			{
				box_open = i + code_sections[x].begin_index;
				for (unsigned int y = 0; y < box_index.size(); y++)
				{
					if (box_index[y][0] == box_open)
					{
						box_close = box_index[y][1] - code_sections[x].begin_index;
						box_open = box_open;
						break;
					}
				}
				buffer = buffer + code_selected.substr(i, box_close - i + 1);
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


			for (unsigned int j = 0; j < const_regex::all_regex.size(); j++)
			{

				if (regex_match(buffer, const_regex::all_regex[j]))
				{
					//log_output << "\t\t" << buffer << " -> " << j << "\n";
					//log_output.flush();

					//if (j == const_regex::index_char_declaration)
					//{
					//	if (regex_match(buffer, const_regex::regex_char_declaration_and_init))
					//	{
					//		expression_with_consts.push_back(Const_expresion{ buffer, const_regex::index_char_declaration });
					//	}
					//}
					//else if (j == const_regex::index_int_declaration)
					//{
					//	if (regex_match(buffer, const_regex::regex_int_declaration_and_init))
					//	{
					//		expression_with_consts.push_back(Const_expresion{ buffer, const_regex::index_int_declaration });
					//	}
					//}
					//else if (j == const_regex::index_output_expression)
					//{
					//	if (regex_match(buffer, const_regex::regex_output_string))
					//	{
					//		expression_with_consts.push_back(Const_expresion{ buffer, const_regex::index_output_expression });
					//	}
					//}

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
			throw string("\t\tBlok zawiera b³¹d sk³adniowy:\n\t" + buffer + "\n");
		}

		log_output << "\tOK\n\n";
		log_output.flush();
	}

	//---------------------------------------------------

	log_output << "\n Sk³adnia OK \n";
}

void code_transformator::code_into_sections()
{
	int open_number = 0;
	int close_number = 0;

	log_output << "Dzielenie kodu na sekcje:\n";
	log_output.flush();

	for (unsigned int i = 0; i < code.size(); i++)
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
		throw string("\t\tNiepowodzenie: Liczba klamer otwierajacych nie jest równa liczbie klamer zamykajacych\n");
	}

	for (unsigned int i = 0; i < code.size(); i ++)
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
	for (unsigned int i = 0; i < box_index.size(); i ++)
	{
		code_sections.push_back(code_section{ code.substr(box_index[i][0] + 1, box_index[i][1] - box_index[i][0] - 1), box_index[i][0]} );
	}


	//Bez tej pêtli nie dzia³a... chuj wie dlaczego
	for (unsigned int i = 1; i < code_sections.size(); i++)
	{
		code_sections[i].begin_index++;
	}

	log_output << "\t\tOK\n\n";
	log_output.flush();

}

//void code_transformator::catch_consts()
//{
//	log_output << "\n Zbieranie Sta³ych:\n";
//	log_output.flush();
//
//	int start_reading_index = 0;
//	int stop_reading_index = 0;
//	string buffer;
//	string tag_creator;
//
//	for (int i = 0; i < expression_with_consts.size(); i ++)
//	{
//		if (expression_with_consts[i].expression_type == const_regex::index_char_declaration)
//		{
//			
//			if (!const_set.const_exists(expression_with_consts[i].expression_code[expression_with_consts[i].expression_code.size() - 3]))
//			{
//				tag_creator = "t" + to_string(tag_iterator++);
//				data.push_back(W_Assembler_line{ tag_creator, "RST", Char_to_asci_code_as_string (expression_with_consts[i].expression_code[expression_with_consts[i].expression_code.size() - 3]) });
//				const_set.add(data.back());
//
//				log_output 
//					<< "\t"
//					<< expression_with_consts[i].expression_code[expression_with_consts[i].expression_code.size() - 3] 
//					<< " -> "
//					<< data.back().argument
//					<<"\n";
//				log_output.flush();
//
//			}
//			
//
//
//		}
//		else if (expression_with_consts[i].expression_type == const_regex::index_int_declaration)
//		{
//			start_reading_index = expression_with_consts[i].expression_code.find('=') + 1;
//			stop_reading_index = expression_with_consts[i].expression_code.find(';');
//			buffer = expression_with_consts[i].expression_code.substr(start_reading_index, stop_reading_index - start_reading_index);
//
//			if (!const_set.const_exists(stoi(buffer)))
//			{
//				tag_creator = "t" + to_string(tag_iterator++);
//				data.push_back(W_Assembler_line{ tag_creator, "RST", buffer });
//				const_set.add(data.back());
//
//				log_output
//					<< "\t"
//					<< buffer
//					<< "\n";
//				log_output.flush();
//			}
//
//
//		}
//		else if (expression_with_consts[i].expression_type == const_regex::index_output_expression)
//		{
//			start_reading_index = 8;
//			stop_reading_index = expression_with_consts[i].expression_code.size() - 4;
//			//!!!
//		}
//	}
//
//	log_output << "\tOK\n";
//
//}

void code_transformator::adapt_section(Assembler_section &section_to_add)
{
	for (unsigned int i = 0; i < section_to_add.program_assembler_vector.size(); i++)
	{
		program.push_back(section_to_add.program_assembler_vector[i]);
	}
	for (unsigned int i = 0; i < section_to_add.data_assembler_vector.size(); i++)
	{
		data.push_back(section_to_add.data_assembler_vector[i]);
	}
}


void code_transformator::generate_assembler_code()
{
	log_output << "\n Generowanie assemblera:\n";
	this->adapt_section(translate_string(code));
	log_output << "\tOK";
}

void code_transformator::save_one_line_of_assembler_code(W_Assembler_line &line)
{
	assembler_prg_output_file << line.tag << "\t" << line.W_command << "\t" << line.argument << "\n";
}

void code_transformator::save_generated_code()
{
	for (unsigned int i = 0; i < program.size(); i++)
	{
		this->save_one_line_of_assembler_code(program[i]);
	}

	//why i < data.size() - 1??? provents from '\n' at the end of file
	for (unsigned int i = 0; i < data.size() - 1; i++)
	{
		this->save_one_line_of_assembler_code(data[i]);
	}

	//provents from '\n' at the end of file
	assembler_prg_output_file << data[data.size()-1].tag << "\t" << data[data.size() - 1].W_command << "\t" << data[data.size() - 1].argument;
}

void code_transformator::add_stop_at_the_end()
{
	program.push_back( W_Assembler_line{ "", "STP", "" }) ;
}

Tag_menager& code_transformator::get_tag_menager_ref()
{
	return tag_menager;
}

void code_transformator::merge_tags()
{
	log_output << "\nScalanie Etykiet";

	vector<W_Assembler_line> returning_swaping_asembler_line_vector;
	vector<tag_swaps> swaping_tags;

	//detecting swaps
	for (unsigned int i = 0; i < program.size() - 1; i++)
	{
		if (program[i].is_just_tag() && program[i+1].is_just_tag())
		{
			swaping_tags.push_back(tag_swaps{ return_without_last_symbol(program[i].tag), return_without_last_symbol(program[i+1].tag) });
		}
	}

	//reduction
	for (unsigned int i = 0; i < swaping_tags.size(); i ++)
	{
		tag_swaps buffer = swaping_tags[i];
		for (unsigned int j = 0; j < swaping_tags.size(); j++)
		{
			if (swaping_tags[j].swaper == buffer.swaped_tag)
			{
				swaping_tags[j].swaper = buffer.swaper;
			}
		}
	}



	//swaping
	bool copy = true;
	for (unsigned int i = 0; i < program.size(); i++)
	{
		for (unsigned int  j = 0; j < swaping_tags.size(); j++)
		{
			copy = true;
			if (program[i].argument == swaping_tags[j].swaped_tag)
			{
				returning_swaping_asembler_line_vector.push_back(program[i].return_with_swaped_tag(swaping_tags[j].swaper));
				copy = false;
				break;
			}
			else if (program[i].tag == swaping_tags[j].swaped_tag + ":")
			{
				copy = false;
				break;
			}
			
		}
		if (copy)
		{
			returning_swaping_asembler_line_vector.push_back(program[i]);
		}
		
	}


	program = returning_swaping_asembler_line_vector;
	log_output << "\n\tOK";
}


void code_transformator::execute_meta_commands()
{
	log_output << "\nWykonywanie Meta-Rozkazów";

	vector<W_Assembler_line> returning_program;
	W_Assembler_line buffer{"", "", ""};

	for (unsigned int i = 0; i < program.size(); i ++)
	{
		switch (command_to_meta_ID(program[i].W_command))
		{
		case meta_command_ID::REVERSE:

			program[i].W_command = "DELETE";
			buffer = program[i - 1];
			program[i - 1] = program[i + 1];
			program[i + 1] = buffer;

			break;
		case meta_command_ID::DELETE_UP:

			program[i - 1].W_command = "DELETE";
			program[i].W_command = "DELETE";

			break;
		default:
			break;
		}
	}

	for (unsigned int i = 0; i < program.size(); i++)
	{
		if (!(program[i].W_command == "DELETE"))
		{
			returning_program.push_back(program[i]);
		}
	}

	program = returning_program;
	log_output << "\n\tOK";

}

code_transformator::code_transformator(ostream &log_output, ifstream &input, ofstream &output)
	:
	log_output(log_output), input(input), assembler_prg_output_file(output)
{
}


code_transformator::~code_transformator()
{
}
