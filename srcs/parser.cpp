/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:42:35 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/02 18:50:19 by pdubois          ###   ########.fr       */
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

bool	isascii(const std::string src) /*Inutile, surement a supprimer*/
{
	for (size_t i = 0; i != src.length(); ++i)
	{
		if (static_cast<unsigned char>(src[i]) > 127)
			return false;
	}
	return true;
}

void	execute_verb(Command& command, Server &server)
{
	if (command.getVerb() == "NICK")
	{
		if (command.getSource()->getPass() == true)
			execute_NICK(command, server);
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else if (command.getVerb() == "USER")
	{
		if (command.getSource()->getPass() == true && command.getSource()->getRegistered() == false)
			execute_USER(command, server);
		else if (command.getSource()->getRegistered() == true)
			std::cerr << "Redirection 462" << std::endl;
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else if (command.getVerb() == "PASS")
	{
		if (command.getSource()->getRegistered() == false)
			execute_PASS(command, server);
		else
			std::cerr << "Redirection 462" << std::endl;
	}
	else if (command.getVerb() == "MODE")
	{
		if (command.getSource()->getRegistered() == true)
			execute_MODE(command, server);
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else if (command.getVerb() == "JOIN")
	{
		if (command.getSource()->getRegistered() == true)
			execute_JOIN(command, server);
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else if (command.getVerb() == "PART")
	{
		if (command.getSource()->getRegistered() == true)
			execute_PART(command, server);
		else
			std::cerr << "Redirection 451" << std::endl;
	}	
	else if (command.getVerb() == "PING")
	{
		if (command.getSource()->getRegistered() == true)
			execute_PING(command);
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else if (command.getVerb() == "KICK")
	{
		if (command.getSource()->getRegistered() == true)
			execute_KICK(command, server);
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else if (command.getVerb() == "PRIVMSG")
	{
		if (command.getSource()->getRegistered() == true)
			execute_PRIVMSG(command, server);
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else if (command.getVerb() == "QUIT")
	{
		if (command.getSource()->getRegistered() == true)
			execute_QUIT(command);
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else if (command.getVerb() == "INVITE")
	{
		if (command.getSource()->getRegistered() == true)
			execute_INVITE(command, server);
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else if (command.getVerb() == "TOPIC")
	{
		if (command.getSource()->getRegistered() == true)
			execute_TOPIC(command, server);
		else
			std::cerr << "Redirection 451" << std::endl;
	}
	else
	{
		if (command.getSource()->getRegistered() == false)
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
	// for (std::vector<std::string>::iterator it = command.getParams().begin(); it != command.getParams().end(); ++it)
	// {
	// 	if (it->empty())
	// 		std::cout << "Argument : (null)" << std::endl;
	// 	else	
	// 		std::cout << "Argument : \"" << *it << "\"" << std::endl;
	// }
	// fin supprimer

	execute_verb(command, server);
}