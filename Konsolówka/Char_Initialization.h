#pragma once
#include "Initialization.h"
#include "Declaration.h"
#include "Command.h"


class Char_Initialization :
	public Initialization,
	public Command
{
public:
	Char_Initialization();
	~Char_Initialization();
};

