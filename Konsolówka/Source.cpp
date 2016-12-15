#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "const_regex.h"
#include <vector>
#include "code_transformator.h"
#include "Declaration.h"
#include "Initialization.h"
#include "equation.h"

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
	Initialization test4{ "intDUPAA=123;", CodeTranformator };
	Equation eq_test{ "_XXX=_XXX+1/DUPA*DUPA-DUPAA", CodeTranformator };
	Equation eq_test2{ "DUPA=3", CodeTranformator };
	Equation eq_test3{ "DUP=3", CodeTranformator };


	//Initialization test5{ CodeTranformator.code, CodeTranformator };
	Initialization test5{ "chara=\"a\";", CodeTranformator };
	try
	{
		CodeTranformator.adapt_section(test.translate());
		//CodeTranformator.adapt_section(test2.translate());
		CodeTranformator.adapt_section(test3.translate());
		CodeTranformator.adapt_section(test4.translate());
		CodeTranformator.adapt_section(test5.translate());
		CodeTranformator.adapt_section(eq_test.translate());
		CodeTranformator.adapt_section(eq_test2.translate());
		CodeTranformator.adapt_section(eq_test3.translate());

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