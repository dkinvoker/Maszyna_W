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
	CodeTranformator.bind_commands();

	CodeTranformator.clear_blank_and_save();
	CodeTranformator.code_into_sections();
	CodeTranformator.check_syntax();
	//CodeTranformator.catch_consts();
	//CodeTranformator.generate_assembler_code();
	//CodeTranformator.save_generated_code();




	//// SEKCJA TESTOWA
	//log_file << "\nTEST:\n";

	//Declaration test{ "char_XXX;" };
	//Declaration test2{ "char_XXX;" };
	//Initialization test3{ "intDUPA=123;" };
	//Initialization test4{ "intDUPAA=123;" };
	//Equation eq_test{ "_XXX=_XXX+1/DUPA*DUPA-DUPAA;" };
	//Equation eq_test2{ "DUPA=3;" };
	//Equation eq_test3{ "DUP=3;" };


	////Initialization test5{ CodeTranformator.code, CodeTranformator };
	//Initialization test5{ "chara=\"a\";" };
	//try
	//{
	//	CodeTranformator.adapt_section(test.translate());
	//	//CodeTranformator.adapt_section(test2.translate());
	//	CodeTranformator.adapt_section(test3.translate());
	//	CodeTranformator.adapt_section(test4.translate());
	//	CodeTranformator.adapt_section(test5.translate());
	//	CodeTranformator.adapt_section(eq_test.translate());
	//	CodeTranformator.adapt_section(eq_test2.translate());
	//	CodeTranformator.adapt_section(eq_test3.translate());

	//}
	//catch (string &Error)
	//{
	//	log_file
	//		<< Error
	//		<< "\n\n" << "Ostatnie wyrażenie rozwinięte z sukcesem: " << "\n" << CodeTranformator.get_last_successfully_translated_command()
	//		<< "\n\n" << "Zaniechanie dalszej pracy\n";
	//}






	// KONIEC SEKCJI TESTOWEJ

	vector<Command*> lel;
	lel.push_back(new Declaration{"xD"});

	log_file << "\n KONIEC \n";

	output_file.close();
	input_file.close();
	log_file.close();



	//system("pause");



}