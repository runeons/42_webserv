# include "Array.hpp"

void	test_string(void)
{
	std::cout << CORAIL << std::endl;
	std::cout << "___________________ TESTS WITH STRING ___________________" << C_RES;
	std::cout << std::endl;

	std::string str_fill[6] = { "Abc", "Def", "Ghi", "Jkl", "Mno", "Pqr"};
	std::cout << GREEN_TREE << std::endl << "________________ Empty std::string array ________________" << std::endl << C_RES << std::endl;

	Array<std::string> empty_str;
	std::cout << BROWN << "size : " << empty_str.size() << std::endl;
	std::cout << empty_str << std::endl;
	std::cout << GREEN_TREE << std::endl << "_ _ _ _ _ _ _ _  Try [out of boundaries] _ _ _ _ _ _ _ _ _" << std::endl << C_RES << std::endl;
	try { std::cout << empty_str[-1] << std::endl; }
	catch (std::exception &e) {
		std::cout << RED_B << "Error :" << WHITE_B << " index is out of boundaries" << C_RES << std::endl; }
	try { std::cout << empty_str[0] << std::endl; }
	catch (std::exception &e) {
		std::cout << RED_B << "Error :" << WHITE_B << " index is out of boundaries" << C_RES << std::endl; }

	std::cout << GREEN_TREE << std::endl << "______________________ Int[1] array _____________________" << std::endl << C_RES << std::endl;

	Array<std::string> one_str(1);
	std::cout << BROWN << "size : " << one_str.size() << std::endl;
	for (int i = 0; i < 1; i++)
		one_str[i] = str_fill[i];
	std::cout << one_str << std::endl;
	std::cout << GREEN_TREE << std::endl << "_ _ _ _ _ _ _ _  Try [out of boundaries] _ _ _ _ _ _ _ _ _" << std::endl << C_RES << std::endl;
	try { std::cout << one_str[-1] << std::endl; }
	catch (std::exception &e) {
		std::cout << RED_B << "Error :" << WHITE_B << " index is out of boundaries" << C_RES << std::endl; }
	try { std::cout << one_str[1] << std::endl; }
	catch (std::exception &e) {
		std::cout << RED_B << "Error :" << WHITE_B << " index is out of boundaries" << C_RES << std::endl; }

	std::cout << GREEN_TREE << std::endl << "______________________ Int[4] array _____________________" << std::endl << C_RES << std::endl;

	Array<std::string> four_str(4);
	std::cout << BROWN << "size : " << four_str.size() << std::endl;
	for (int i = 0; i < 4; i++)
		four_str[i] = str_fill[i];
	std::cout << four_str << std::endl;
	std::cout << GREEN_TREE << std::endl << "_ _ _ _ _ _ _ _  Try [out of boundaries] _ _ _ _ _ _ _ _ _" << std::endl << C_RES << std::endl;
	try { std::cout << four_str[-1] << std::endl; }
	catch (std::exception &e) {
		std::cout << RED_B << "Error :" << WHITE_B << " index is out of boundaries" << C_RES << std::endl; }
	try { std::cout << four_str[5] << std::endl; }
	catch (std::exception &e) {
		std::cout << RED_B << "Error :" << WHITE_B << " index is out of boundaries" << C_RES << std::endl; }

	std::cout << GREEN_TREE << std::endl << "_ _ _ _ _ _ _ _ _  Constructor by copy _ _ _ _ _ _ _ _ _ _" << std::endl << C_RES << std::endl;
	Array<std::string> cpy_str(four_str);
	std::cout << "src : "<< four_str << std::endl;
	std::cout << "cpy : "<< cpy_str << std::endl;
	std::cout << GREEN_TREE << std::endl << "_ _ _ _ _ _ _ _ _ _ _  Assignation _ _ _ _ _ _ _ _ _ _ _ _" << std::endl << C_RES << std::endl;
	cpy_str = one_str;
	std::cout << "src after assignation (should not have changed): " << four_str << std::endl;
	std::cout << "cpy after assignation (should have changed)    : " << cpy_str << std::endl;
	std::cout << GREEN_TREE << std::endl << "_ _ _ _ _ _ _ _ Change first elem in cpy _ _ _ _ _ _ _ _ _" << std::endl << C_RES << std::endl;
	cpy_str[0] = "new_first_elem";
	std::cout << "one : "<< one_str << std::endl;
	std::cout << "src : "<< four_str << std::endl;
	std::cout << "cpy : "<< cpy_str << std::endl;
	std::cout << std::endl;
}

void	test_int(void)
{
	std::cout << CORAIL << std::endl;
	std::cout << "_____________________ TESTS WITH INT ____________________" << C_RES;
	std::cout << std::endl;

	int int_fill[6] = { 0, 1, 22, 333, 4444, 55555 };
	std::cout << GREEN_TREE << std::endl << "____________________ Empty int array ____________________" << std::endl << C_RES << std::endl;

	Array<int> empty_int;
	std::cout << BROWN << "size : " << empty_int.size() << std::endl;
	std::cout << empty_int << std::endl;
	std::cout << GREEN_TREE << std::endl << "_ _ _ _ _ _ _ _  Try [out of boundaries] _ _ _ _ _ _ _ _ _" << std::endl << C_RES << std::endl;
	try { std::cout << empty_int[-1] << std::endl; }
	catch (std::exception &e) {
		std::cout << RED_B << "Error :" << WHITE_B << " index is out of boundaries" << C_RES << std::endl; }
	try { std::cout << empty_int[0] << std::endl; }
	catch (std::exception &e) {
		std::cout << RED_B << "Error :" << WHITE_B << " index is out of boundaries" << C_RES << std::endl; }

	std::cout << GREEN_TREE << std::endl << "____________________ String[1] array ____________________" << std::endl << C_RES << std::endl;

	Array<int> one_int(1);
	std::cout << BROWN << "size : " << one_int.size() << std::endl;
	for (int i = 0; i < 1; i++)
		one_int[i] = int_fill[i];
	std::cout << one_int << std::endl;
	std::cout << GREEN_TREE << std::endl << "_ _ _ _ _ _ _ _  Try [out of boundaries] _ _ _ _ _ _ _ _ _" << std::endl << C_RES << std::endl;
	try { std::cout << one_int[-1] << std::endl; }
	catch (std::exception &e) {
		std::cout << RED_B << "Error :" << WHITE_B << " index is out of boundaries" << C_RES << std::endl; }
	try { std::cout << one_int[1] << std::endl; }
	catch (std::exception &e) {
		std::cout << RED_B << "Error :" << WHITE_B << " index is out of boundaries" << C_RES << std::endl; }

	std::cout << GREEN_TREE << std::endl << "____________________ String[4] array ____________________" << std::endl << C_RES << std::endl;

	Array<int> four_int(4);
	std::cout << BROWN << "size : " << four_int.size() << std::endl;
	for (int i = 0; i < 4; i++)
		four_int[i] = int_fill[i];
	std::cout << four_int << std::endl;
	std::cout << GREEN_TREE << std::endl << "_ _ _ _ _ _ _ _  Try [out of boundaries] _ _ _ _ _ _ _ _ _" << std::endl << C_RES << std::endl;
	try { std::cout << four_int[-1] << std::endl; }
	catch (std::exception &e) {
		std::cout << RED_B << "Error :" << WHITE_B << " index is out of boundaries" << C_RES << std::endl; }
	try { std::cout << four_int[5] << std::endl; }
	catch (std::exception &e) {
		std::cout << RED_B << "Error :" << WHITE_B << " index is out of boundaries" << C_RES << std::endl; }

	std::cout << GREEN_TREE << std::endl << "_ _ _ _ _ _ _ _ _  Constructor by copy _ _ _ _ _ _ _ _ _ _" << std::endl << C_RES << std::endl;
	Array<int> cpy_int(four_int);
	std::cout << "src : "<< four_int << std::endl;
	std::cout << "cpy : "<< cpy_int << std::endl;
	std::cout << GREEN_TREE << std::endl << "_ _ _ _ _ _ _ _ _ _ _  Assignation _ _ _ _ _ _ _ _ _ _ _ _" << std::endl << C_RES << std::endl;
	cpy_int = one_int;
	std::cout << "src after assignation (should not have changed): " << four_int << std::endl;
	std::cout << "cpy after assignation (should have changed)    : " << cpy_int << std::endl;
	std::cout << GREEN_TREE << std::endl << "_ _ _ _ _ _ _ _ Change first elem in cpy _ _ _ _ _ _ _ _ _" << std::endl << C_RES << std::endl;
	cpy_int[0] = 8;
	std::cout << "one : "<< one_int << std::endl;
	std::cout << "src : "<< four_int << std::endl;
	std::cout << "cpy : "<< cpy_int << std::endl;
	std::cout << std::endl;
}

void	test_float(void)
{
	std::cout << CORAIL << std::endl;
	std::cout << "____________________ TESTS WITH FLOAT ___________________" << C_RES;
	std::cout << std::endl;

	float float_fill[6] = { 0.01, 1.11, 22.2, 333.33, 4444.4444, 55555.55 };
	std::cout << GREEN_TREE << std::endl << "___________________ Empty float array ___________________" << std::endl << C_RES << std::endl;

	Array<float> empty_float;
	std::cout << BROWN << "size : " << empty_float.size() << std::endl;
	std::cout << empty_float << std::endl;
	std::cout << GREEN_TREE << std::endl << "_ _ _ _ _ _ _ _  Try [out of boundaries] _ _ _ _ _ _ _ _ _" << std::endl << C_RES << std::endl;
	try { std::cout << empty_float[-1] << std::endl; }
	catch (std::exception &e) {
		std::cout << RED_B << "Error :" << WHITE_B << " index is out of boundaries" << C_RES << std::endl; }
	try { std::cout << empty_float[0] << std::endl; }
	catch (std::exception &e) {
		std::cout << RED_B << "Error :" << WHITE_B << " index is out of boundaries" << C_RES << std::endl; }

	std::cout << GREEN_TREE << std::endl << "____________________ String[1] array ____________________" << std::endl << C_RES << std::endl;

	Array<float> one_float(1);
	std::cout << BROWN << "size : " << one_float.size() << std::endl;
	for (int i = 0; i < 1; i++)
		one_float[i] = float_fill[i];
	std::cout << one_float << std::endl;
	std::cout << GREEN_TREE << std::endl << "_ _ _ _ _ _ _ _  Try [out of boundaries] _ _ _ _ _ _ _ _ _" << std::endl << C_RES << std::endl;
	try { std::cout << one_float[-1] << std::endl; }
	catch (std::exception &e) {
		std::cout << RED_B << "Error :" << WHITE_B << " index is out of boundaries" << C_RES << std::endl; }
	try { std::cout << one_float[1] << std::endl; }
	catch (std::exception &e) {
		std::cout << RED_B << "Error :" << WHITE_B << " index is out of boundaries" << C_RES << std::endl; }

	std::cout << GREEN_TREE << std::endl << "____________________ String[4] array ____________________" << std::endl << C_RES << std::endl;

	Array<float> four_float(4);
	std::cout << BROWN << "size : " << four_float.size() << std::endl;
	for (int i = 0; i < 4; i++)
		four_float[i] = float_fill[i];
	std::cout << four_float << std::endl;
	std::cout << GREEN_TREE << std::endl << "_ _ _ _ _ _ _ _  Try [out of boundaries] _ _ _ _ _ _ _ _ _" << std::endl << C_RES << std::endl;
	try { std::cout << four_float[-1] << std::endl; }
	catch (std::exception &e) {
		std::cout << RED_B << "Error :" << WHITE_B << " index is out of boundaries" << C_RES << std::endl; }
	try { std::cout << four_float[5] << std::endl; }
	catch (std::exception &e) {
		std::cout << RED_B << "Error :" << WHITE_B << " index is out of boundaries" << C_RES << std::endl; }

	std::cout << GREEN_TREE << std::endl << "_ _ _ _ _ _ _ _ _  Constructor by copy _ _ _ _ _ _ _ _ _ _" << std::endl << C_RES << std::endl;
	Array<float> cpy_float(four_float);
	std::cout << "src : "<< four_float << std::endl;
	std::cout << "cpy : "<< cpy_float << std::endl;
	std::cout << GREEN_TREE << std::endl << "_ _ _ _ _ _ _ _ _ _ _  Assignation _ _ _ _ _ _ _ _ _ _ _ _" << std::endl << C_RES << std::endl;
	cpy_float = one_float;
	std::cout << "src after assignation (should not have changed): " << four_float << std::endl;
	std::cout << "cpy after assignation (should have changed)    : " << cpy_float << std::endl;
	std::cout << GREEN_TREE << std::endl << "_ _ _ _ _ _ _ _ Change first elem in cpy _ _ _ _ _ _ _ _ _" << std::endl << C_RES << std::endl;
	cpy_float[0] = 9.0456;
	std::cout << "one : "<< one_float << std::endl;
	std::cout << "src : "<< four_float << std::endl;
	std::cout << "cpy : "<< cpy_float << std::endl;
	std::cout << std::endl;
}

int main(void)
{
	test_int();
	test_float();
	test_string();
	return 0;
}
