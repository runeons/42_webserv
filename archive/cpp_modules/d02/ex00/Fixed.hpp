#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include "color.hpp"

/*
• Membre privés :
◦ Un int pour stocker la valeur a point fixe
◦ Une variable statique constante de type int pour stocker le nombre de bits
fractionnels. Cette variable vaudra toujours 8.
• Membres publics :
◦ Un constructeur par défaut qui initialise la valeur a point fixe à 0
◦ Un destructeur.
◦ Un constructeur par copie.
◦ Un overload d’opérateur d’assignation.
◦ Une fonction membre int getRawBits(void) const; qui renvoie la valeur
brute du nombre à point fixe.
◦ Une fonction membre void setRawBits(int const raw); qui set la valeur
du nombre à point fixe.
*/

class Fixed
{
	private:
		int 				_rawBits;
		static const int	_nbBits = 8;

	public:
		Fixed();
		Fixed(const Fixed&);
		~Fixed();
		Fixed &operator=(const Fixed&);
		int getRawBits(void) const;
		void setRawBits(int const raw);
};

#endif