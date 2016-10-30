#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "const_regex.h"
#include <vector>
#include <fstream>

using namespace std;

int main()
{
	ofstream out_put_file;
	out_put_file.open("code.troll");
	string test;
	regex liczba_w_nawiasch{"(\\([[:digit:]]\\))"};
	regex test_regex;

	test = const_regex::syntax_sting;
	test_regex = test;


	out_put_file
		<< test;

	//while (true)
	//{
	//	cin >> test;
	//	if (regex_match(test, test_regex))
	//	{
	//		cout << "GOOD\n";
	//	}
	//	else
	//	{
	//		cout << "nicht\n";
	//	}
	//}


	system("pause");

}