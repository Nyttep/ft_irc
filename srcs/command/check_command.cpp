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
	return (vector);
}

bool	correct_nick_chan(std::string name)
{
	if (chantypes(name[0]) == true)
	{
		for (size_t i = 0; i != name.length(); ++i)
		{
			if (name[i] == ' ' || name[i] == '^G' || name[i] == ',')
			{
				std::cerr << "redirection  432" << std::endl;
				return (false);
			}
		}
	}
	else
	{
		if (name[0] == '$' || name[0] == '#' || name[0] == '&' || name[0] == '%' || (isdigit(name[0])))
		{
			std::cerr << "Redirection 432" << std::endl;
			return (false);
		}
		for (size_t i = 0; i != name.length(); ++i)
		{
			if (name[i] == ' ' || name[i] == ','|| name[i] == '.' || name[i] == '*' || \
				name[i] == '?' || name[i] == '!' || name[i] == '@')
			{
				std::cerr << "Redirection 432" << std::endl;
				return (false);
			}
		}
	}
	return (true);
}

std::string	store_message(Command command)
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

std::string empty_param(std::vector<std::string> params, size_t i)
{
	if (params.size() < i)
		return ("");
	return (params[i]);
}

bool	analyse_param(std::string param)
{
	if (param.size() != 2)
	{
		sendAll(RPL_INVALIDMODEPARAN("@"+command.getSource(), command.getParams()[0], command.getParams()[1], empty_param(command.getParams(), 2), " : One mode char ((+/-)(i/t/k/l/o))\r\n"), command.getSource());
		return (false);
	}
	if (param[0] != '+' && param[0] != '-')
	{
		sendAll(RPL_INVALIDMODEPARAN("@"+command.getSource(), command.getParams()[0], command.getParams()[1], empty_param(command.getParams(), 2), " : Incorrect mode char ((+/-)(i/t/k/l/o))\r\n"), command.getSource());
		return (false);
	}
	return (true);
}

std::string	DateCreation()
{
	std::string str;
    std::stringstream stream;
	std::time_t time = std::time(NULL);

	std::tm *tm = std::localtime(&time);
    stream << tm->tm_hour << ":" << tm->tm_min << " " << tm->tm_mday << "/" << 1 + tm->tm_mon << "/" << tm->tm_year - 100;
    str += stream.str();
    return (str);
}

void	handshake(Command command, Server server)
{
	sendAll(RPL_WELCOME(SERVERNAME, command.getSource().getNName()), command.getSource());
	sendAll(RPL_YOURHOST(SERVERNAME), command.getSource());
	sendAll(RPL_CREATED(SERVERNAME, server.getTime()), command.getSource());
	sendAll(RPL_MYINFO(SERVERNAME, CHANMODES), command.getSource());
	sendAll(RPL_ISUPPORT(SERVERNAME, NETWORK), command.getSource());
	sendAll(RPL_ISUPPORT(SERVERNAME, "CASEMAPPING=" + CASEMAPPING), command.getSource());
	sendAll(RPL_ISUPPORT(SERVERNAME, "CHANTYPES=" + CHANTYPES), command.getSource());
	sendAll(RPL_ISUPPORT(SERVERNAME, "CHANLIMIT=" + CHANLIMIT), command.getSource());
	sendAll(RPL_ISUPPORT(SERVERNAME, "CHANMODES=" + CHANMODES), command.getSource());
	sendAll(RPL_ISUPPORT(SERVERNAME, "MODE=" + std::itoa(MODES)), command.getSource());
	sendAll(RPL_ISUPPORT(SERVERNAME, "PREFIX=" + PREFIX), command.getSource());
	sendAll(RPL_ISUPPORT(SERVERNAME, "TARGMAX=" + TARGMAX), command.getSource());
	sendAll(RPL_ISUPPORT(SERVERNAME, "NICKLEN=" + std::itoa(NICKLEN)), command.getSource());
	sendAll(RPL_ISUPPORT(SERVERNAME, "USERLEN=" + std::itoa(USERLEN)), command.getSource());
	sendAll(RPL_ISUPPORT(SERVERNAME, "CHANNELLEN=" + std::itoa(CHANNELLEN)), command.getSource());
	sendAll(RPL_ISUPPORT(SERVERNAME, "KICKLEN=" + std::itoa(KICKLEN)), command.getSource());
	sendAll(RPL_ISUPPORT(SERVERNAME, "TOPICLEN=" + std::itoa(TOPICLEN)), command.getSource());
}