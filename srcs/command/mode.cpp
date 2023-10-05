/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:36 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/05 19:09:30 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

// Mode Type B (Toujours des parametres): o
// Mode Type C (Parametre quand +, pas de param quand -): k l
// Mode Type D (pas de parametres): i t
std::string	display_modes(Channel *chan)
{
	std::string message;
	if (chan->getI() == true)
	{
		if (message.empty())
			message = "+";
		message += "i";
	}
	if (chan->getT() == true)
	{
		if (message.empty())
			message = "+";
		message += "t";
	}
	if (chan->getK() == true)
	{
		if (message.empty())
			message = "+";
		message += "k";
	}
	if (chan->getL() == true)
	{
		if (message.empty())
			message = "+";
		message += "l";
	}
	return (message);
}

void	mode_invite(Command &command, Server &server, std::vector<std::string> currParams)
{
	if (currParams[1][0] == '-')
	{
		server.getChan(currParams[0])->setI(false);
		server.getChan(command.getParams()[0])->sendToChan(US_MODE(setUserAddress(*command.getSource()), command.getParams()[0], currParams[1], " "), "", "");
	}
	else if (currParams[1][0] == '+')
	{
		server.getChan(currParams[0])->setI(true);
		server.getChan(command.getParams()[0])->sendToChan(US_MODE(setUserAddress(*command.getSource()), command.getParams()[0], currParams[1], " "), "", "");
	}
	else
	{
		sendAll(RPL_INVALIDMODEPARAM(HOSTNAME, command.getSource()->getNName(), currParams[0], currParams[1], "", " : Incorrect mode char ((+/-)(i/t/k/l/o))\r\n"), *command.getSource());
		std::cerr << "Redirection 696" << std::endl;
	}
}

void	mode_topic(Command &command, Server &server, std::vector<std::string> currParams)
{
	if (currParams[1][0] == '-')
	{
		server.getChan(currParams[0])->setT(false);
		server.getChan(command.getParams()[0])->sendToChan(US_MODE(setUserAddress(*command.getSource()), command.getParams()[0], currParams[1], " "), "", "");
	}
	else if (currParams[1][0] == '+')
	{
		server.getChan(currParams[0])->setT(true);
		server.getChan(command.getParams()[0])->sendToChan(US_MODE(setUserAddress(*command.getSource()), command.getParams()[0], currParams[1], " "), "", "");
	}
	else
	{
		sendAll(RPL_INVALIDMODEPARAM(HOSTNAME, command.getSource()->getNName(), currParams[0], currParams[1], "", " : Incorrect mode char ((+/-)(i/t/k/l/o))\r\n"), *command.getSource());
		std::cerr << "Redirection 696" << std::endl;
	}
}

void	mode_operator(Command &command, Server &server, std::vector<std::string> currParams)
{
	if (currParams.size() < 3 || currParams[2].empty())
		return;
	if (chantypes(currParams[2][0]) == false && correct_nick(currParams[2]) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(HOSTNAME, command.getSource()->getNName(), currParams[2]), *command.getSource());
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}
	if (server.isUser(currParams[2]) == false)
	{
		sendAll(ERR_NOSUCHNICK(HOSTNAME, command.getSource()->getNName(), currParams[2]), *command.getSource());
		std::cerr << "Redirection 401" << std::endl;
		return ;
	}
	if (server.getChan(currParams[0])->onChannel(server.getUser(currParams[2])) == false)
	{
		sendAll(ERR_USERNOTINCHANNEL(HOSTNAME, command.getSource()->getNName(), currParams[2], currParams[0]), *command.getSource());
		std::cerr << "Redirection 441" << std::endl;
		return ;
	}
	if (currParams[1][0] == '+')
	{
		if (server.getChan(currParams[0])->isOperator(server.getUser(currParams[2])) == true)
			return ;
		server.getChan(currParams[0])->addOperator(server.getUser(currParams[2]));
		server.getChan(currParams[0])->removeUser(server.getUser(currParams[2]));
		server.getChan(command.getParams()[0])->sendToChan(US_MODE(setUserAddress(*command.getSource()), command.getParams()[0], currParams[1], std::string(" ") + currParams[2]), "", "");
	}
	else if (currParams[1][0] == '-')
	{
		if (server.getChan(currParams[0])->isOperator(server.getUser(currParams[2])) == false)
			return ;
		server.getChan(currParams[0])->removeOperator(server.getUser(currParams[2]));
		server.getChan(currParams[0])->addUser(server.getUser(currParams[2]));
		server.getChan(command.getParams()[0])->sendToChan(US_MODE(setUserAddress(*command.getSource()), command.getParams()[0], currParams[1], std::string(" ") + currParams[2]), "", "");
	}
	else
	{
		sendAll(RPL_INVALIDMODEPARAM(HOSTNAME, command.getSource()->getNName(), currParams[0], currParams[1], empty_param(currParams[2], 2), " : Incorrect mode char ((+/-)(i/t/k/l/o))\r\n"), *command.getSource());
		std::cerr << "Redirection 696" << std::endl;
	}
}

void	mode_key(Command &command, Server &server, std::vector<std::string> currParams)
{
	if (currParams[1][0] == '+')
	{
		if (currParams.size() < 3 || currParams[2].empty())
		{
			// sendAll(RPL_INVALIDMODEPARAM(HOSTNAME, command.getSource()->getNName(), currParams[0], currParams[1], empty_param(currParams[2], 2), " : +k <key>\r\n"), *command.getSource());
			// std::cerr << "Redirection 696" << std::endl;
			return ;
		}
		server.getChan(currParams[0])->setK(true);
		server.getChan(currParams[0])->setKey(currParams[2]);
		server.getChan(command.getParams()[0])->sendToChan(US_MODE(setUserAddress(*command.getSource()), command.getParams()[0], currParams[1], std::string(" ") + currParams[2]), "", "");
	}
	else if (currParams[1][0] == '-')
	{
		server.getChan(currParams[0])->setK(false);
		server.getChan(currParams[0])->setKey("");
		server.getChan(command.getParams()[0])->sendToChan(US_MODE(setUserAddress(*command.getSource()), command.getParams()[0], currParams[1], " "), "", "");
	}
	else
	{
		sendAll(RPL_INVALIDMODEPARAM(HOSTNAME, command.getSource()->getNName(), currParams[0], currParams[1], empty_param(currParams[2], 2), " : Incorrect mode char ((+/-)(i/t/k/l/o))\r\n"), *command.getSource());
		std::cerr << "Redirection 696" << std::endl;
	}
}

void	mode_limit(Command &command, Server &server, std::vector<std::string> currParams)
{
	if (currParams[1][0] == '+')
	{
		if (currParams.size() < 3 || currParams[2].empty())
		{
			sendAll(RPL_INVALIDMODEPARAM(HOSTNAME, command.getSource()->getNName(), currParams[0], currParams[1], empty_param(currParams[2], 2), " : +l <limits>\r\n"), *command.getSource());
			std::cerr << "Redirection 696" << std::endl;
			return ;
		}
		int limit = std::atoi(currParams[2].c_str());
		if (limit < 0) 
		{
			sendAll(RPL_INVALIDMODEPARAM(HOSTNAME, command.getSource()->getNName(), currParams[0], currParams[1], empty_param(currParams[2], 2), " : Invalid number\r\n"), *command.getSource());
			std::cerr << "Redirection 696" << std::endl;
			return ;
		}
		if ((size_t)limit < server.getChan(currParams[0])->nbUser())
		{
			sendAll(RPL_INVALIDMODEPARAM(HOSTNAME, command.getSource()->getNName(), currParams[0], currParams[1], empty_param(currParams[2], 2), " : Limit below number of users\r\n"), *command.getSource());
			std::cerr << "Redirection 696" << std::endl;
			return ;
		}
		server.getChan(currParams[0])->setL(true);
		server.getChan(currParams[0])->setLimit(limit);
		server.getChan(command.getParams()[0])->sendToChan(US_MODE(setUserAddress(*command.getSource()), command.getParams()[0], currParams[1], std::string(" ") + currParams[2]), "", "");
	}
	else if (currParams[1][0] == '-')
	{
		server.getChan(currParams[0])->setL(false);
		server.getChan(command.getParams()[0])->sendToChan(US_MODE(setUserAddress(*command.getSource()), command.getParams()[0], currParams[1], " "), "", "");
	}
	else
	{
		sendAll(RPL_INVALIDMODEPARAM(HOSTNAME, command.getSource()->getNName(), currParams[0], currParams[1], empty_param(currParams[2], 2), " : Incorrect mode char ((+/-)(i/t/k/l/o))\r\n"), *command.getSource());
		std::cerr << "Redirection 696" << std::endl;
	}
}

std::vector<std::string>	getCurrParams(Command& cmd, size_t& i)
{
	std::vector<std::string>	ret;
	ret.push_back(cmd.getParams()[0]);
	ret.push_back(cmd.getParams()[i]);
	if (i + 1 < cmd.getParams().size())
	{
		if (!cmd.getParams()[i + 1].empty() && (cmd.getParams()[i + 1][0] != '+' && cmd.getParams()[i + 1][0] != '-'))
			ret.push_back(cmd.getParams()[i + 1]);
	}
	return (ret);
}

void	execute_MODE(Command &command, Server &server)
{
	if (command.getParams().empty() || command.getParams().size() < 1 || command.getParams()[0].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		std::cerr << "Redirection 461" << std::endl;
		return ;
	}
	if (correct_nick(command.getParams()[0]) == true)
	{
		sendAll(RPL_INVALIDMODEPARAM(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], "", "", " : Server does not handle user modes\r\n"), *command.getSource());
		std::cerr << "Redirection 696" << std::endl;
		return ;
	}
	if (correct_chan(command.getParams()[0]) == false)
	{
		sendAll(ERR_BADCHANMASK(HOSTNAME, command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}
	if (server.chanExist(command.getParams()[0]) == false)
	{
		sendAll(ERR_NOSUCHCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 696" << std::endl;
		return ;
	}
	if (server.getChan(command.getParams()[0])->onChannel(command.getSource()) == false)
	{
		sendAll(ERR_NOTONCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 442" << std::endl;
		return ;
	}
	if (command.getParams().size() == 1)
	{
		std::string message = display_modes(server.getChan(command.getParams()[0]));
		sendAll(RPL_CHANNELMODEIS(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], message), *command.getSource());
		std::cout << "Redirection 324" << std::endl;
		return ;
	}
	if (server.getChan(command.getParams()[0])->isOperator(command.getSource()) == false)
	{
		sendAll(ERR_CHANPRIVSNEEDED(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 482" << std::endl;
		return ;
	}
	else
	{
		for (size_t i = 1; i < command.getParams().size(); i++)
		{
			std::vector<std::string>	currParams = getCurrParams(command, i);
			if (analyse_param(currParams[1], command) == false)
			{
				// dans la fonction les sendAll
				std::cerr << "Redirection 696" << std::endl;
				return ;
			}
			char c = currParams[1][1];
			switch (c)
			{
				case 'i':
					mode_invite(command, server, currParams);
					break;
				case 't':
					mode_topic(command, server, currParams);
					break;
				case 'k':
					mode_key(command, server, currParams);
					break;
				case 'o':
					mode_operator(command, server, currParams);
					break;
				case 'l':
					mode_limit(command, server, currParams);
					break;
				default:
					sendAll(RPL_INVALIDMODEPARAM(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], command.getParams()[1], empty_param(command.getParams()[2], 2), " : Unknown mode char ((+/-)(i,t,k,l,o))\r\n"), *command.getSource());
					std::cerr << "Redirection 696" <<std::endl;
			}
			if (currParams.size() == 3)
				i++;
		}
	}
}
