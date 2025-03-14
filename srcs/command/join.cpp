/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:23 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/06 11:45:36 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	create_chan(Command &command, Server &server, std::vector<std::string> channels, std::vector<std::string> keys, size_t i)
{
	if (command.getSource()->maxChannel(channels[i]) == true)
	{   
		sendAll(ERR_TOOMANYCHANNELS(HOSTNAME, command.getSource()->getNName(), channels[i]), *command.getSource());
		return ;
	}
	if (channels[i].length() > CHANNELLEN)
		channels[i].erase(CHANNELLEN, channels[i].length() - CHANNELLEN);
	server.addChan(new Channel(channels[i]));
	server.getChan(channels[i])->addOperator(command.getSource());
	sendAll(US_JOIN(setUserAddress(*command.getSource()), channels[i]), *command.getSource());
	command.getSource()->joinChan(server.getChan(channels[i]));
	sendAll(RPL_MODE(HOSTNAME, channels[i], "+o", std::string(" ") + command.getSource()->getNName()), *command.getSource());
	if (channels[i][0] == '#')
	{
		server.getChan(channels[i])->setT(true);
		sendAll(RPL_MODE(HOSTNAME, channels[i], "+t", ""), *command.getSource());
	}
	if (!keys.empty() && (keys.size() >= i))
	{
		if (!keys[i].empty())
		{
			server.getChan(channels[i])->setK(true);
			server.getChan(channels[i])->setKey(keys[i]);
			sendAll(RPL_MODE(HOSTNAME, channels[i], "+k", keys[i]), *command.getSource());
		}
	}
	sendAll(RPL_NOTOPIC(HOSTNAME, command.getSource()->getNName(), channels[i]), *command.getSource());
	sendAll(RPL_NAMEREPLY(HOSTNAME, command.getSource()->getNName(), channels[i], std::string("@") + command.getSource()->getNName()), *command.getSource());
	sendAll(RPL_ENDOFNAMES(HOSTNAME, command.getSource()->getNName(), channels[i]), *command.getSource());
}

void	join_chan(Command &command, Server &server, std::vector<std::string> channels, std::vector<std::string> keys, size_t i)
{
	if (server.getChan(channels[i])->onChannel(command.getSource()) == true)
		return ;
	if (server.getChan(channels[i])->getK() == true)
	{ 
		if (!keys.empty() && (keys.size() >= i))
		{
			if (server.getChan(channels[i])->getKey() != keys[i])
			{
				sendAll(ERR_BADCHANNELKEY(HOSTNAME, command.getSource()->getNName(), channels[i]), *command.getSource());
				return ;
			}
		}
		else
		{
			sendAll(ERR_BADCHANNELKEY(HOSTNAME, command.getSource()->getNName(), channels[i]), *command.getSource());
			return ;
		}
	}
	if (server.getChan(channels[i])->getI() == true && (server.getChan(channels[i])->isInvite(command.getSource()) == false))
	{
		sendAll(ERR_INVITEONLYCHAN(HOSTNAME, command.getSource()->getNName(), channels[i]), *command.getSource());
		return ;
	}
	if (server.getChan(channels[i])->getL() == true && (server.getChan(channels[i])->maxUser() == true))
	{
		sendAll(ERR_CHANNELISFULL(HOSTNAME, command.getSource()->getNName(), channels[i]), *command.getSource());
		return ;
	}
	if (command.getSource()->maxChannel(channels[i]) == true)
	{   
		sendAll(ERR_TOOMANYCHANNELS(HOSTNAME, command.getSource()->getNName(), channels[i]), *command.getSource());
		return ;
	}
	if (server.getChan(channels[i])->isInvite(command.getSource()) == true)
		server.getChan(channels[i])->removeInvite(command.getSource());
	server.getChan(channels[i])->addUser(command.getSource());
	command.getSource()->joinChan(server.getChan(channels[i]));
	server.getChan(channels[i])->sendToChan(US_JOIN(setUserAddress(*command.getSource()), channels[i]), "", "");
	if (server.getChan(channels[i])->getTopic().empty())
		sendAll(RPL_NOTOPIC(HOSTNAME, command.getSource()->getNName(), channels[i]), *command.getSource());
	else
		sendAll(RPL_TOPIC(HOSTNAME, command.getSource()->getNName(), channels[i], server.getChan(channels[i])->getTopic()), *command.getSource());
	server.getChan(channels[i])->sendUsersList(*command.getSource());
}

void	execute_JOIN(Command &command, Server &server)
{
	if (command.getParams().empty() || command.getParams().size() < 1 || command.getParams()[0].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		return;
	}
	if ((command.getParams().size() == 1) && (command.getParams()[0] == "0"))
	{
		command.getSource()->leaveAllChanPART(command, server);
		return;
	}
	std::vector<std::string>	channels = collect_arguments(command.getParams()[0]);
	if (channels.size() > targmax(command.getVerb()))
	{
		sendAll(ERR_TOOMANYTARGETS(HOSTNAME, command.getSource()->getNName()), *command.getSource());
		return ;
	}
	std::vector<std::string>	keys;
	if (command.getParams().size() > 1)
		keys = collect_arguments(command.getParams()[1]);
	for (size_t i = 0; i != channels.size(); ++i)
	{
		if (channels[i].empty())
		{
			sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		}
		else if (correct_chan(channels[i]) == false)
		{
			sendAll(ERR_BADCHANMASK(HOSTNAME, channels[i]), *command.getSource());
		}
		else if (server.chanExist(channels[i]) == false)
			create_chan(command, server, channels, keys, i);
		else
			join_chan(command, server, channels, keys, i);
	}
}