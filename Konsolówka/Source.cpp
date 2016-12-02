#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "const_regex.h"
#include <vector>
#include "code_transformator.h"
#include "Declaration.h"
#include "Initialization.h"

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


	// SEKCJA TESTOWA
	log_file << "\nTEST:\n";

	Declaration test{ "char_XXX;", CodeTranformator };
	Declaration test2{ "char_XXX;", CodeTranformator };
	Initialization test3{ "intDUPA=123;", CodeTranformator };
	try
	{
		CodeTranformator.adapt_section(test.translate());
		CodeTranformator.adapt_section(test2.translate());
		CodeTranformator.adapt_section(test3.translate());
	}
	catch (string Error)
	{
		log_file << Error << "\n" << "Zaniechanie dalszej pracy\n";
	}
	// KONIEC SEKCJI TESTOWEJ

	log_file << "\n KONIEC \n";

	output_file.close();
	input_file.close();
	log_file.close();



	//system("pause");



}