# include "Convert.hpp"

// Default constructor
Convert::Convert(void)
{
	this->_litteral = "";
	this->_value = 0;
	this->_precision = 0;
	return ;
}

bool isDigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

bool isAlpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

bool isPrintable(char c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

void Convert::checkInput(void)
{
	// int	i = 0;
	return;
}

int		isLastCharOK(std::string s)
{
	if (s[s.length() - 1] == 'f' || isDigit(s[s.length() - 1]))
	{
		if (s[s.length() - 1] == 'f' && !isDigit(s[s.length() - 2]))
			return (0);
		return (1);
	}
	return (0);
}

int		isFirstCharOK(std::string s)
{
	if (s[0] == '-' || isDigit(s[0]))
		return (1);
	return (0);
}

int		areMidCharsOK(std::string s)
{
	for (size_t i = 1; i < s.length() - 1; i++)
	{
		if (s[i] != '.' && isDigit(s[i]) == 0)
			return (0);
	}
	return (1);
}

int		countDot(std::string s)
{
	int	n = 0;

	for (size_t i = 0; i < s.length(); i++)
	{
		if (s[i] == '.')
			n++;
	}
	return (n);
}

void Convert::fillValue(void)
{
	if (this->_litteral.length() == 0 || (this->_litteral.length() == 1 && !isDigit(this->_litteral[0])))
		throw (Convert::NotValidFormat());
	else if (isInf() == 1 || isNan() || (this->_litteral.length() == 1 && isDigit(this->_litteral[0])))
		this->_value = strtod(this->_litteral.c_str(), NULL);
	else if (isLastCharOK(this->_litteral) == 1 && isFirstCharOK(this->_litteral) == 1 && areMidCharsOK(this->_litteral) && (countDot(this->_litteral) == 1 || countDot(this->_litteral) == 0))
		this->_value = strtod(this->_litteral.c_str(), NULL);
	else
	{
		std::cout << isLastCharOK(this->_litteral) << std::endl;
		std::cout << isFirstCharOK(this->_litteral) << std::endl;
		std::cout << areMidCharsOK(this->_litteral) << std::endl;
		std::cout << "HERE" << std::endl;
		throw (Convert::NotValidFormat());
	}
	if (countDot(this->_litteral) == 0)
	{
		this->_precision = 1;
		return ;
	}
	int	p = 0;
	for (size_t i = this->_litteral.length() - 1; i >= 0; i--)
	{
		if (this->_litteral[i] == '.')
			break ;
		if (isDigit(this->_litteral[i]) == 1)
			p++;
	}
	// std::cout << "precision : " << p << std::endl;
	this->_precision = p;
}

// Parametric constructor (std::string)
Convert::Convert(std::string litteral) : _litteral(litteral)
{
	this->_value = 0;
	this->_precision = 0;
	return ;
}

// Copy constructor
Convert::Convert(const Convert& src)
{
	*this = src;
	return;
}

// Destructor
Convert::~Convert(void)
{
	return;
}

// Assignation operator
Convert &	Convert::operator=(const Convert& rhs)
{
	if (this != &rhs)
	{
		this->_precision = rhs.getPrecision();
		this->_value = rhs.getValue();
		this->_litteral = rhs.getLitteral();
	}
	return (*this);
}

// getters and setters (non static attributes)
double Convert::getValue(void) const
{
	return (this->_value);
}

std::string Convert::getLitteral(void) const
{
	return (this->_litteral);
}

double Convert::getPrecision(void) const
{
	return (this->_precision);
}

bool	Convert::isNan(void)
{
	if (this->_litteral == "nanf" || this->_litteral == "nan")
		return (1);
	return (0);
}

bool	Convert::isInf(void)
{
	if (this->_litteral == "-inff" || this->_litteral == "+inff"
	 || this->_litteral == "-inf" || this->_litteral == "+inf")
		return (1);
	return (0);
}

bool	Convert::isNeg(void)
{
	if (this->_litteral[0] == '-')
		return (1);
	return (0);
}

void Convert::toChar(void)
{
	std::cout << GREEN_TREE << "char: ";
	if (isNan() || isInf())
		std::cout << "impossible" << std::endl;
	else if (!isPrintable(this->_value))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "\'" << static_cast<char>(this->_value) << "\'" << std::endl;
	std::cout << C_RES;
	return ;
}

void Convert::toInt(void)
{
	std::cout << GREEN_TREE << "int: ";
	if (isNan() || isInf())
		std::cout << "impossible" << std::endl;
	else if (this->_value < -2147483648 || this->_value > 2147483647)
		std::cout << "out of boundaries" << std::endl;
	else
		std::cout << static_cast<int>(this->_value) << std::endl;
	std::cout << C_RES;
	return ;
}

void Convert::toFloat(void)
{
	std::cout << GREEN_TREE << "float: ";
	if (isNan())
		std::cout << this->_value;
	else if (isInf() && isNeg())
		std::cout << this->_value;
	else if (isInf())
		std::cout << "+" << this->_value;
	else if (this->_precision > 16)
		std::cout << std::fixed << std::setprecision(16) << static_cast<float>(this->_value);
	else
		std::cout << std::fixed << std::setprecision(this->_precision) << static_cast<float>(this->_value);
	std::cout << "f" << std::endl;
	std::cout << C_RES;
	return ;
}

void Convert::toDouble(void)
{
	std::cout << GREEN_TREE << "double: ";
	if (isNan())
		std::cout << "nan" << std::endl;
	else if (isInf() && isNeg())
		std::cout << this->_value << std::endl;
	else if (isInf())
		std::cout << "+" << this->_value << std::endl;
	else if (this->_precision > 47)
		std::cout << std::fixed << std::setprecision(47) << static_cast<double>(this->_value) << std::endl;
	else
		std::cout << std::fixed << std::setprecision(this->_precision) << static_cast<double>(this->_value) << std::endl;
	std::cout << C_RES;
	return ;
}

void Convert::convert(void)
{
	try
	{
		fillValue();
	}
	catch (Convert::NotValidFormat &e)
	{
		std::cout << RED_B << "Error:" << WHITE_B << " not a valid number format" <<  C_RES << std::endl;
		return;
	}
	Convert::toChar();
	Convert::toInt();
	Convert::toFloat();
	Convert::toDouble();
	return ;
}
