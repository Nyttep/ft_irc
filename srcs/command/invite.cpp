#include "irc.hpp"

void	execute_INVITE(Command command, Server server)
{
	if (command.getParams().empty() || command.getParams().size() != 2 || \
		command.getParams()[0].empty() || command.getParams()[1].empty())
	{
		if (command.getParams().size() > 2)
			std::cout << "Too many params" << std::endl;
		else
		{
			sendAll(ERR_NEEDMOREPARAMS(command.getSource().getNName(), command.getVerb()), command.getSource());
			std::cout << "Redirection 461" << std::endl;
		}
		return ;
	}
	std::vector<std::string>	target = collect_arguments(command.getParams()[0]);
	std::vector<std::string>	channel = collect_arguments(command.getParams()[1]);
	if (target.size() != 1 || channel.size() != 1)
	{
		std::cout << "Too may params" << std::endl;
		return ;
	}
	if (server.chanExist(channel[0]) == false)
	{
		sendAll(ERR_NOSUCHCHANNEL(command.getSource().getNName(), channel[0]), command.getSource());
		std::cerr << "Redirection 403" << std::endl;
		return;
	}
	if (server.getChan(channel[0]).onChannel(command.getSource()) == false)
	{
		sendAll(ERR_NOTONCHANNEL(command.getSource().getNName(), channel[0]), command.getSource());
		std::cerr << "Redirection 442" << std::endl;
		return ;
	}
	if (server.getChan(channel[0]).isOperator(command.getSource()) == false)
	{
		sendAll(ERR_CHANPRIVSNEEDED(command.getSource().getNName(), command.getSource().getNName()), command.getSource());
		std::cerr << "Redirection 482" << std::endl;
		return ;
	}
	if (server.isUser(target[0]) == false)
	{
		sendAll(ERR_NOSUCHNICK(command.getSource().getNName(), target[0]), command.getSource());
		std::cerr << "Redirection 401" << std::endl;
		return ;
	}
	if (server.getChan(channel[0]).onChannel(server.getUser(target[0])) == true)
	{
		sendALL(ERR_USERONCHANNEL(command.getSource().getNName(), target[0], channel[0]), command.getSource());
		std::cerr << "Redirection 443" << std::endl;
		return ;
	}
	server.getChan(channel[0]).addInvite(server.getUser(target[0]));
	sendAll(RPL_INVITING(command.getSource().getNName(), target[0],channel[0]), command.getSource());
	sendAll(":" + command.getSource().getNName() + " :You are invited to " + channel[0] + "\r\n", server.getUser(target[0]));
	std::cout << "Redirection 341 à User command et message invite pour la cible" << std::endl;
	return;
}