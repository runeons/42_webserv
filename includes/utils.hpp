
#ifndef UTILS_HPP
# define UTILS_HPP

// ********************************************* exec_cmd **************************************

std::string	exec_cmd(std::string cmd, std::string file_res);

// ********************************************* file manip ************************************

std::string	get_extension(std::string path);
std::string	get_file_content(std::string filename);

// ********************************************* binary conversion *****************************

std::string	itos(int nb);
std::string	int_to_binary(int n);
std::string	string_to_binary(std::string s);
std::string	binary_to_string(std::string s);

// ********************************************* char printing *********************************

void		print_char_printf(char c);
void		print_char(char c);

#endif
