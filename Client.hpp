#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "webserv.hpp"

class Client
{
	private:
		SOCKET		_socket;
		std::string	_address;
		std::string	_request;


	public:
		Client();
		Client(const Client & src);
		virtual ~Client();

		SOCKET		getSocket(void) const;
		void		setSocket(const SOCKET client_socket);
		std::string	getAddress(void) const;
		void		setAddress(const std::string address);
		std::string	getRequest(void) const;
		void		setRequest(const std::string request);

		void		treat_client(void);
		void		receive_request(void);
		void		check_request(void);

		Client		&operator=(const Client & src);
};


#endif
