#include "Command.h"

void Command::Load_sring_into(string &a)
{
	command_string = a;
}

//Command::Command(Tag_menager &ref, string code)
//	:command_string(code),
//	tag_menager_ptr(ref)
//{
//
//}


Command::Command(string code, code_transformator &to_ref_to)
	:
	command_string(code),
	tag_menager_ptr(&(to_ref_to.tag_menager))
{
}


//Command::Command()
//{
//}


Command::~Command()
{
}
