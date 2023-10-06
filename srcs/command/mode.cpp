/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:36 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/06 14:48:43 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

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

void	mode_invite(Command &command, Server &server, std::string currParams)
{
	if (currParams.empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		return ;
	}
	if (currParams[0] == '-')
	{
		server.getChan(command.getParams()[0])->setI(false);
		server.getChan(command.getParams()[0])->sendToChan(US_MODE(setUserAddress(*command.getSource()), command.getParams()[0], std::string(":") + currParams, ""), "", "");
	}
	else if (currParams[0] == '+')
	{
		server.getChan(command.getParams()[0])->setI(true);
		server.getChan(command.getParams()[0])->sendToChan(US_MODE(setUserAddress(*command.getSource()), command.getParams()[0], std::string(":") + currParams, ""), "", "");
	}
	else
	{
		sendAll(RPL_INVALIDMODEPARAM(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], currParams, "", "Incorrect mode char ((+/-)(i/t/k/l/o))"), *command.getSource());
	}
}

void	mode_topic(Command &command, Server &server, std::string currParams)
{
	if (currParams.empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		return ;
	}
	if (currParams[0] == '-')
	{
		server.getChan(command.getParams()[0])->setT(false);
		server.getChan(command.getParams()[0])->sendToChan(US_MODE(setUserAddress(*command.getSource()), command.getParams()[0], std::string(":") + currParams, ""), "", "");
	}
	else if (currParams[0] == '+')
	{
		server.getChan(command.getParams()[0])->setT(true);
		server.getChan(command.getParams()[0])->sendToChan(US_MODE(setUserAddress(*command.getSource()), command.getParams()[0], std::string(":") + currParams, ""), "", "");
	}
	else
	{
		sendAll(RPL_INVALIDMODEPARAM(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], currParams, "", "Incorrect mode char ((+/-)(i/t/k/l/o))"), *command.getSource());
	}
}

void	mode_operator(Command &command, Server &server, std::string currParams, std::vector<std::string> &args)
{
	if (currParams.empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		return ;
	}
	if (args.empty() || args[0].empty())
		return;
	if (correct_nick(args[0]) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(HOSTNAME, command.getSource()->getNName(), args[0]), *command.getSource());
		args.erase(args.begin());
		return ;
	}
	if (server.isUser(args[0]) == false)
	{
		sendAll(ERR_NOSUCHNICK(HOSTNAME, command.getSource()->getNName(), args[0]), *command.getSource());
		args.erase(args.begin());
		return ;
	}
	if (server.getChan(command.getParams()[0])->onChannel(server.getUser(args[0])) == false)
	{
		sendAll(ERR_USERNOTINCHANNEL(HOSTNAME, command.getSource()->getNName(), args[0], command.getParams()[0]), *command.getSource());
		args.erase(args.begin());
		return ;
	}
	if (currParams[0] == '+')
	{
		if (server.getChan(command.getParams()[0])->isOperator(server.getUser(args[0])) == true)
		{
			args.erase(args.begin());
			return ;
		}
		server.getChan(command.getParams()[0])->addOperator(server.getUser(args[0]));
		server.getChan(command.getParams()[0])->removeUser(server.getUser(args[0]));
		server.getChan(command.getParams()[0])->sendToChan(US_MODE(setUserAddress(*command.getSource()), command.getParams()[0], currParams, std::string(" :") + args[0]), "", "");
		args.erase(args.begin());
	}
	else if (currParams[0] == '-')
	{
		if (server.getChan(command.getParams()[0])->isOperator(server.getUser(args[0])) == false)
			return ;
		server.getChan(command.getParams()[0])->removeOperator(server.getUser(args[0]));
		server.getChan(command.getParams()[0])->addUser(server.getUser(args[0]));
		server.getChan(command.getParams()[0])->sendToChan(US_MODE(setUserAddress(*command.getSource()), command.getParams()[0], currParams, std::string(" :") + args[0]), "", "");
		args.erase(args.begin());

	}
	else
	{
		sendAll(RPL_INVALIDMODEPARAM(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], currParams, "", "Incorrect mode char ((+/-)(i/t/k/l/o))"), *command.getSource());
	}
}

void	mode_key(Command &command, Server &server, std::string currParams, std::vector<std::string> &args)
{
	if (currParams.empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		return ;
	}
	if (currParams[0] == '+')
	{
		if (args.empty() || args[0].empty())
		{
			return ;
		}
		server.getChan(command.getParams()[0])->setK(true);
		server.getChan(command.getParams()[0])->setKey(args[0]);
		server.getChan(command.getParams()[0])->sendToChan(US_MODE(setUserAddress(*command.getSource()), command.getParams()[0], currParams, std::string(" :") + args[0]), "", "");
		args.erase(args.begin());
	}
	else if (currParams[0] == '-')
	{
		server.getChan(command.getParams()[0])->setK(false);
		server.getChan(command.getParams()[0])->setKey("");
		server.getChan(command.getParams()[0])->sendToChan(US_MODE(setUserAddress(*command.getSource()), command.getParams()[0], std::string(":") + currParams, ""), "", "");
	}
	else
	{
		sendAll(RPL_INVALIDMODEPARAM(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], currParams, "", "Incorrect mode char ((+/-)(i/t/k/l/o))"), *command.getSource());
	}
}

void	mode_limit(Command &command, Server &server, std::string currParams, std::vector<std::string> &args)
{
	if (currParams.empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		return ;
	}
	if (currParams[0] == '+')
	{
		if (args.empty()|| args[0].empty())
		{
			return ;
		}
		int limit = std::atoi(args[0].c_str());
		if (limit < 0) 
		{
			sendAll(RPL_INVALIDMODEPARAM(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], currParams, args[0], "Invalid number"), *command.getSource());
			args.erase(args.begin());
			return ;
		}
		if ((size_t)limit < server.getChan(command.getParams()[0])->nbUser())
		{
			sendAll(RPL_INVALIDMODEPARAM(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], currParams, args[0], "Limit below number of users"), *command.getSource());
			args.erase(args.begin());
			return ;
		}
		server.getChan(command.getParams()[0])->setL(true);
		server.getChan(command.getParams()[0])->setLimit(limit);
		server.getChan(command.getParams()[0])->sendToChan(US_MODE(setUserAddress(*command.getSource()), command.getParams()[0], currParams, std::string(" :") + args[0]), "", "");
		args.erase(args.begin());
	}
	else if (currParams[0] == '-')
	{
		server.getChan(command.getParams()[0])->setL(false);
		server.getChan(command.getParams()[0])->sendToChan(US_MODE(setUserAddress(*command.getSource()), command.getParams()[0], currParams, ""), "", "");
	}
	else
	{
		sendAll(RPL_INVALIDMODEPARAM(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], currParams, "", "Incorrect mode char ((+/-)(i/t/k/l/o))"), *command.getSource());
	}
}

void	execute_MODE(Command &command, Server &server)
{
	if (command.getParams().empty() || command.getParams().size() < 1 || command.getParams()[0].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		return ;
	}
	if (correct_nick(command.getParams()[0]) == true)
	{
		sendAll(RPL_INVALIDMODEPARAM(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], empty_param(command.getParams(), 1), empty_param(command.getParams(), 2), "Server does not handle user modes"), *command.getSource());
		return ;
	}
	if (correct_chan(command.getParams()[0]) == false)
	{
		sendAll(ERR_BADCHANMASK(HOSTNAME, command.getParams()[0]), *command.getSource());
		return ;
	}
	if (server.chanExist(command.getParams()[0]) == false)
	{
		sendAll(ERR_NOSUCHCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		return ;
	}
	if (server.getChan(command.getParams()[0])->onChannel(command.getSource()) == false)
	{
		sendAll(ERR_NOTONCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		return ;
	}
	if (command.getParams().size() == 1)
	{
		std::string message = display_modes(server.getChan(command.getParams()[0]));
		sendAll(RPL_CHANNELMODEIS(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], message), *command.getSource());
		return ;
	}
	if (server.getChan(command.getParams()[0])->isOperator(command.getSource()) == false)
	{
		sendAll(ERR_CHANPRIVSNEEDED(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		return ;
	}
	else
	{
		std::vector<std::string>	currParams = collect_mode_char(command.getParams()[1]);
		std::vector<std::string>	args = getParamsMODE(command.getParams());
		if (currParams.empty())
		{
			sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
			return ;
		}
		for (size_t i = 0; (i < currParams.size()) && (i != (MODES)); i++)
		{
			if (analyse_param(currParams[i], command) == false)
			{
				continue ;
			}
			char c = currParams[i][1];
			switch (c)
			{
				case 'i':
					mode_invite(command, server, currParams[i]);
					break;
				case 't':
					mode_topic(command, server, currParams[i]);
					break;
				case 'k':
					mode_key(command, server, currParams[i], args);
					break;
				case 'o':
					mode_operator(command, server, currParams[i], args);
					break;
				case 'l':
					mode_limit(command, server, currParams[i], args);
					break;
				default:
					sendAll(RPL_INVALIDMODEPARAM(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], command.getParams()[1], empty_param(command.getParams(), 2), "Unknown mode char ((+/-)(i,t,k,l,o))"), *command.getSource());
			}
		}
	}
}
