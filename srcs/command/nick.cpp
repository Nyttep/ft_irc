#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <cstdlib>

void	execute_NICK(Command command, Server server) /* prendre le serveur en paramètres */
{
		// Empty vector
	if (command.getParams().empty() || command.getParams()[0].empty() || command.getParams().size() != 1)
	{
		if (command.getParams().size > 1)
			std::cerr << "Too many params" << std::endl;
		else
			std::cerr << "Redirection 431" << std::endl;
		return ;
	}

	// Invalid character
	if (command.getParams()[0][0] == '$' || command.getParams()[0][0] == '#' || command.getParams()[0][0] == '&' || command.getParams()[0][0] == '%' || (isdigit(command.getParams()[0][0])))
	{
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}
	for (size_t i = 0; i != command.getParams()[0].length(); ++i)
	{
		if (command.getParams()[0][i] == ' ' || command.getParams()[0][i] == ','|| command.getParams()[0][i] == '.' || command.getParams()[0][i] == '*' || command.getParams()[0][i] == '?' || command.getParams()[0][i] == '!' || command.getParams()[0][i] == '@')
		{
			std::cerr << "Redirection 432" << std::endl;
			return ;
		}
	}
	if (command.getParams()[0].length() > NICKLEN)
	{
		std::string	trunc_nick = command.getParams()[0].substr(0, NICKLEN);
		command.setPParams(0, trunc_nick));
	}
	// List users comparison
	std::string	low_nick = command.getParams()[0];
	for (size_t i = 0; i != low_nick.length(); ++i)
		low_nick[i] = std::tolower(low_nick[i]);
	std::map<int, User>	userlist = server.getUser();
	for (std::map<int, std::string>::const_iterator it = userlist.begin(); it != userlist.end(); ++it)
	{
		std::string registered = it->second;
		for (size_t i = 0; i != registered.length(); ++i)
			registered[i] = std::tolower(registered[i]);
		if (registered == low_nick)
		{
			std::cerr << "Redirection 433" << std::endl;
			return ;
		}
	}
	std::string formername = command.getSource().getNName();
	command.getSource().setNName(command.getParams()[0]);
	// Ajout dans liste users serveur, set_nick dans User et verif les channels ou ils se trouvent pour modifier tous ces nick
}