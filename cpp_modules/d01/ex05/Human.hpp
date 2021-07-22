#ifndef HUMAN_HPP
# define HUMAN_HPP
# include "Brain.hpp"

// DECLARATION
class Human
{
	private:
		Brain	const _brain;
	public:
		std::string	identify() const;
		Brain const & getBrain() const;
		Human();
		~Human();
};
#endif