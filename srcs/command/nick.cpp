#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <cstdlib>

void	execute_NICK(std::vector<std::string> arguments) /* prendre le serveur en paramètres */
{
		// Empty vector
	if (arguments.empty() || arguments[0].empty())
	{
		std::cerr << "Redirection 431" << std::endl;
		exit (1);
	}

	// Invalid character
	if (arguments[0][0] == '$' || arguments[0][0] == '#' || arguments[0][0] == '&' || arguments[0][0] == '%' || (isdigit(arguments[0][0])))
	{
		std::cerr << "Redirection 432" << std::endl;
		exit (1);
	}
	for (size_t i = 0; i != arguments[0].length(); ++i)
	{
		if (arguments[0][i] == ' ' || arguments[0][i] == '.' || arguments[0][i] == '*' || arguments[0][i] == '?' || arguments[0][i] == '!' || arguments[0][i] == '@')
		{
			std::cerr << "Redirection 432" << std::endl;
			exit (1);
		}
	}
	if (arguments[0].length() > NICKLEN)
		arguments[0].substr(0, NICKLEN);
	// List users comparison
	std::string	low_nick = arguments[0];
	for (size_t i = 0; i != low_nick.length(); ++i)
		low_nick[i] = std::tolower(low_nick[i]);
	for (std::map<int, std::string>::const_iterator it = list.begin(); it != list.end(); ++it)
	{
		std::string registered = it->second;
		for (size_t i = 0; i != registered.length(); ++i)
			registered[i] = std::tolower(registered[i]);
		if (registered == low_nick)
		{
			std::cerr << "Redirection 433" << std::endl;
			exit (1);
		}
	}
	// Ajout dans liste users serveur, set_nick dans User et verif les channels ou ils se trouvent pour modifier tous ces nick
}