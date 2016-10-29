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
	string regex_in_brackets_character_STRING			(string regex_string);
	//returns string representing one of the regexes given in vector
	string multi_regex_og_regex_STRING					(vector<string> alternative_strings);
	//returns string representing regex in box characters
	string regex_in_box_STRING							(string regex_string);


	const string ID								{ "([[:alpha:]][[:w:]]*)" };
	const string arithmetical_symbol			{ "(\\*|\\+|-|\\/)" };
	const string logic_symbol					{ "(<|>|(==)|(!=)|(<=)|(>=))" };
	const string eq								{ "(=)" };
	const string number							{ "([[:digit:]])+" };
	const string ID_or_number					{ regex_or_regex_STRING(ID, number) };

	const string if_string						{ "(if)" };
	const string else_string					{ "(else)" };
	const string while_string					{ "(while)" };
	const string for_string						{ "(for)" };
	const string input_string					{ "(input)" };
	const string output_string					{ "(output)" };
	const string subroutine_string				{ "(sub)" };
	const string start_string					{ "(start)" };
	const string call_string					{ "(call)" };

	const string arithmetical_expression		{ regex_or_regex_STRING (ID_or_number, ID_or_number + multi_regex_STRING(arithmetical_symbol + ID_or_number)) };
	const string logic_expression				{ arithmetical_expression + logic_symbol + arithmetical_expression };
	const string arithmetical_equation			{ ID + eq + arithmetical_expression };

}

namespace const_regex 
{
	using namespace const_regex_string;
	const regex regex_arithmetical_expression	{ arithmetical_expression };
	const regex regex_logic_expression			{ logic_expression };
	const regex regex_arithmetical_equation		{ arithmetical_equation };

}




