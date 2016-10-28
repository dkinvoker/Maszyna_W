#include "const_regex.h"

string const_regex_string::multi_regex_string(string regex_string)
{
	return "(" + regex_string + ")*";
}

string const_regex_string::regex_or_regex(string regex1, string regex2)
{
	return "((" + regex1 + ")|(" + regex2 + "))";
}




//-----------------------------------------------------------------
