#pragma once
#include <string>
#include <regex>


using namespace std;


namespace const_regex_string
{	
	
	
	string multi_regex_string(string regex_string);
	string regex_or_regex(string regex1, string regex2);


	const string ID								{ "([[:alpha:]][[:w:]]*)" };
	const string arithmetical_symbol			{ "(\\*|\\+|-|\\/)" };
	const string logic_symbol					{ "(<|>|(==)|(!=)|(<=)|(>=))" };
	const string eq								{ "(=)" };
	const string digit							{ "([[:digit:]])" };
	const string ID_or_digit					{ regex_or_regex(ID, digit) };

	const string if_string						{ "if" };
	const string else_string					{ "else" };
	const string while_string					{ "while" };
	const string for_string						{ "for" };
	const string input_string					{ "input" };
	const string output_string					{ "output" };
	const string subroutine_string				{ "subroutine" };


	const string arithmetical_expression		{ ID_or_digit + multi_regex_string(arithmetical_symbol + ID_or_digit) };
	const string logic_expression				{ ID_or_digit + logic_symbol + arithmetical_expression };
	const string arithmetical_equation			{ ID + eq + arithmetical_expression };

}

namespace const_regex 
{
	using namespace const_regex_string;
	const regex regex_arithmetical_expression	{ arithmetical_expression };
	const regex regex_logic_expression			{ logic_expression };
	const regex regex_arithmetical_equation		{ arithmetical_equation };

}




