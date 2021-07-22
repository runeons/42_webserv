#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "webserv.hpp"

class Client
{
	private:
		SOCKET		_socket;

		// errors
		std::map<int, std::string> _error_msg;
		std::map<int, std::string> _error_body;

		// requete
		std::string	_request; // full request
		std::string	_method;
		std::string	_ressource;
		std::string	_version;

		// reponse
		std::string	_full_path;

	public:
		Client();
		Client(const Client & src);
		virtual ~Client();

		SOCKET		getSocket(void) const;
		void		setSocket(const SOCKET client_socket);
		std::string	getRequest(void) const;
		void		setRequest(const std::string request);

		void		treat_client(void);
		void		receive_request(void);
		void		check_request(void);
		void		generate_response_header(void);
		void		generate_error_body(int);
		void		construct_full_path(void);

		std::map<int, std::string>	create_map_msg();
		std::map<int, std::string>	create_map_body();

		Client		&operator=(const Client & src);
};


#endif
