/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_backtrace.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 02:26:34 by tharchen          #+#    #+#             */
/*   Updated: 2021/07/24 03:16:19 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

// 0   a.out                               0x00000001075efaa4 _Z2bcv + 36
// 1   a.out                               0x00000001075ef9bd _Z5fun_gv + 13
// 2   a.out                               0x00000001075efbd9 _Z5fun_fv + 9
// 3   a.out                               0x00000001075efbe9 _Z5fun_ev + 9
// 4   a.out                               0x00000001075efbf9 _Z5fun_dv + 9
// 5   a.out                               0x00000001075efc09 _Z5fun_cv + 9
// 6   a.out                               0x00000001075efc19 _Z5fun_bv + 9
// 7   a.out                               0x00000001075efc2d _Z5fun_av + 13
// 8   a.out                               0x00000001075efdd4 main + 20

inline void bc(void)
{
	void	*array[1024];
	char	**trace;
	int		size;

	size = backtrace(array, 1024);
	trace = backtrace_symbols(array, size);
	if (trace != NULL)
	{
		for (int i = 1; i < size - 3; i++)
		{
			int j = 62;
			for (;trace[i][j] && trace[i][j] != ' '; j++) {}
			trace[i][j - 1] = '\0';
			std::cout << &trace[i][62] << std::endl;
		}
		delete (trace);
	}
}

class LexerException: public std::exception
{
	private:
		std::string _msg;
	public:
		LexerException(std::string msg): _msg(msg) {}  // constructor
		virtual ~LexerException(void) throw() {} // destructor
		virtual const char *what() const throw() { return (this->_msg.c_str()); }
};

void fun_g(void)
{
	bc(); throw (Exceptions::LexerException("fuck, it\'s wrong !"));
}

void fun_f(void) { fun_g(); }
void fun_e(void) { fun_f(); }
void fun_d(void) { fun_e(); }
void fun_c(void) { fun_d(); }
void fun_b(void) { fun_c(); }
void fun_a(void)
{
	try
	{
		fun_b();
	}
	catch (std::exception & e)
	{
		std::cout << "error: " << e.what() << std::endl;
	}
}

int		main(void)
{
	fun_a();
	return (0);
}
