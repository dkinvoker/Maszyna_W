#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "const_regex.h"
#include <vector>
#include "code_transformator.h"
#include "Declaration.h"

using namespace std;

int main()
{
	ofstream output_file;
	ofstream log_file;
	ifstream input_file;
	code_transformator CodeTranformator	{ log_file, input_file, output_file };

	input_file.open("code.troll");
	output_file.open("Asembler.prg");
	log_file.open("Log.txt");


	CodeTranformator.clear_blank_and_save();
	CodeTranformator.code_into_sections();
	CodeTranformator.check_syntax();
	//CodeTranformator.catch_consts();

	Declaration test{ "char_XXX;", CodeTranformator };
	CodeTranformator.adapt_section(test.expand());

	output_file.close();
	input_file.close();
	log_file.close();



	//system("pause");



}