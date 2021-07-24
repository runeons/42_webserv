#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "webserv.hpp"

class Response
{
	private:
		std::map<int, std::string>	_headers_response;
		std::string					_page_content;

	public:
		Response();
		Response(const Response & src);
		virtual ~Response();

		std::map<int, std::string>	getHeadersResponse(void) const;
		void						setHeadersResponse(const std::map<int, std::string> headers_response);
		std::string					getPageContent(void) const;
		void						setPageContent(const std::string page_content);


		Response					&operator=(const Response & src);
};


#endif
