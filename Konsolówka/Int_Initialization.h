#pragma once
#include "Initialization.h"
#include "Declaration.h"
#include "Command.h"


class Int_Initialization :
	public Initialization,
	public Command
{
public:
	Int_Initialization();
	~Int_Initialization();
};

