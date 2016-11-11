#include "code_transformator.h"

void code_transformator::clear_blank_and_save(ifstream &input, string &buffer)
{
	string IN_buffer;
	while (input >> IN_buffer)
	{
		buffer = buffer + IN_buffer;
	}
}


code_transformator::code_transformator()
{
}


code_transformator::~code_transformator()
{
}
