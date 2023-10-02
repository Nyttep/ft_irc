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

void	handshake(Command &command, Server &server)
{
	RPL_WELCOME(SERVERNAME, command.getSource()->getNName());
	RPL_YOURHOST(SERVERNAME);
	RPL_CREATED(SERVERNAME, /*une fonction qui cree le temps*/);
	RPL_MYINFO(SERVERNAME, CHANMODES);
	RPL_ISUPPORT(SERVERNAME, NETWORK);
	RPL_ISUPPORT(SERVERNAME, "CASEMAPPING=" + CASEMAPPING);
	RPL_ISUPPORT(SERVERNAME, "CHANTYPES=" + CHANTYPES);
	RPL_ISUPPORT(SERVERNAME, "CHANLIMIT=" + CHANLIMIT);
	RPL_ISUPPORT(SERVERNAME, "CHANMODES=" + CHANMODES);
	RPL_ISUPPORT(SERVERNAME, "MODE=" + std::atoi(MODES));
	RPL_ISUPPORT(SERVERNAME, "PREFIX=" + PREFIX);
	RPL_ISUPPORT(SERVERNAME, "TARGMAX=" + TARGMAX);
	RPL_ISUPPORT(SERVERNAME, "NICKLEN=" + NICKLEN);
	RPL_ISUPPORT(SERVERNAME, "USERLEN=" + USERLEN);
	RPL_ISUPPORT(SERVERNAME, "CHANNELLEN=" + CHANNELLEN);
	RPL_ISUPPORT(SERVERNAME, "KICKLEN=" + KICKLEN);
	RPL_ISUPPORT(SERVERNAME, "TOPICLEN=" + TOPICLEN);
}