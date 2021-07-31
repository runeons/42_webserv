/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response_class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 18:41:45 by tsantoni          #+#    #+#             */
/*   Updated: 2021/07/31 11:59:23 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <webserv.hpp>

// ********************************************* set page content if error *********************************************

void	Response::generate_error_content(void)
{
	if (_status_code != 200)
		_page_content = _error_content[_status_code];
}

// ********************************************* create body *********************************************

void	Response::GET_create_body(void)
{
	_response_body = _page_content;

	// if CGI (dans quels cas ?? A reflechir)
	// std::cout << C_G_YELLOW << "Let's start with cgi !" << C_RES << std::endl;
	// Cgi *cgi = new Cgi(_request);
	// cgi->launch();
	// delete cgi;
	// std::cout << C_G_YELLOW << "We are finished with cgi !" << C_RES << std::endl;

}

// ********************************************* generate response headers *********************************************

void		Response::generate_response_header(void)
{
	_response_header = generate_status_line();
	_response_header += r_header_server();
	_response_header += r_header_date();
	_response_header += r_header_connection();
	_response_header += r_header_content_length();
	_response_header += r_header_content_type();

	return ;
}

// ********************************************* concatenate response *********************************************

void	Response::concatenate_response()
{
	_response = _response_header + PAT_CRLF + _response_body;
}

// ********************************************* main - generate *********************************************

void	Response::generate(void)
{
	generate_error_content();
	GET_create_body(); // from page_content
	generate_response_header(); // from status_code, page_content and full_path
	concatenate_response();
}
