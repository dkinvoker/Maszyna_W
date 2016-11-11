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
	string buffer;

	input_file.open("code.troll");
	output_file.open("Asembler.prg");

	code_transformator::clear_blank_and_save(input_file, buffer);
	output_file << buffer;


}