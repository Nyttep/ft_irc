#include <iostream>
#include <cstring>
#include <vector>

std::string	trim(const std::string &src)
{
	std::string	whitespace = " \n\r\t\f\v";
	std::string	res = src;
	size_t	start, end;

	start = res.find_first_not_of(whitespace);
	if (start == std::string::npos)
		return ("");
	if (start != 0)
		res = res.erase(0, start);
	end = res.find_last_not_of(whitespace);
	if (end != std::string::npos)
		res = res.erase(end + 1);
	return (res);
}

bool	isascii(const std::string src) /*Inutile, surement a supprimer*/
{
	for (size_t i = 0; i != src.length(); ++i)
	{
		if (static_cast<unsigned char>(src[i]) > 127)
			return false;
	}
	return true;
}

void	execute_command(Command command, Server server)
{
	if (command.getVerb() == "NICK")
	{
		if (command.getSource().getPass() == true)
			execute_NICK(command, server);
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else if (command.getVerb() == "USER")
	{
		if (command.getSource().getPass() == true && command.getSource().getRegistered() == false)
			execute_USER(command, server);
		else if (command.getSource().getRegistered() == true)
			std::cerr << "Redirection 462" << std::endl;
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else if (command.getVerb() == "PASS")
	{
		if (command.getSource().getRegistered() == false)
			execute_PASS(command, server);
		else
			std::cerr << "Redirection 462" << std::endl;
	}
	else if (command.getVerb() == "MODE")
	{
		if (command.getSource().getRegistered() == true)
			execute_MODE(command, server);
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else if (command.getVerb() == "JOIN")
	{
		if (command.getSource().getRegistered() == true)
			execute_JOIN(command, server);
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else if (command.getVerb() == "PART")
	{
		if (command.getSource().getRegistered() == true)
			execute_PART(command, server);
		else
			std::cerr << "Redirection 451" << std::endl;
	}	
	else if (command.getVerb() == "PING")
	{
		if (command.getSource().getRegistered() == true)
			execute_PING(command, server);
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else if (command.getVerb() == "PONG")
	{
		if (command.getSource().getRegistered() == true)
			execute_PONG(command, server);
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else if (command.getVerb() == "KICK")
	{
		if (command.getSource().getRegistered() == true)
			execute_KICK(command, server);
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else if (command.getVerb() == "PRIVMSG")
	{
		if (command.getSource().getRegistered() == true)
			execute_PRIVMSG(command, server);
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else if (command.getVerb() == "QUIT")
	{
		if (command.getSource().getRegistered() == true)
			execute_QUIT(command, server);
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else if (command.getVerb() == "INVITE")
	{
		if (command.getSource().getRegistered() == true)
			execute_INVITE(command, server);
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else if (command.getVerb() == "TOPIC")
	{
		if (command.getSource().getRegistered() == true)
			execute_TOPIC(command, server);
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else
	{
		if (command.getSource().getRegistered() == false)
			std::cerr << "Redirection 451" << std::endl;
		else
			std::cout << "Redirection 421" << std::endl;
	}
}

bool	only_space(std::string string)
{
	size_t	i = 0;
	while (string[i])
	{
		if (string[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

std::vector<std::string>	parsing_arguments(std::string *reception)
{
	std::vector<std::string>	arguments;
	std::string::size_type		space;
	
	while (!reception->empty())
	{
		*reception = trim(*reception);
		space = reception->find(' ');
		if ((*reception)[0] == ':')
		{
			if (only_space(reception->substr(1, reception->length())) == true)
			{
				arguments.push_back("");
				*reception = "";
			}
			else if ((*reception)[1] == ' ')
			{
				arguments.push_back(reception->substr(0, space));
				*reception = reception->substr(space + 1);
			}
			else
			{
				reception->erase(0, 1);
				arguments.push_back(*reception);
				*reception = "";
			}
		}
		else if (space != std::string::npos)
		{
		   	arguments.push_back(reception->substr(0, space));
			*reception = reception->substr(space + 1);
		}
		else
		{
			if (only_space(*reception) == true)
				arguments.push_back("");
			else
			{
				arguments.push_back(*reception);
			}
			*reception = "";
		}
	}
	return (arguments);
}

std::string	parsing_cmd(std::string *reception)
{
	std::string::size_type	space;
	std::string				command;
	space = reception->find(' ');
	command = reception->substr(0, space);
	reception->erase(0, space);
	return (command);
}

int	main(int argc, char **argv)
{
	// a supprimer
	if (argc != 2)
		return (0);

	std::string reception = argv[1]; /*a supprimer, sera la string envoye*/
	std::string	verb;
	std::vector<std::string> arguments;

	reception = trim(reception);
	if (reception.empty())
		return (0);
	command.setVerb(parsing_cmd(&reception));
	if (!reception.empty())
		arguments = parsing_arguments(&reception);
	Command	command(source, verb, arguments);

	// un simple check  a supprimer
	if (verb.empty())
		std::cout << "verb : (null)" << std::endl;
	else	
		std::cout << "verb : \"" << verb << "\"" << std::endl;
	for (std::vector<std::string>::iterator it = arguments.begin(); it != arguments.end(); ++it)
	{
		if (it->empty())
			std::cout << "Argument : (null)" << std::endl;
		else	
			std::cout << "Argument : \"" << *it << "\"" << std::endl;
	}
	// fin supprimer

	if (arguments.size() > 15)
		std::cerr << "Creer une phrase si il y a trop de parametres" << std::endl;
	execute_verb(command, server);

	return (0);
}