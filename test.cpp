/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 18:00:33 by tharchen          #+#    #+#             */
/*   Updated: 2021/08/03 11:08:37 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector>

int		main(void)
{
	std::string s("visible\0invisible");

	std::cout << "[" << s << "]" << std::endl;
	std::cout << "length  : " << s.length() << std::endl;
	std::cout << "size    : " << s.size() << std::endl;
	std::cout << "capacity: " << s.capacity() << std::endl;

	s += "iseeyou\0superinvisible";

	std::cout << "[" << s << "]" << std::endl;
	std::cout << "length  : " << s.length() << std::endl;
	std::cout << "size    : " << s.size() << std::endl;
	std::cout << "capacity: " << s.capacity() << std::endl;

	s += ";aklsdfja;ksldjfakl;sdfjkla;sdjf;kalsdf";

	std::cout << "[" << s << "]" << std::endl;
	std::cout << "length  : " << s.length() << std::endl;
	std::cout << "size    : " << s.size() << std::endl;
	std::cout << "capacity: " << s.capacity() << std::endl;

	return (0);
}
