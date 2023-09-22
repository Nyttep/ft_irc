#include "irc.hpp"

int	ft_atoi(const char *str)
{
	long long	res;
	int			sign;
	int			i;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] && ((str[i] >= '\t' && str[i] <= '\r')
			|| str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && res < 3000000000)
		res = res * 10 + (str[i++] - '0');
	res = res * sign;
	if (res < 0)
		return (-1);
	else if (res > 65535)
		return (-1);
	else
		return ((int)res);
}

void	ft_check_arg(int argc, char **argv)
{
	int i = 0;
	int port = ft_atoi(argv[1]);
	std::string password = argv[2];

	while (argv[1][i])
	{
		if (isdigit(argv[1][i]) == 0)
		{
			std::cerr << "Error: Non digit in Port number" << std::endl;
			exit(1);
		}
		i++;
	}
	if (port < 0 || port > 65535 || port <= 1024)
	{
		if (port >= 0 && port <= 1024)
		{
			std::cerr << "Error: System port" << std::endl;
		}
		else
		{
			std::cerr << "Error: Invalid Port value" << std::endl;
		}
		exit(1);
	}
	if (password.length() > 510)
	{
		std::cerr << "Error: Password too long" << std::endl;
		exit(1);
	}
}