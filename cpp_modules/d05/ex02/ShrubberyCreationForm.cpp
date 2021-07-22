# include "ShrubberyCreationForm.hpp"

// Copy constructor
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& src) : Form(src), _target(src.getTarget())
{
	return;
}

// Parametric constructor (std::string)
ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : Form("Shrubbery", 145, 137), _target(target)
{
	return ;
}

// Destructor
ShrubberyCreationForm::~ShrubberyCreationForm(void)
{
	std::cout << CORAIL << "ShrubberyCreationFormForm destruction..." << C_RES << std::endl;
	return;
}

// Assignation operator
ShrubberyCreationForm &	ShrubberyCreationForm::operator=(const ShrubberyCreationForm& rhs)
{
	std::cout << GREY << "ShrubberyCreationForm Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_target = rhs.getTarget();
	}
	return (*this);
}

// getters and setters (non static attributes)
std::string ShrubberyCreationForm::getTarget(void) const
{
	return (this->_target);
}

/*
	ShrubberyCreationForm (Grades requis : signature 145, execution 137). Action :
	Crée un fichier nommé <target>_shrubbery, et dessine des arbres en ASCII
	dedans, dans le dossier courant.
*/

std::string	draw_tree(void)
{
	return
	" \
                                 x\n \
                                xxx\n \
                               xxxxx\n \
                              xxxxxxx\n \
                             xxxxxxxxx\n \
                            xxxxxxxxxxx\n \
                           xxxxxxxxxxxxx\n \
                          xxxxxxxxxxxxxxx\n \
                         xxxxxxxxxxxxxxxxx\n \
                        xxxxxxxxxxxxxxxxxxx\n \
                       xxxxxxxxxxxxxxxxxxxxx\n \
                      xxxxxxxxxxxxxxxxxxxxxxx\n \
                     xxxxxxxxxxxxxxxxxxxxxxxxx\n \
                    xxxxxxxxxxxxxxxxxxxxxxxxxxx\n \
                   xxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n \
                  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n \
                 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n \
                              xxxxxxx\n \
                              xxxxxxx\n \
                              xxxxxxx\n \
                              xxxxxxx\n \
                              \n \
                  \n \
                  x\n \
                 xxx\n \
                xxxxx\n \
               xxxxxxx\n \
              xxxxxxxxx\n \
             xxxxxxxxxxx\n \
            xxxxxxxxxxxxx\n \
           xxxxxxxxxxxxxxx\n \
          xxxxxxxxxxxxxxxxx\n \
               xxxxxxx\n \
               xxxxxxx\n \
               xxxxxxx\n \
               xxxxxxx\n \
               \n";
}

void ShrubberyCreationForm::action(void) const
{
	std::cout << SKY_BLUE << "*********************************************" << std::endl << C_RES << std::endl;
	std::string filename;
	filename = this->_target + "_shruberry";
	std::ofstream ofs(filename.c_str());
	try
	{
		if (!ofs)
			throw (std::exception());
		else
		{
			std::cout << SKY_BLUE << "I have drawn a tree ! checkout " << filename << " file"<< std::endl;
			ofs << draw_tree();
		}
	}
	catch (std::exception &e)
	{
		std::cout << "Error in file handling" << std::endl;
	}
	std::cout << std::endl << SKY_BLUE << "*********************************************" << C_RES << std::endl;
	return ;

	return ;
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const ShrubberyCreationForm & src)
{
	os << src.getTarget();
	return (os);
}

