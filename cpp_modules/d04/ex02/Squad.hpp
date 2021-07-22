#ifndef SQUAD_HPP
# define SQUAD_HPP

# include "ISquad.hpp"

class Squad : public ISquad
{
	private:
		typedef struct		s_unit
		{
			ISpaceMarine*	unit;
			struct s_unit	*next;
			struct s_unit	*prev;
		}					t_unit;
		int				_nb_units;
		t_unit *		_lst_begin;
		void			lst_add_back(ISpaceMarine * new_unit);
		void			lst_clear(void);
		void			lst_cpy(const Squad &src);


	public:
		Squad();
		Squad(const Squad & src);
		virtual ~Squad();

		int				getNbUnits(void) const;
		void			setNbUnits(const int nb_units);
		t_unit *		getLst(void) const;
		void			setLst(t_unit * lst);

		int				getCount(void) const;
		ISpaceMarine *	getUnit(int nb) const;
		int				push(ISpaceMarine * new_unit);
		std::string		getAddress(void) const;
		std::string		getLstBeginAddress(void) const;
		std::string		getNbUnitsAddress(void) const;

		Squad			&operator=(const Squad & src);
};

std::ostream	&operator<<(std::ostream & os, const Squad & src);

#endif
