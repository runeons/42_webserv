/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class_pattern_ovop.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 19:36:15 by tharchen          #+#    #+#             */
/*   Updated: 2021/07/11 21:21:22 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

RequestParser		&RequestParser::operator=(RequestParser const &rhs)
{
	static_cast<void>(rhs);
	return (*this);
}

std::ostream	&operator<<(std::ostream &o, RequestParser const &i)
{
	static_cast<void>(i);
	return (o);
}
