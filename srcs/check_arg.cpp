/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:42:17 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/06 10:25:16 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_check_arg(char **argv)
{
	int i = 0;
	std::string password = argv[2];
	std::string ports = argv[1];

	if (ports.empty() || password.empty())
	{
		std::cerr << "Error: Empty argument" << std::endl;
		exit (1);
	}
	while (argv[1][i])
	{
		if (isdigit(argv[1][i]) == 0)
		{
			std::cerr << "Error: Non digit in Port number" << std::endl;
			exit(1);
		}
		i++;
	}
	int port = ft_atoi(argv[1]);
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
	if (password.length() > 255)
	{
		std::cerr << "Error: Password too long" << std::endl;
		exit(1);
	}
	if (password.find('\a') != std::string::npos || password.find('\t') != std::string::npos || password.find(' ') != std::string::npos \
		|| password.find('\n') != std::string::npos || password.find('\v') != std::string::npos || password.find('\f') != std::string::npos \
		|| password.find('\r') != std::string::npos)
	{
			std::cerr << "Error: Whitespaces forbidden" << std::endl;
			exit (1);
	}
}
