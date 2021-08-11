/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 15:12:22 by tharchen          #+#    #+#             */
/*   Updated: 2021/08/09 14:26:27 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSER_HPP
# define CONFIGPARSER_HPP

#include <webserv.hpp>

#ifndef CONFIG_HPP
class Config;
#endif

extern int deep;

class ConfigParser
{
	private:
		std::string			_config_raw;
		size_t				_head;
		size_t				_head_last_digest;
		std::vector<Config> _servers_config; // confiture de figues :D
		ConfigParser(void);  // constructor

		// debug
		void	bc_s(void);
		void	debug_print_line(void);
		void	bc_p(void);
		void	print_center_line(int fn, int msg);

		// parsing tools
		int		eat(int to_eat);
		int		eat_debug(int to_eat);
		int		eat_nodebug(int to_eat);
		void	init_digest(void);
		void	digest(std::string & target);

		// lexing functions
		void	ALPHA(void);
		void	ALPHA_UPPER(void);
		void	DIGIT(void);
		void	TDIGIT(void);
		void	LF(void);
		void	SP(void);
		void	HTAB(void);
		void	CHAR(int c);
		void	RANGE(int start, int end);

		// tokens functions
		void	server_token(void);
		void	return_token(void);
		void	token_301(void);
		void	host_token(void);
		void	port_token(void);
		void	server_name_token(void);
		void	max_client_body_token(void);
		void	root_token(void);
		void	error_token(void);
		void	location_token(void);
		void	uri_token(void);
		void	index_token(void);
		void	autoindex_token(void);
		void	alias_token(void);
		void	method_token(void);
		void	upload_token(void);
		void	on_token(void);
		void	off_token(void);

		// parsing functions
		void	OWS(void);
		void	OWSON(void);
		void	token(void);
		void	dec_octet(void);
		void	port_no(void);
		void	IPv4address(void);
		void	unreserved(void);
		void	name(void);
		void	number(void);
		void	sub_delims(void);
		void	pchar(void);
		void	segment_nz(void);
		void	segment(void);
		void	path(void);
		void	file(void);
		void	status_code(void);
		void	item_error(void);
		void	index(void);
		void	uri(void);
		void	server_root(void);
		void	location_root(void);
		void	autoindex(void);
		void	alias(void);
		void	return301(void);
		void	method(void);
		void	upload(void);
		void	item_location(void);
		void	host(void);
		void	port(void);
		void	server_name(void);
		void	max_client_body(void);
		void	error(void);
		void	location(void);
		void	item(void);
		void	server(void);
		void	config(void);
	public:
		ConfigParser(std::string file);  // params constructor
		~ConfigParser(void); // destructor
		void	start_parsing(void); // entry point
		void	print_info(void) const;
		const std::vector<Config> & get__servers_config(void) const;
};

#endif
