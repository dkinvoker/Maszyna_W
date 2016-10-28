#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "const_regex.h"

using namespace std;

int main()
{

	string test;
	while (true)
	{
		cin >> test;
		if (regex_match(test,const_regex::regex_arithmetical_expression))
		{
			cout << "GOOD\n";
		}
		else
		{
			cout << "nicht\n";
		}
	}

	system("pause");

}