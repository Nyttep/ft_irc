#include "irc.hpp"

void	execute_NICK(Command &command, Server &server) /* prendre le serveur en paramètres */
{
		// Empty vector
	if (command.getParams().empty() || command.getParams()[0].empty() || command.getParams().size() != 1)
	{
		if (command.getParams().size() > 1)
			std::cerr << "Too many params" << std::endl;
		else
			std::cerr << "Redirection 431" << std::endl;
		return ;
	}

	// Invalid character
	if (command.getParams()[0][0] == '$' || command.getParams()[0][0] == '#' || \
		command.getParams()[0][0] == '&' || command.getParams()[0][0] == '%' || \
		(isdigit(command.getParams()[0][0])))
	{
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}
	for (size_t i = 0; i != command.getParams()[0].length(); ++i)
	{
		if (command.getParams()[0][i] == ' ' || command.getParams()[0][i] == ','|| \
			command.getParams()[0][i] == '.' || command.getParams()[0][i] == '*' || \
			command.getParams()[0][i] == '?' || command.getParams()[0][i] == '!' || \
			command.getParams()[0][i] == '@')
		{
			std::cerr << "Redirection 432" << std::endl;
			return ;
		}
	}
	if (command.getParams()[0].length() > NICKLEN)
		command.setPParams(0, command.getParams()[0].erase(NICKLEN, command.getParams()[0].length() - NICKLEN));
	std::string	low_nick = command.getParams()[0];
	for (size_t i = 0; i != low_nick.length(); ++i)
		low_nick[i] = std::tolower(low_nick[i]);
	if (server.nicknameCollision(low_nick) == true)
	{
		std::cerr << "Redirection 433" << std::endl;
		return ;
	}
	if (command.getSource().getRegistered() == false && !command.getSource().getNName().empty() \
        && !command.getSource().getUName().empty() && !command.getSource().getRName().empty())
    {
        command.getSource().setRegistered(true);
        handshake(command, server);
    }
	else
	{
		std::string formername = command.getSource().getNName();
		command.getSource().setNName(command.getParams()[0]);
	}
}