#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "const_regex.h"
#include <vector>

using namespace std;

int main()
{

	string test;
	regex liczba_w_nawiasch{"(\\([[:digit:]]\\))"};
	regex test_regex;
	//while (true)
	//{
	//	cin >> test;
	//	if (regex_match(test,const_regex::regex_arithmetical_expression))
	//	{
	//		cout << "GOOD\n";
	//	}
	//	else
	//	{
	//		cout << "nicht\n";
	//	}
	//}

	//while (true)
	//{
	//	cin >> test;
	//	if (regex_match(test, liczba_w_nawiasch))
	//	{
	//		cout << "GOOD\n";
	//	}
	//	else
	//	{
	//		cout << "nicht\n";
	//	}
	//}

	//test = const_regex_string::multi_OR_regex_STRING( vector<string> {"pierwsze","drugie","czecie"} );
	//
	//cout 
	//	<< test
	//	<< "\n";

	test_regex = const_regex_string::code_surrounded_by_quotation;
	while (true)
	{
		cin >> test;
		if (regex_match(test, test_regex))
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