/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:42:35 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/03 13:53:25 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

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

void	execute_verb(Command& command, Server &server)
{
	if (command.getVerb().empty())
		return ;
	else if (command.getVerb() == "CAP")
		return;
	else if (command.getVerb() == "NICK")
	{
		if (command.getSource()->getPass() == true)
			execute_NICK(command, server);
		else
		{
			sendAll(ERR_NOTREGISTERED(command.getSource()->getNName()), *command.getSource());
			std::cerr << "Redirection 451" << std::endl;
		}
	}
	else if (command.getVerb() == "USER")
	{
		if (command.getSource()->getPass() == true && command.getSource()->getRegistered() == false)
			execute_USER(command, server);
		else if (command.getSource()->getRegistered() == true)
		{
			sendAll(ERR_ALREADYREGISTERED(command.getSource()->getNName()), *command.getSource());
			std::cerr << "Redirection 462" << std::endl;
		}
		else
		{
			sendAll(ERR_NOTREGISTERED(command.getSource()->getNName()), *command.getSource());
			std::cerr << "Redirection 451" << std::endl;
		}
	}
	else if (command.getVerb() == "PASS")
	{
		if (command.getSource()->getRegistered() == false)
			execute_PASS(command, server);
		else
		{
			sendAll(ERR_ALREADYREGISTERED(command.getSource()->getNName()), *command.getSource());
			std::cerr << "Redirection 462" << std::endl;
		}
	}
	else if (command.getVerb() == "MODE")
	{
		if (command.getSource()->getRegistered() == true)
			execute_MODE(command, server);
		else
		{
			sendAll(ERR_NOTREGISTERED(command.getSource()->getNName()), *command.getSource());
			std::cerr << "Redirection 451" << std::endl;
		}
	}
	else if (command.getVerb() == "JOIN")
	{
		if (command.getSource()->getRegistered() == true)
			execute_JOIN(command, server);
		else
		{
			sendAll(ERR_NOTREGISTERED(command.getSource()->getNName()), *command.getSource());
			std::cerr << "Redirection 451" << std::endl;
		}
	}
	else if (command.getVerb() == "PART")
	{
		if (command.getSource()->getRegistered() == true)
			execute_PART(command, server);
		else
		{
			sendAll(ERR_NOTREGISTERED(command.getSource()->getNName()), *command.getSource());
			std::cerr << "Redirection 451" << std::endl;
		}
	}	
	else if (command.getVerb() == "PING")
	{
		if (command.getSource()->getRegistered() == true)
			execute_PING(command);
		else
		{
			sendAll(ERR_NOTREGISTERED(command.getSource()->getNName()), *command.getSource());
			std::cerr << "Redirection 451" << std::endl;
		}
	}
	else if (command.getVerb() == "KICK")
	{
		if (command.getSource()->getRegistered() == true)
			execute_KICK(command, server);
		else
		{
			sendAll(ERR_NOTREGISTERED(command.getSource()->getNName()), *command.getSource());
			std::cerr << "Redirection 451" << std::endl;
		}
	}
	else if (command.getVerb() == "PRIVMSG")
	{
		if (command.getSource()->getRegistered() == true)
			execute_PRIVMSG(command, server);
		else
		{
			sendAll(ERR_NOTREGISTERED(command.getSource()->getNName()), *command.getSource());
			std::cerr << "Redirection 451" << std::endl;
		}
	}
	else if (command.getVerb() == "QUIT")
	{
		if (command.getSource()->getRegistered() == true)
			execute_QUIT(command, server);
		else
		{
			sendAll(ERR_NOTREGISTERED(command.getSource()->getNName()), *command.getSource());
			std::cerr << "Redirection 451" << std::endl;
		}
	}
	else if (command.getVerb() == "INVITE")
	{
		if (command.getSource()->getRegistered() == true)
			execute_INVITE(command, server);
		else
		{
			sendAll(ERR_NOTREGISTERED(command.getSource()->getNName()), *command.getSource());
			std::cerr << "Redirection 451" << std::endl;
		}
	}
	else if (command.getVerb() == "TOPIC")
	{
		if (command.getSource()->getRegistered() == true)
			execute_TOPIC(command, server);
		else
		{
			sendAll(ERR_NOTREGISTERED(command.getSource()->getNName()), *command.getSource());
			std::cerr << "Redirection 451" << std::endl;
		}
	}
	else
	{
		sendAll(ERR_UNKNOWNCOMMAND(command.getSource()->getNName(), command.getVerb()), *command.getSource());
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

void	parser(User& source, std::string reception, Server& server)
{
	Command	command(&source);

	reception = trim(reception);
	if (reception.empty())
		return ;
	command.setVerb(parsing_cmd(&reception));
	if (!reception.empty())
		command.setParams(parsing_arguments(&reception));

	// un simple check  a supprimer
	if (command.getVerb().empty())
		std::cout << "verb : (null)" << std::endl;
	else	
		std::cout << "verb : \"" << command.getVerb() << "\"" << std::endl;
	for (size_t it = 0; it != command.getParams().size(); ++it)
	{
		if (command.getParams().empty())
			std::cout << "Argument : (null)" << std::endl;
		else	
			std::cout << "Argument : \"" << command.getParams()[it] << "\"" << std::endl;
	}
	// fin supprimer

	execute_verb(command, server);
}