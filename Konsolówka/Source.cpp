#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "const_regex.h"
#include <vector>
#include "code_transformator.h"
#include "Command.h"
#include "Declaration.h"
#include "Initialization.h"
#include "equation.h"
#include "If_expression.h"

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


	try
	{
		CodeTranformator.clear_blank_and_save();
		CodeTranformator.code_into_sections();
		CodeTranformator.check_syntax();
		//CodeTranformator.catch_consts();
		CodeTranformator.generate_assembler_code();
		CodeTranformator.merge_tags();
		CodeTranformator.add_stop_at_the_end();
		CodeTranformator.save_generated_code();
		log_file << "\n\nTranslacja zakoñczona sukcesem";
	}
	catch (const string &Error)
	{
			log_file
				<< Error
				<< "\n\n" << "Ostatnie wyra¿enie rozwiniête z sukcesem: " << "\n\t" << CodeTranformator.get_last_successfully_translated_command()
				<< "\n\n" << "Zaniechanie dalszej pracy\n"
				<< "\n NIEPOWODZENIE";
	}




	//// SEKCJA TESTOWA
	//log_file << "\nTEST:\n";

	//Declaration test{ "char_XXX;" };
	//Declaration test2{ "char_XXX;" };
	//Initialization test3{ "intDUPA=123;" };
	//Initialization test4{ "intDUPAA=123;" };
	//Equation eq_test{ "_XXX=_XXX+1/DUPA*DUPA-DUPAA;" };
	//Equation eq_test2{ "DUPA=3;" };
	//Equation eq_test3{ "DUP=3;" };
	//If_expression test_ifa{"if(troll!=elizabet+8){randomaction}"};


	//Initialization test5{ CodeTranformator.code, CodeTranformator };
	//Initialization test5{ "chara=\"a\";" };
	try
	{
		//CodeTranformator.adapt_section(test.translate());
		////CodeTranformator.adapt_section(test2.translate());
		//CodeTranformator.adapt_section(test3.translate());
		//CodeTranformator.adapt_section(test4.translate());
		//CodeTranformator.adapt_section(test5.translate());
		//CodeTranformator.adapt_section(eq_test.translate());
		//CodeTranformator.adapt_section(eq_test2.translate());
		//CodeTranformator.adapt_section(eq_test3.translate());
		//test_ifa.translate();

	}
	catch (string &Error)
	{
		log_file
			<< Error
			<< "\n\n" << "Ostatnie wyra¿enie rozwiniête z sukcesem: " << "\n" << CodeTranformator.get_last_successfully_translated_command()
			<< "\n\n" << "Zaniechanie dalszej pracy\n";
	}






	// KONIEC SEKCJI TESTOWEJ


	//log_file << "\n KONIEC \n";

	output_file.close();
	input_file.close();
	log_file.close();



	//system("pause");



}