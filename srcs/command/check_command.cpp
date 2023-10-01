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

void	handshake(Command command, Server server)
{
	RPL_WELCOME(SERVERNAME, command.getSource().getNName());
	RPL_YOURHOST(SERVERNAME);
	RPL_CREATED(SERVERNAME, /*une fonction qui cree le temps*/);
	RPL_MYINFO(SERVERNAME, CHANMODES);
	RPL_ISUPPORT(SERVERNAME, "CASEMAPPING=" + CASEMAPPING);
	


}