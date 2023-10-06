/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:07 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/06 15:00:08 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

std::vector<std::string>	collect_arguments(std::string string)
{
	std::vector<std::string>	vector;
	std::string					buff;
	size_t						begin = 0, end = 0;

	while ((end = string.find(',', begin)) != std::string::npos)
	{
		buff = string.substr(begin, end - begin);
		vector.push_back(buff);
		begin = end +1; 
	}
    buff = string.substr(begin, end - begin);
    vector.push_back(buff);
	return (vector);
}

bool	correct_nick(std::string name)
{
	if (chantypes(name[0]) == true)
		return (false);
	if (name[0] == '$' || name[0] == '#' || name[0] == '&' || name[0] == '%' || (isdigit(name[0])))
	{
		return (false);
	}
	for (size_t i = 0; i != name.length(); ++i)
	{
		if (name[i] == ' ' || name[i] == ','|| name[i] == '.' || name[i] == '*' || \
			name[i] == '?' || name[i] == '!' || name[i] == '@')
		{
			return (false);
		}
	}
	return (true);
}

bool	correct_chan(std::string name)
{
	if (chantypes(name[0]) == false)
		return (false);
	if (name.size() == 1)
		return (false);
	if (name.find('\a') != std::string::npos)
		return (false);
	for (size_t i = 0; i != name.length(); ++i)
	{
		if (name[i] == ' ' || name[i] == ',')
				return (false);
	}
	return (true);
}

std::string	store_message(Command &command)
{
	std::string message;
	for (size_t i = 1; i != command.getParams().size(); ++i)
	{
		if (!command.getParams()[i].empty())
		{
			if (!message.empty())
				message += " ";
			message += (command.getParams()[i]);
		}
	}
	return (message);
}

std::string empty_param(std::vector<std::string> param, size_t i)
{
	if (i >= param.size())
		return ("");
	return (std::string(" ") + param[i]);
}

bool	analyse_param(std::string param, Command &command)
{
	if (param.size() != 2)
	{
		sendAll(RPL_INVALIDMODEPARAM(setUserAddress(*command.getSource()), command.getSource()->getNName(), command.getParams()[0], param, "",  " :One mode char ((+/-)(i/t/k/l/o))\r\n"), *command.getSource());
		return (false);
	}
	if (param.empty())
	{
		sendAll(RPL_INVALIDMODEPARAM(setUserAddress(*command.getSource()), command.getSource()->getNName(), command.getParams()[0], param, "", " :Incorrect mode char ((+/-)(i/t/k/l/o))\r\n"), *command.getSource());
		return (false);
	}
	if (param[0] != '+' && param[0] != '-')
	{
		sendAll(RPL_INVALIDMODEPARAM(setUserAddress(*command.getSource()), command.getSource()->getNName(), command.getParams()[0], param, "", " :Incorrect mode char ((+/-)(i/t/k/l/o))\r\n"), *command.getSource());
		return (false);
	}
	return (true);
}

std::string	itoa(int value)
{
	std::stringstream stream;
	
	stream << value;
	return (stream.str());
}

void	handshake(Command &command, Server &server)
{
	sendAll(RPL_WELCOME(setUserAddress(*command.getSource()), command.getSource()->getNName(), command.getSource()->getNName()), *command.getSource());
	sendAll(RPL_YOURHOST(setUserAddress(*command.getSource()), command.getSource()->getNName()), *command.getSource());
	sendAll(RPL_CREATED(setUserAddress(*command.getSource()), command.getSource()->getNName(), server.getTime()), *command.getSource());
	sendAll(RPL_MYINFO(setUserAddress(*command.getSource()), command.getSource()->getNName(), CHANMODES), *command.getSource());
	sendAll(RPL_ISUPPORT(setUserAddress(*command.getSource()), command.getSource()->getNName(), "CASEMAPPING=" + CASEMAPPING), *command.getSource());
	sendAll(RPL_ISUPPORT(setUserAddress(*command.getSource()), command.getSource()->getNName(), "CHANTYPES=" + CHANTYPES), *command.getSource());
	sendAll(RPL_ISUPPORT(setUserAddress(*command.getSource()), command.getSource()->getNName(), "CHANLIMIT=" + CHANLIMIT), *command.getSource());
	sendAll(RPL_ISUPPORT(setUserAddress(*command.getSource()), command.getSource()->getNName(), "CHANMODES=" + CHANMODES), *command.getSource());
	sendAll(RPL_ISUPPORT(setUserAddress(*command.getSource()), command.getSource()->getNName(), "PREFIX=" + PREFIX), *command.getSource());
	sendAll(RPL_ISUPPORT(setUserAddress(*command.getSource()), command.getSource()->getNName(), "MODES=" + itoa(MODES)), *command.getSource());
	sendAll(RPL_ISUPPORT(setUserAddress(*command.getSource()), command.getSource()->getNName(), "TARGMAX=" + TARGMAX), *command.getSource());
	sendAll(RPL_ISUPPORT(setUserAddress(*command.getSource()), command.getSource()->getNName(), "NICKLEN=" + itoa(NICKLEN)), *command.getSource());
	sendAll(RPL_ISUPPORT(setUserAddress(*command.getSource()), command.getSource()->getNName(), "USERLEN=" + itoa(USERLEN)), *command.getSource());
	sendAll(RPL_ISUPPORT(setUserAddress(*command.getSource()), command.getSource()->getNName(), "CHANNELLEN=" + itoa(CHANNELLEN)), *command.getSource());
	sendAll(RPL_ISUPPORT(setUserAddress(*command.getSource()), command.getSource()->getNName(), "KICKLEN=" + itoa(KICKLEN)), *command.getSource());
	sendAll(RPL_ISUPPORT(setUserAddress(*command.getSource()), command.getSource()->getNName(), "TOPICLEN=" + itoa(TOPICLEN)), *command.getSource());
}

std::vector<std::string>	collect_mode_char(std::string str)
{
	std::vector<std::string>	vec;
	std::string			 		res;
	size_t i = 0;
	while (str[i])
	{
		if (str[i] == '-')
		{
			i++;
			while (str[i] && str[i] != '+')
			{
				if (str[i] == '-')
					i++;
				else
				{
					res = std::string("-") + str[i];
					vec.push_back(res);
					if (i != str.size())
						i++;
				}
			}

		}
		else if (str[i] == '+')
		{
			i++;
			while (str[i] && str[i] != '-')
			{
				if (str[i] == '+')
					i++;
				else
				{
					res = std::string("+") + str[i];
					if(i != str.size())
						i++;
					vec.push_back(res);
				}
			}
		}
		else
		{
			res = std::string("+") + str[i];
			if (i != str.size())
				i++;
			vec.push_back(res);
		}
	}
	return (vec);
}

std::vector<std::string>	getParamsMODE(std::vector<std::string> getParams)
{
	std::vector<std::string>	ret;
	for (size_t i = 2; i < getParams.size(); i++)
	{
		ret.push_back(getParams[i]);
	}
	return (ret);
}