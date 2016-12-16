#include "Command.h"

Tag_menager* Command::tag_menager_ptr = nullptr;
string* Command::last_success_string_ptr = nullptr;
bool* Command::was_last_success_if_ptr = nullptr;

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

void Command::set_static_tag_menager_ptr(Tag_menager* ptr)
{
	tag_menager_ptr = ptr;
}

void Command::set_last_success_string_ptr(string *ptr)
{
	last_success_string_ptr = ptr;
}

void Command::set_was_last_success_if_ptr(bool *ptr)
{
	was_last_success_if_ptr = ptr;
}

Command::Command(string code)
	:
	command_string(code)
{
}


//Command::Command()
//{
//}


Command::~Command()
{
}
