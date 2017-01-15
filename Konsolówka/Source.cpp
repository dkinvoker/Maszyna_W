#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif


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

int main(int argc, char *argv[])
{
	ofstream output_file;
	ofstream log_file;
	ifstream input_file;
	code_transformator CodeTranformator	 {input_file, output_file };
	bool input_path_done = false;
	bool output_path_done = false;
	bool log_path_done = false;

	try
	{
		if (argc != 5 && argc != 7)
		{
			throw string("Nieprawid³owa liczba argumentów!\n");
		}
		for (int i = 1; i < argc; i++)
		{
			if ( string(*(argv+ i)) == "-i")
			{
				i++;
				input_file.open(*(argv + i));
				input_path_done = true;
				
			}
			else if ( string(*(argv + i)) == "-o")
			{
				i++;
				output_file.open(*(argv + i));
				output_path_done = true;
			}
			else if( string(*(argv + i)) == "-l")
			{
				i++;
				log_file.open(*(argv + i));
				log_path_done = true;
			}
			else
			{
				throw string("Nieprawid³owe parametry dla programu");
			}
		}
		if (input_path_done != true || output_path_done != true)
		{
			throw string("Musisz podaæ œciê¿kê wejœciow¹ i wyjœciow¹!\n");
		}

		if (!input_file.is_open())
		{
			throw string("Plik wejœciowy nie zosta³ odnaleziony, lub nie mo¿na go otworzyæ!\n");
		}
		if (!output_file.is_open())
		{
			throw string("Plik wyjœciowy nie zosta³ odnaleziony, lub nie mo¿na go otworzyæ!\n");
		}

		if (log_path_done == true)
		{
			if (!log_file.is_open())
			{
				throw string("Plik wyjœciowy logów nie zosta³ odnaleziony, lub nie mo¿na go otworzyæ!\n");
			}
			CodeTranformator.set_log_output(&log_file);
		}

	}
	catch (const string &ERROR)
	{
		cout << ERROR;
		return 0;
	}


	


	try
	{
		CodeTranformator.bind_commands();
		CodeTranformator.clear_blank_and_save();
		CodeTranformator.code_into_sections();
		CodeTranformator.check_syntax();
		CodeTranformator.generate_assembler_code();
		CodeTranformator.execute_meta_commands();
		CodeTranformator.merge_tags();
		CodeTranformator.save_start_to_the_file();
		CodeTranformator.save_additional_subs();
		CodeTranformator.add_stop_at_the_end();
		CodeTranformator.tag_absorption();
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

	output_file.close();
	input_file.close();
	log_file.close();


	_CrtDumpMemoryLeaks();


}