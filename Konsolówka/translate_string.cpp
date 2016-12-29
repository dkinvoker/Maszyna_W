#include "translate_string.h"
#include "Command.h"
#include "Declaration.h"
#include "Initialization.h"
#include "equation.h"
#include "If_expression.h"
#include "Else_expression.h"
#include "While_expression.h"
#include "For_expression.h"
#include "Start_command.h"
#include "Output_expression.h"

Assembler_section translate_string(const string &arg_string)
{
	string buffer;
	unsigned int how_many_bracked_symbol = 0;
	vector<Command*> object_to_translate_ptr_vector;
	Assembler_section returner;

	try
	{

		for (unsigned int i = 0; i < arg_string.size(); i++)
		{
			buffer += arg_string[i];

			if (arg_string[i] == '{')
			{
				how_many_bracked_symbol++;
			}

			if (arg_string[i] == '}')
			{
				how_many_bracked_symbol--;
			}

			if (how_many_bracked_symbol == 0)
			{


				switch (which_command(buffer))
				{
				case const_regex::index_int_declaration:

					if (regex_match(buffer, const_regex::regex_int_declaration_no_init))
					{
						object_to_translate_ptr_vector.push_back(new Declaration{ buffer });
					}
					else
					{
						object_to_translate_ptr_vector.push_back(new Initialization{ buffer });
					}

					buffer.clear();

					break;
				case const_regex::index_arithmetical_equation:

					object_to_translate_ptr_vector.push_back(new Equation{ buffer });
					buffer.clear();

					break;
				case const_regex::index_while_expression:

					object_to_translate_ptr_vector.push_back(new While_expression{ buffer });
					buffer.clear();

					break;
				case const_regex::index_if_expression:
					
					object_to_translate_ptr_vector.push_back(new If_expression{ buffer });
					buffer.clear();
					
					break;
				case const_regex::index_else_expression:

					object_to_translate_ptr_vector.push_back(new Else_expression{ buffer });
					buffer.clear();

					break;
				case const_regex::index_for_expression:

					object_to_translate_ptr_vector.push_back(new For_expression{ buffer });
					buffer.clear();

					break;
				case const_regex::index_input_expression:
					buffer.clear();
					throw string("Tego jeszcze nie zaimplementowalem");
					break;
				case const_regex::index_output_expression:

					object_to_translate_ptr_vector.push_back(new Output_expression{ buffer });
					buffer.clear();

					break;
				case const_regex::index_sub_declaration:
					buffer.clear();
					throw string("Tego jeszcze nie zaimplementowalem");
					break;
				case const_regex::index_sub_call:
					buffer.clear();
					throw string("Tego jeszcze nie zaimplementowalem");
					break;
				case const_regex::index_start:

					object_to_translate_ptr_vector.push_back(new Start_command{ buffer });
					buffer.clear();

					break;
				case const_regex::index_char_declaration:

					if (regex_match(buffer, const_regex::regex_char_declaration_no_init))
					{
						object_to_translate_ptr_vector.push_back(new Declaration(buffer));
					}
					else
					{
						object_to_translate_ptr_vector.push_back(new Initialization(buffer));
					}
					buffer.clear();


					break;
				case const_regex::index_return:
					buffer.clear();
					throw string("Tego jeszcze nie zaimplementowalem");
					break;
				case const_regex::index_stop:
					buffer.clear();
					throw string("Tego jeszcze nie zaimplementowalem");
					break;
				case const_regex::index_comment:
					buffer.clear();
					throw string("Tego jeszcze nie zaimplementowalem");
					break;


				default:
					break;
				}
			}

		}

	}
	catch (string &Error)
	{
		for (unsigned int i = 0; i < object_to_translate_ptr_vector.size(); i++)
		{
			delete object_to_translate_ptr_vector[i];
		}
		throw Error;
	}




	for (unsigned int i = 0; i < object_to_translate_ptr_vector.size(); i++)
	{
		adapt_section(returner, object_to_translate_ptr_vector[i]->translate());
		delete object_to_translate_ptr_vector[i];
	}
	return returner;

}

