#include "const_regex.h"

string const_regex_string::multi_regex_STRING(string regex_string)
{
	return "(" + regex_string + ")*";
}

string const_regex_string::regex_or_regex_STRING(string regex1, string regex2)
{
	return "((" + regex1 + ")|(" + regex2 + "))";
}

string const_regex_string::regex_in_brackets_character_STRING(string regex_string)
{
	return "(\\(" + regex_string + "\\))";
}

string const_regex_string::multi_regex_og_regex_STRING(vector<string> alternative_strings)
{
	string buffer_string;
	buffer_string = buffer_string + "(";
	for (int i = 0; i < alternative_strings.size(); i++)
	{
		if (i == alternative_strings.size() - 1)
		{
			buffer_string = buffer_string + "(" + alternative_strings[i] + ")";
		}
		else
		{
			buffer_string = buffer_string + "(" + alternative_strings[i] + ")|";
		}

	}
	buffer_string = buffer_string + ")";
	return buffer_string;
}

string const_regex_string::regex_in_box_STRING(string regex_string)
{
	return "\\{" + regex_string + "\\}";
}


//-----------------------------------------------------------------
