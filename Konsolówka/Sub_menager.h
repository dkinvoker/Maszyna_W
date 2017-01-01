#pragma once
#include "Struct_header.h"
#include <vector>

using namespace std;

class Sub_menager
{
	vector<sub_and_parameters> Sub_parameters_vector;
	string translating_now;

public:

	void register_variables(string name, vector<string> input_var, vector<string> output_var);
	sub_and_parameters get_parmeters_by_name( string name );
	void set_translating_now(string name);
	const string get_translating_now();

	Sub_menager();
	~Sub_menager();
};

