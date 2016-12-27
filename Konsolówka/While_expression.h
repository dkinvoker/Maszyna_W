#pragma once
#include "If_expression.h"
class While_expression :
	public If_expression
{

public:

	Assembler_section translate();

	While_expression(string code);
	While_expression() = delete;
	~While_expression();
};

