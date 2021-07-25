/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.test.class.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 17:52:41 by tharchen          #+#    #+#             */
/*   Updated: 2021/07/22 23:37:46 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

void			RequestParser::init_parser_for_test(std::string request_test)
{
	this->_request_raw = request_test;
	this->_head = 0;
	this->_head_last_digest = 0;

	this->_method = METHOD_NONE;
}

void			RequestParser::tester(void)
{
	// tests for DOT
	std::cout << "tests for DOT ************************************************" << std::endl;
	{
		{
			std::string		valid_entry[] = { ".", "\.", "..", ".poqiwer", ".\r\n"};
			std::vector<std::string> list_request(valid_entry, valid_entry + sizeof(valid_entry) / sizeof(*valid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					DOT();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
		{
			std::string		invalid_entry[] = { "", " .", ";", "lel" };
			std::vector<std::string> list_request(invalid_entry, invalid_entry + sizeof(invalid_entry) / sizeof(*invalid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					DOT();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
	}
	std::cout << "**************************************************************" << std::endl << std::endl;
	// tests for SLASH
	std::cout << "tests for SLASH **********************************************" << std::endl;
	{
		{
			std::string		valid_entry[] = { "/", "\/", "//", "/asdf", "/."};
			std::vector<std::string> list_request(valid_entry, valid_entry + sizeof(valid_entry) / sizeof(*valid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					SLASH();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
		{
			std::string		invalid_entry[] = { "", " /", "asd/", "./", "\\/" };
			std::vector<std::string> list_request(invalid_entry, invalid_entry + sizeof(invalid_entry) / sizeof(*invalid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					SLASH();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
	}
	std::cout << "**************************************************************" << std::endl << std::endl;
	// tests for SP
	std::cout << "tests for SP *************************************************" << std::endl;
	{
		{
			std::string		valid_entry[] = { " ", "  " , "\ " , " laksdj "};
			std::vector<std::string> list_request(valid_entry, valid_entry + sizeof(valid_entry) / sizeof(*valid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					SP();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
		{
			std::string		invalid_entry[] = { "", "dfg ", ". ", "/ ", "\t " };
			std::vector<std::string> list_request(invalid_entry, invalid_entry + sizeof(invalid_entry) / sizeof(*invalid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					SP();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
	}
	std::cout << "**************************************************************" << std::endl << std::endl;
	// tests for HTAB
	std::cout << "tests for HTAB ***********************************************" << std::endl;
	{
		{
			std::string		valid_entry[] = { "\t", "\t\t" , "\t " , "\tlaksdj "};
			std::vector<std::string> list_request(valid_entry, valid_entry + sizeof(valid_entry) / sizeof(*valid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					HTAB();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
		{
			std::string		invalid_entry[] = { "", "dfg\t", ".\t", "\\t", " \t" };
			std::vector<std::string> list_request(invalid_entry, invalid_entry + sizeof(invalid_entry) / sizeof(*invalid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					HTAB();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
	}
	std::cout << "**************************************************************" << std::endl << std::endl;
	// tests for CR
	std::cout << "tests for CR *************************************************" << std::endl;
	{
		{
			std::string		valid_entry[] = { "\r", "\r\r" , "\r " , "\rlaksdj "};
			std::vector<std::string> list_request(valid_entry, valid_entry + sizeof(valid_entry) / sizeof(*valid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					CR();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
		{
			std::string		invalid_entry[] = { "", "dfg\r", ".\r", "\\r", " \r" };
			std::vector<std::string> list_request(invalid_entry, invalid_entry + sizeof(invalid_entry) / sizeof(*invalid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					CR();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
	}
	std::cout << "**************************************************************" << std::endl << std::endl;
	// tests for LF
	std::cout << "tests for LF *************************************************" << std::endl;
	{
		{
			std::string		valid_entry[] = { "\n", "\n\n" , "\n " , "\nlaksdj "};
			std::vector<std::string> list_request(valid_entry, valid_entry + sizeof(valid_entry) / sizeof(*valid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					LF();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
		{
			std::string		invalid_entry[] = { "", "dfg\n", ".\n", "\\n", " \n" };
			std::vector<std::string> list_request(invalid_entry, invalid_entry + sizeof(invalid_entry) / sizeof(*invalid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					LF();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
	}
	std::cout << "**************************************************************" << std::endl << std::endl;
	// tests for DDOT
	std::cout << "tests for DDOT ***********************************************" << std::endl;
	{
		{
			std::string		valid_entry[] = { ":", "\:", "::", ":poqiwer", ":\r\n"};
			std::vector<std::string> list_request(valid_entry, valid_entry + sizeof(valid_entry) / sizeof(*valid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					DDOT();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
		{
			std::string		invalid_entry[] = { "", " :", ";", ";:", "lel" };
			std::vector<std::string> list_request(invalid_entry, invalid_entry + sizeof(invalid_entry) / sizeof(*invalid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					DDOT();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
	}
	std::cout << "**************************************************************" << std::endl << std::endl;
	// tests for HYPHEN
	std::cout << "tests for HYPHEN *********************************************" << std::endl;
	{
		{
			std::string		valid_entry[] = { "-", "\-", "--", "-poqiwer", "-\r\n"};
			std::vector<std::string> list_request(valid_entry, valid_entry + sizeof(valid_entry) / sizeof(*valid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					HYPHEN();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
		{
			std::string		invalid_entry[] = { "", " -", ";", ";-", "lel" };
			std::vector<std::string> list_request(invalid_entry, invalid_entry + sizeof(invalid_entry) / sizeof(*invalid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					HYPHEN();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
	}
	std::cout << "**************************************************************" << std::endl << std::endl;
	// tests for CRLF
	std::cout << "tests for CRLF ***********************************************" << std::endl;
	{
		{
			std::string		valid_entry[] = { "\r\n", "\\r\n", "\r\n\r\n", "\r\npoqiwer", "\r\n\r\n"};
			std::vector<std::string> list_request(valid_entry, valid_entry + sizeof(valid_entry) / sizeof(*valid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					CRLF();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
		{
			std::string		invalid_entry[] = { "", " \r\n", ";", "\r", "\r\t", "\n", ";\r\n", "lel" };
			std::vector<std::string> list_request(invalid_entry, invalid_entry + sizeof(invalid_entry) / sizeof(*invalid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					CRLF();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
	}
	std::cout << "**************************************************************" << std::endl << std::endl;
	// tests for ALPHA
	std::cout << "tests for ALPHA **********************************************" << std::endl;
	{
		{
			std::string		valid_entry[] = { "a", "z", "A", "Z", "aljkh", "zljkh", "Aljkh", "Zljkh", "askdljfh", "JKAHDSHlkjasld", "ajshdkasJK889" };
			std::vector<std::string> list_request(valid_entry, valid_entry + sizeof(valid_entry) / sizeof(*valid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					ALPHA();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
		{
			std::string		invalid_entry[] = { "" };
			std::vector<std::string> list_request(invalid_entry, invalid_entry + sizeof(invalid_entry) / sizeof(*invalid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					ALPHA();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
	}
	std::cout << "**************************************************************" << std::endl << std::endl;
	// tests for DIGIT
	std::cout << "tests for DIGIT **********************************************" << std::endl;
	{
		{
			std::string		valid_entry[] = { "" };
			std::vector<std::string> list_request(valid_entry, valid_entry + sizeof(valid_entry) / sizeof(*valid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					DIGIT();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
		{
			std::string		invalid_entry[] = { "" };
			std::vector<std::string> list_request(invalid_entry, invalid_entry + sizeof(invalid_entry) / sizeof(*invalid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					DIGIT();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
	}
	std::cout << "**************************************************************" << std::endl << std::endl;
	// tests for ALPHA_DIGIT_HYPHEN
	std::cout << "tests for ALPHA_DIGIT_HYPHEN *********************************" << std::endl;
	{
		{
			std::string		valid_entry[] = { "" };
			std::vector<std::string> list_request(valid_entry, valid_entry + sizeof(valid_entry) / sizeof(*valid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					ALPHA_DIGIT_HYPHEN();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
		{
			std::string		invalid_entry[] = { "" };
			std::vector<std::string> list_request(invalid_entry, invalid_entry + sizeof(invalid_entry) / sizeof(*invalid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					ALPHA_DIGIT_HYPHEN();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
	}
	std::cout << "**************************************************************" << std::endl << std::endl;
	// tests for group_ALPHA_DIGIT_HYPHEN
	std::cout << "tests for group_ALPHA_DIGIT_HYPHEN ***************************" << std::endl;
	{
		{
			std::string		valid_entry[] = { "" };
			std::vector<std::string> list_request(valid_entry, valid_entry + sizeof(valid_entry) / sizeof(*valid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					group_ALPHA_DIGIT_HYPHEN();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
		{
			std::string		invalid_entry[] = { "" };
			std::vector<std::string> list_request(invalid_entry, invalid_entry + sizeof(invalid_entry) / sizeof(*invalid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					group_ALPHA_DIGIT_HYPHEN();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
	}
	std::cout << "**************************************************************" << std::endl << std::endl;
	// tests for TEXT
	std::cout << "tests for TEXT ***********************************************" << std::endl;
	{
		{
			std::string		valid_entry[] = { "" };
			std::vector<std::string> list_request(valid_entry, valid_entry + sizeof(valid_entry) / sizeof(*valid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					TEXT();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
		{
			std::string		invalid_entry[] = { "" };
			std::vector<std::string> list_request(invalid_entry, invalid_entry + sizeof(invalid_entry) / sizeof(*invalid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					TEXT();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
	}
	std::cout << "**************************************************************" << std::endl << std::endl;
	// tests for OWS
	std::cout << "tests for OWS ************************************************" << std::endl;
	{
		{
			std::string		valid_entry[] = { "" };
			std::vector<std::string> list_request(valid_entry, valid_entry + sizeof(valid_entry) / sizeof(*valid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					OWS();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
		{
			std::string		invalid_entry[] = { "" };
			std::vector<std::string> list_request(invalid_entry, invalid_entry + sizeof(invalid_entry) / sizeof(*invalid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					OWS();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
	}
	std::cout << "**************************************************************" << std::endl << std::endl;
	// tests for VCHAR
	std::cout << "tests for VCHAR **********************************************" << std::endl;
	{
		{
			std::string		valid_entry[] = { "" };
			std::vector<std::string> list_request(valid_entry, valid_entry + sizeof(valid_entry) / sizeof(*valid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					VCHAR();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
		{
			std::string		invalid_entry[] = { "" };
			std::vector<std::string> list_request(invalid_entry, invalid_entry + sizeof(invalid_entry) / sizeof(*invalid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					VCHAR();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
	}
	std::cout << "**************************************************************" << std::endl << std::endl;
	// tests for ANYTEXT
	std::cout << "tests for ANYTEXT ********************************************" << std::endl;
	{
		{
			std::string		valid_entry[] = { "" };
			std::vector<std::string> list_request(valid_entry, valid_entry + sizeof(valid_entry) / sizeof(*valid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					ANYTEXT();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
		{
			std::string		invalid_entry[] = { "" };
			std::vector<std::string> list_request(invalid_entry, invalid_entry + sizeof(invalid_entry) / sizeof(*invalid_entry));
			for (vector_iterator it = list_request.begin(); it != list_request.end(); it++)
			{
				std::cout << "[ test \'" << *it << "\'] -> " ;
				init_parser_for_test(*it);
				try
				{
					ANYTEXT();
					std::cout << "digested: [" << digest() << "]" << std::endl;
				}
				catch (std::exception & e) { std::cout << "no match found !" << std::endl; }
			}
		}
	}
	std::cout << "**************************************************************" << std::endl << std::endl;
}
