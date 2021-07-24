/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.parser.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 17:56:06 by tharchen          #+#    #+#             */
/*   Updated: 2021/07/22 21:38:20 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

int		RequestParser::unimplemented_headfield_data(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	std::string key(digest());
	DDOT();
	OWS();
	digest();
	ANYTEXT();
	std::map<std::string, std::string>::iterator it = this->_header_fields.begin();
	this->_header_fields.insert (it, std::pair<std::string, std::string>(key, digest()));
	OWS();
	return (SUCCESS);
}

int		RequestParser::implemented_headfield_data(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	std::string key(digest());
	DDOT();
	OWS();
	digest();
	TEXT();
	std::map<std::string, std::string>::iterator it = this->_header_fields.begin();
	this->_header_fields.insert (it, std::pair<std::string, std::string>(key, digest()));
	OWS();
	return (SUCCESS);
}

// host					: "Host" DDOT OWS TEXT OWS

int		RequestParser::host(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("Host") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	implemented_headfield_data();
	return (SUCCESS);
}

// accept_Charset			: "Accept-Charset" DDOT OWS ANYTEXT OWS

int		RequestParser::accept_Charset(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("Accept-Charset") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// accept_Encoding			: "Accept-Encoding" DDOT OWS ANYTEXT OWS

int		RequestParser::accept_Encoding(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("Accept-Encoding") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// accept_Language			: "Accept-Language" DDOT OWS ANYTEXT OWS

int		RequestParser::accept_Language(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("Accept-Language") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// authorization			: "Authorization" DDOT OWS ANYTEXT OWS

int		RequestParser::authorization(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("Authorization") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// from					: "From" DDOT OWS ANYTEXT OWS

int		RequestParser::from(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("From") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// accept					: "Accept" DDOT OWS ANYTEXT OWS

int		RequestParser::accept(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("Accept") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// if_Modified_Since		: "If-Modified-Since" DDOT OWS ANYTEXT OWS

int		RequestParser::if_Modified_Since(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("If-Modified-Since") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// proxy_Authorization		: "Proxy-Authorization" DDOT OWS ANYTEXT OWS

int		RequestParser::proxy_Authorization(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("Proxy-Authorization") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// range					: "Range" DDOT OWS ANYTEXT OWS

int		RequestParser::range(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("Range") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// referer					: "Referer" DDOT OWS ANYTEXT OWS

int		RequestParser::referer(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("Referer") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// unless					: "Unless" DDOT OWS ANYTEXT OWS

int		RequestParser::unless(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("Unless") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// user_Agent				: "User-Agent" DDOT OWS ANYTEXT OWS

int		RequestParser::user_Agent(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("User-Agent") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}


// unimplemented_headfield	: accept_Charset
// 							| accept_Encoding
// 							| accept_Language
// 							| authorization
// 							| from
// 							| accept
// 							| if_Modified_Since
// 							| proxy_Authorization
// 							| range
// 							| referer
// 							| unless
// 							| user_Agent
// 							;

int		RequestParser::unimplemented_headfield(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	try { accept_Charset(); }
	catch (std::exception &) {
		try { accept_Encoding(); }
		catch (std::exception &) {
			try { accept_Language(); }
			catch (std::exception &) {
				try { authorization(); }
				catch (std::exception &) {
					try { from(); }
					catch (std::exception &) {
						try { accept(); }
						catch (std::exception &) {
							try { if_Modified_Since(); }
							catch (std::exception &) {
								try { proxy_Authorization(); }
								catch (std::exception &) {
									try { range(); }
									catch (std::exception &) {
										try { referer(); }
										catch (std::exception &) {
											try { unless(); }
											catch (std::exception &) {
												user_Agent();
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return (SUCCESS);
}

// implemented_headfield	: host
// 							;

int		RequestParser::implemented_headfield(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	host();
	return (SUCCESS);
}

// headfield				: implemented_headfield
// 							| unimplemented_headfield
// 							;

int		RequestParser::headfield(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	try { implemented_headfield(); }
	catch (std::exception &) {
		unimplemented_headfield();
	}
	return (SUCCESS);
}

// group_headfield			:
// 							| headfield CRLF group_headfield
// 							;

int		RequestParser::group_headfield(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	try {
		if (headfield() == SUCCESS)
			CRLF(), group_headfield();
	}
	catch (std::exception &) { return (SUCCESS); }
	return (SUCCESS);
}


// group_content		:
// 						| CONTENT
// 						;

int		RequestParser::group_content(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	eatall();
	return (SUCCESS);
}

// method				: "GET"
// 						| "POST"
// 						| "DELETE"
// 						;

int		RequestParser::method(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat("GET") == SUCCESS)
	{
		this->_method = METHOD_GET;
		return (SUCCESS);
	}
	if (eat("POST") == SUCCESS)
	{
		this->_method = METHOD_POST;
		return (SUCCESS);
	}
	if (eat("DELETE") == SUCCESS)
	{
		this->_method = METHOD_DELETE;
		return (SUCCESS);
	}
	throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	// debug();
 std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;	return (FAILURE);
}

// request_target		: '/' ANYTEXT
// 						;

int		RequestParser::request_target(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	SLASH();
	try { TEXT(); }
	catch (std::exception) {}
	return (SUCCESS);
}

// HTTP_version			: "HTTP/" DIGIT '.' DIGIT
// 						;

int		RequestParser::HTTP_version(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat("HTTP/") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));
	digest();
	DIGIT();
	DOT();
	DIGIT();
	this->_http_version = digest();
	std::cout << "this->_http_version: [" << this->_http_version << "]" << std::endl;
	return (SUCCESS);
}

// line_request			: method SP request_target SP HTTP_version
// 						;

int		RequestParser::line_request(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	method();
	SP();
	OWS();
	digest();
	request_target();
	this->_resource = digest();
	std::cout << "this->_resource: [" << this->_resource << "]" << std::endl;
	SP();
	OWS();
	HTTP_version();
	OWS();
	return (SUCCESS);
}

// full_request					: line_request CRLF group_headfield CRLF group_content
// 								;

int		RequestParser::full_request(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	line_request();
	CRLF();
	group_headfield();
	// CRLF();
	// digest();
	// group_content();
	// this->_body = digest();
	return (SUCCESS);
}

// request						: full_request CRLF
// 								;

int		RequestParser::request(void)
{
	// debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	try
	{
		full_request();
		CRLF();
	}
	catch (std::exception & e)
	{
		// std::cout << "error: " << e.what() << std::endl;
		std::cout << "error: RequestParser: " << e.what() << std::endl;
	}
	return (SUCCESS);
}
