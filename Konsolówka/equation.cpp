#include "equation.h"


bool is_constant_type(const string a)
{
	if (regex_match(a, const_regex::regex_ID))
	{
		return false;
	}
	return true;
}


bool is_operator_symbol (const char a) 
{
	if (a == '+' || a == '-' || a == '*' || a == '/')
	{
		return true;
	}
	return false;
}

int get_int_symbolic_value_from_char( const char a )
{
	if (a == '+')
	{
		return add_symbol;
	}
	if (a == '-')
	{
		return subtract_symbol;
	}
	if (a == '*')
	{
		return multiplication_symbol;
	}
	return divid_symbol;
}



void Equation::get_all_expression_information()
{
	string buffer;
	for (unsigned int i = 0; i < expression.size(); i ++)
	{
		if ( is_operator_symbol(expression[i]) )
		{
			//checking if first operand is negative.... (lel = -8)
			if (buffer.size() != 0)
			{
				operands_vector.push_back(buffer);
				operators_vector.push_back( get_int_symbolic_value_from_char(expression[i]) );
			}
			else
			{
				buffer = "-";
				continue;
			}
			


			//negative numbers: skiping the '-' and initializing number as negative
			if (i+1 >= expression.size())
			{
				throw string("Równanie: Przekroczenie zakresu... Teoretycznie niemożliwe");
			}
			if (expression[i+1] == '-')
			{
				buffer = "-";
				i++;
			}
			//Non negative
			else
			{
				buffer = "";
			}

			
		}
		else
		{
			buffer += expression[i];
		}
	}
	operands_vector.push_back(buffer);

}


void Equation::extract_components()
{
	int eq_index;

	for (unsigned int i = 0; i < command_string.size(); i ++)
	{
		if (command_string[i] == '=')
		{
			eq_index = i;
			break;
		}
	}

	equation_head = command_string.substr(0, eq_index);

	//without semicolon
	expression = command_string.substr(eq_index + 1, command_string.size() - eq_index - 2);

}


Assembler_section Equation::translate()
{
	Assembler_section returner;
	bool is_constant_bool_helper;

	this->extract_components();
	this->get_all_expression_information();

	if ( is_constant_type( operands_vector[0]) )
	{
		//Adding const value
		if (tag_menager_ptr->add_const(operands_vector[0]))
		{
			returner.add_data(tag_menager_ptr->get_tag_by_const_value(operands_vector[0]), "RST", operands_vector[0]);
		}
		//Geting first operend to accumulator
		returner.add_program("POB", tag_menager_ptr->get_tag_by_const_value(operands_vector[0]));

	}
	else
	{
		if (tag_menager_ptr->get_type_by_name(operands_vector[0]) != Tag_type::variable_char && tag_menager_ptr->get_type_by_name(operands_vector[0]) != Tag_type::variable_int)
		{
			throw string("Odwołanie do nazwy powiązanej z niewłaściwym typem: " + operands_vector[0]);
		}
		returner.add_program("POB", tag_menager_ptr->get_tag_by_name(operands_vector[0]));
	}

	//dooing arithmetical stuff
	for (unsigned int i = 1; i < operands_vector.size(); i ++)
	{

		if (is_constant_bool_helper = is_constant_type(operands_vector[i]))
		{
			//Adding const value
			if ( tag_menager_ptr->add_const(operands_vector[i]) )
			{
				returner.add_data(tag_menager_ptr->get_tag_by_const_value(operands_vector[i]), "RST", operands_vector[i]);
			}
		}

		switch (operators_vector[i-1])
		{
		case add_symbol:

			if (is_constant_bool_helper)
			{
				returner.add_program( "DOD", tag_menager_ptr->get_tag_by_const_value(operands_vector[i]) );
			}
			else
			{
				if (tag_menager_ptr->get_type_by_name(operands_vector[i]) != Tag_type::variable_char && tag_menager_ptr->get_type_by_name(operands_vector[i]) != Tag_type::variable_int)
				{
					throw string("Odwołanie do nazwy powiązanej z niewłaściwym typem: " + operands_vector[i]);
				}
				returner.add_program( "DOD", tag_menager_ptr->get_tag_by_name(operands_vector[i]) );
			}

			break;
		case subtract_symbol:

			if (is_constant_bool_helper)
			{
				returner.add_program( "ODE", tag_menager_ptr->get_tag_by_const_value(operands_vector[i]) );
			}
			else
			{
				if (tag_menager_ptr->get_type_by_name(operands_vector[i]) != Tag_type::variable_char && tag_menager_ptr->get_type_by_name(operands_vector[i]) != Tag_type::variable_int)
				{
					throw string("Odwołanie do nazwy powiązanej z niewłaściwym typem: " + operands_vector[i]);
				}
				returner.add_program( "ODE", tag_menager_ptr->get_tag_by_name(operands_vector[i]) );
			}

			break;
		case multiplication_symbol:

			if (is_constant_bool_helper)
			{
				returner.add_program( "MNO", tag_menager_ptr->get_tag_by_const_value(operands_vector[i]) );
			}
			else
			{
				if (tag_menager_ptr->get_type_by_name(operands_vector[i]) != Tag_type::variable_char && tag_menager_ptr->get_type_by_name(operands_vector[i]) != Tag_type::variable_int)
				{
					throw string("Odwołanie do nazwy powiązanej z niewłaściwym typem: " + operands_vector[i]);
				}
				returner.add_program( "MNO", tag_menager_ptr->get_tag_by_name(operands_vector[i]) );
			}

			break;
		case divid_symbol:

			if (is_constant_bool_helper)
			{
				returner.add_program( "DZI", tag_menager_ptr->get_tag_by_const_value(operands_vector[i]) );
			}
			else
			{
				if (tag_menager_ptr->get_type_by_name(operands_vector[i]) != Tag_type::variable_char && tag_menager_ptr->get_type_by_name(operands_vector[i]) != Tag_type::variable_int)
				{
					throw string("Odwołanie do nazwy powiązanej z niewłaściwym typem: " + operands_vector[i]);
				}
				returner.add_program( "DZI", tag_menager_ptr->get_tag_by_name(operands_vector[i]) );
			}

			break;
		default:
			throw string("RÓWNANIE: NIEZNANY OPERATOR!!!!!!") ;
			break;
		}
	}

	returner.add_program( "ŁAD", tag_menager_ptr->get_tag_by_name(equation_head) );


	*last_success_string_ptr = command_string;
	*was_last_success_if_ptr = false;
	return returner;
}

Equation::Equation(string code)
	:
	Command(code)
{
}



Equation::~Equation()
{
}
