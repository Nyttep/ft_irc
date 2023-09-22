#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <cstdlib>

int	main(int argc, char **argv)
{
	std::map<int, std::string> list;
	list[0] = "Bob";
	list[1] = "HEHE";
	list[3] = "MaXime";
	list[4] = "LePlusCon";
	list[5] = "PAUL";

	if (argc != 2)
		exit(1);
	std::string nick = argv[1];

	// Empty string
	if (nick.empty())
	{
		std::cerr << "Redirection 431" << std::endl;
		exit (1);
	}

	// Invalid character
	if ((nick[0] == '$' || nick[0] == '#' || nick[0] == '&' || nick[0] == '%' || (isdigit(nick[0]))))
	{
		std::cerr << "Redirection 432" << std::endl;
		exit (1);
	}
	for (size_t i = 0; i != nick.length(); ++i)
	{
		if (nick[i] == ' ' || nick[i] == '.' || nick[i] == '*' || nick[i] == '?' || nick[i] == '!' || nick[i] == '@')
		{
			std::cerr << "Redirection 432" << std::endl;
			exit (1);
		}
	}

	// List users comparison
	std::string	low_nick = nick;
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
	list[list.size() + 1] = nick;

	// Success, print new list
	for (std::map<int, std::string>::const_iterator it = list.begin(); it != list.end(); ++it)
		std::cout << it->first << "\t" << it->second << std::endl;
	return (0);
}