/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 08:30:32 by tsantoni          #+#    #+#             */
/*   Updated: 2021/06/04 13:46:43 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(int ac, char **av)
{

	int	i;
	int	j;

	i = 0;
	j = -1;
	if (ac == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	else
	{
		while (av[++i])
		{
			j = -1;
			while (av[i][++j])
				std::cout << (char)std::toupper(av[i][j]);
		}
		std::cout << std::endl;
	}
	return (0);
}