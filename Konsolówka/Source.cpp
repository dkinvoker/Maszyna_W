#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "const_regex.h"
#include <vector>
#include "code_transformator.h"

using namespace std;

int main()
{
	ofstream output_file;
	ifstream input_file;
	code_transformator CodeTranformator;

	input_file.open("code.troll");
	output_file.open("Asembler.prg");


	CodeTranformator.clear_blank_and_save(input_file);
	CodeTranformator.check_syntax();



	system("pause");



}