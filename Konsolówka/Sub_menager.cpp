#include "Sub_menager.h"

sub_and_parameters Sub_menager::get_parmeters_by_name(string name)
{
	for (unsigned int i = 0; i < Sub_parameters_vector.size(); i++)
	{
		if (Sub_parameters_vector[i].name == name)
		{
			return Sub_parameters_vector[i];
		}
	}

	throw string("Sub meganer: jakiœ hard b³¹d");
}

void Sub_menager::register_variables(string name, vector<string> input_var, vector<string> output_var)
{
	Sub_parameters_vector.push_back(sub_and_parameters{name, input_var, output_var});
}

const string Sub_menager::get_translating_now()
{
	return translating_now;
}

void Sub_menager::set_translating_now(string name)
{
	translating_now = name;
}


Sub_menager::Sub_menager()
{
}


Sub_menager::~Sub_menager()
{
}
