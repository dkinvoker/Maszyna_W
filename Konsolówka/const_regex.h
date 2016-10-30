#pragma once
#include <string>
#include <regex>
#include <vector>


using namespace std;


namespace const_regex_string
{	
	
	//returns string representing 0 or more the given regex
	string multi_regex_STRING							(string regex_string);
	//returns string representing regex1 or regex2
	string regex_or_regex_STRING						(string regex1, string regex2);
	//returns string containing regex in brackets (character of bracket)
	string regex_in_brackets_characters_STRING			(string regex_string);
	//returns string representing one of the regexes given in vector
	string multi_OR_regex_STRING						(vector<string> alternative_strings);
	//returns string representing regex in box characters
	string regex_in_box_STRING							(string regex_string);
	//returns string representing regex separated by string
	string regex_separation_STRING						(string regex1, string regex2, string separator);
	//returns string representing regex separated by string
	string regex_separation_STRING						(string regex1, string regex2, string regex3, string separator);
	//returns string representing regex surrounded by string
	string regex_surrounded_STRING						(string regex_string, string surrounder);


	const string ID								{ "(([[:alpha:]]|_)([[:w:]]|_)*)" };
	const string arithmetical_symbol			{ "(\\*|\\+|-|\\/)" };
	const string logic_symbol					{ "(<|>|(==)|(!=)|(<=)|(>=))" };
	const string eq								{ "(=)" };
	const string number							{ "([[:digit:]])+" };
	const string ID_or_number					{ regex_or_regex_STRING(ID, number) };
	const string any_code_string				{ "(.*)" };
	const string colon_symbol					{ "\\:" };
	const string semicolon_symbol				{ "\\;" };
	const string quotation_mark_symbol			{ "\"" };
	const string comma_symbol					{ "\\," };

	const string if_string						{ "(if)" };
	const string else_string					{ "(else)" };
	const string while_string					{ "(while)" };
	const string for_string						{ "(for)" };
	const string input_string					{ "(input)" };
	const string output_string					{ "(output)" };
	const string subroutine_string				{ "(sub)" };
	const string start_string					{ "(start)" };
	const string call_string					{ "(call)" };
	const string int_string						{ "(int)" };
	const string char_string					{ "(char)" };
	const string stack_string					{ "(stack)" };
	const string string_string					{ "(string)" };

	const string arithmetical_expression					{ regex_or_regex_STRING (ID_or_number, ID_or_number + multi_regex_STRING(arithmetical_symbol + ID_or_number)) };
	const string logic_expression							{ arithmetical_expression + logic_symbol + arithmetical_expression };
	const string arithmetical_equation						{ ID + eq + arithmetical_expression + semicolon_symbol };

	const string any_code_in_box							{ regex_in_box_STRING(any_code_string) };
	const string logic_condition_and_box					{ regex_in_brackets_characters_STRING(logic_expression) + any_code_in_box };
	const string for_for_logic_expression					{ regex_in_brackets_characters_STRING(arithmetical_equation + logic_expression + semicolon_symbol + arithmetical_equation) };
	const string code_surrounded_by_quotation_marks			{ regex_surrounded_STRING(any_code_string,quotation_mark_symbol) };
	const string string_expression_surrounded_by_brackets	{ regex_in_brackets_characters_STRING(code_surrounded_by_quotation_marks) };
	const string sub_parameters								{ regex_in_brackets_characters_STRING(ID + multi_regex_STRING(comma_symbol + ID)) };
	const string sub_variables_to_call_with					{ regex_separation_STRING(sub_parameters,sub_parameters, colon_symbol) };
	const string ID_in_brackets								{ regex_in_brackets_characters_STRING(ID) };

	const string while_expression_string					{ "(" + while_string + logic_condition_and_box + ")" };
	const string if_expression_string						{ "(" + if_string + logic_condition_and_box + ")" };
	const string else_expression_string						{ "(" + else_string + any_code_in_box + ")" };
	const string for_expression_string						{ "(" + for_string + for_for_logic_expression + any_code_in_box + ")" };
	const string input_expression_string					{ "(" + input_string + ID_in_brackets + ")" };
	const string output_expression_string					{ regex_or_regex_STRING (output_string + string_expression_surrounded_by_brackets, output_string + ID_in_brackets) };
	const string sub_declaration_expression_string			{ "(" + subroutine_string + ID + sub_variables_to_call_with + any_code_in_box + ")" };
	const string sub_call_expression_string					{ "(" + call_string + ID + sub_variables_to_call_with + ")" };
	const string start_expression_string					{ "(" + start_string + colon_symbol + ")" };
	const string stack_expression_string					{ "(" + stack_string + number + semicolon_symbol + ")" };
	const string int_declaration							{ regex_or_regex_STRING(int_string + ID + semicolon_symbol, int_string + ID + eq + number + semicolon_symbol) };
	const string string_declaration							{ regex_or_regex_STRING(string_string + ID + semicolon_symbol, string_string + ID + eq + code_surrounded_by_quotation_marks + semicolon_symbol) };

	const vector<string> all_commands						{ arithmetical_equation, while_expression_string, if_expression_string, else_expression_string, for_expression_string, input_expression_string, output_expression_string, sub_declaration_expression_string, sub_call_expression_string, start_expression_string, stack_expression_string, int_declaration, string_declaration };

	const string syntax_sting								{ multi_regex_STRING(multi_OR_regex_STRING(all_commands)) };

}

namespace const_regex 
{
	using namespace const_regex_string;
	const regex regex_arithmetical_expression	{ arithmetical_expression };
	const regex regex_logic_expression			{ logic_expression };
	const regex regex_arithmetical_equation		{ arithmetical_equation };

	const regex regex_syntax					{ syntax_sting };

}




