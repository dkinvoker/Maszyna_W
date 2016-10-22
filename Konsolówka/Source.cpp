#include <iostream>
#include <string>


using namespace std;

int main()
{
	string test = "37.65";
	double test_double;
	test_double = stod(test);
	cout << test_double
		<< "\n";
	system("pause");

}