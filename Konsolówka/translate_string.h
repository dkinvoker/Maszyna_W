#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "const_regex.h"
#include <vector>
#include "Struct_header.h"
#include "Command.h"
//#include "Declaration.h"
//#include "Initialization.h"
//#include "equation.h"
//
//using namespace std;
//


//inline int which_command(string &arg_string)
//{
//	for (int i = 0; i < const_regex::all_regex.size(); i ++)
//	{
//		if (regex_match(arg_string, const_regex::all_regex[i]))
//		{
//			return i;
//		}
//	}
//
//	//incorrect command
//	return -1;
//
//}
//
//inline void adapt_section(Assembler_section &adaptiong_section, Assembler_section &section_to_adapt)
//{
//	for (int i = 0; i < section_to_adapt.program_assembler_vector.size(); i++)
//	{
//		adaptiong_section.program_assembler_vector.push_back(section_to_adapt.program_assembler_vector[i]);
//	}
//	for (int i = 0; i < section_to_adapt.data_assembler_vector.size(); i++)
//	{
//		adaptiong_section.data_assembler_vector.push_back(section_to_adapt.data_assembler_vector[i]);
//	}
//}


//Assembler_section translate_string (const string &arg_string)
//{
//	string buffer;
//	unsigned int how_many_bracked_symbol = 0;
//	vector<Command*> object_to_translate_ptr_vector;
//	Assembler_section returner;
//
//	try
//	{
//
//		for (int i = 0; i < arg_string.size(); i++)
//		{
//			buffer += arg_string[i];
//
//			if (arg_string[i] == '{')
//			{
//				how_many_bracked_symbol++;
//			}
//
//			if (arg_string[i] == '}')
//			{
//				how_many_bracked_symbol--;
//			}
//
//			if (how_many_bracked_symbol == 0)
//			{
//
//
//				switch (which_command(buffer))
//				{
//				case const_regex::index_int_declaration:
//
//					if (regex_match(buffer, const_regex::regex_int_declaration_no_init))
//					{
//						object_to_translate_ptr_vector.push_back(new Declaration( buffer ));
//					}
//					else
//					{
//						object_to_translate_ptr_vector.push_back(new Initialization( buffer ));
//					}
//
//					buffer.clear();
//
//					break;
//				case const_regex::index_arithmetical_equation:
//
//					object_to_translate_ptr_vector.push_back(new Equation( buffer ));
//					buffer.clear();
//
//					break;
//				case const_regex::index_while_expression:
//					buffer.clear();
//					throw "Tego jeszcze nie zaimplementowalem";
//					break;
//				case const_regex::index_if_expression:
//					buffer.clear();
//					throw "Tego jeszcze nie zaimplementowalem";
//					break;
//				case const_regex::index_else_expression:
//					buffer.clear();
//					throw "Tego jeszcze nie zaimplementowalem";
//					break;
//				case const_regex::index_for_expression:
//					buffer.clear();
//					throw "Tego jeszcze nie zaimplementowalem";
//					break;
//				case const_regex::index_input_expression:
//					buffer.clear();
//					throw "Tego jeszcze nie zaimplementowalem";
//					break;
//				case const_regex::index_output_expression:
//					buffer.clear();
//					throw "Tego jeszcze nie zaimplementowalem";
//					break;
//				case const_regex::index_sub_declaration:
//					buffer.clear();
//					throw "Tego jeszcze nie zaimplementowalem";
//					break;
//				case const_regex::index_sub_call:
//					buffer.clear();
//					throw "Tego jeszcze nie zaimplementowalem";
//					break;
//				case const_regex::index_start:
//					buffer.clear();
//					throw "Tego jeszcze nie zaimplementowalem";
//					break;
//				case const_regex::index_stack:
//					buffer.clear();
//					throw "Tego jeszcze nie zaimplementowalem";
//					break;
//				case const_regex::index_char_declaration:
//
//					if (regex_match(buffer, const_regex::regex_char_declaration_no_init))
//					{
//						object_to_translate_ptr_vector.push_back(new Declaration( buffer ));
//					}
//					else
//					{
//						object_to_translate_ptr_vector.push_back(new Initialization( buffer ));
//					}
//					buffer.clear();
//
//
//					break;
//				case const_regex::index_return:
//					buffer.clear();
//					throw "Tego jeszcze nie zaimplementowalem";
//					break;
//				case const_regex::index_stop:
//					buffer.clear();
//					throw "Tego jeszcze nie zaimplementowalem";
//					break;
//				case const_regex::index_comment:
//					buffer.clear();
//					throw "Tego jeszcze nie zaimplementowalem";
//					break;
//
//
//				default:
//					break;
//				}
//			}
//
//		}
//
//	}
//	catch (string &Error)
//	{
//		for (int i = 0; i < object_to_translate_ptr_vector.size(); i ++)
//		{
//			delete object_to_translate_ptr_vector[i];
//		}
//		throw Error;
//	}
//
//
//
//
//
//
//	for (int i = 0; i < object_to_translate_ptr_vector.size(); i++)
//	{
//		adapt_section(returner, object_to_translate_ptr_vector[i]->translate());
//		delete object_to_translate_ptr_vector[i];
//	}
//	return returner;
//
//}
