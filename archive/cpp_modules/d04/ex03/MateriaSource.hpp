#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{
	private:
		AMateria * _inventory[4];
	public:
		MateriaSource();
		MateriaSource(const MateriaSource & src);
		virtual ~MateriaSource();

		void	learnMateria(AMateria * m);
		AMateria *createMateria(std::string const & type);

		int		countInventory();

		MateriaSource&operator=(const MateriaSource & src);
};

#endif
