#include	<iostream>
#include    <cstring>
#include	<vector>

void	execute_INVITE(Command command, Server server)
{
	if (command.getParams().empty() || command.getParams().size() != 2 || \
		command.getParams()[0].empty() || command.getParams()[1].empty())
	{
		if (command.getParams().size() > 2)
			std::cout << "Too many params" << std::endl;
		else
			std::cout << "Redirection 461" << std::endl;
		return ;
	}
	std::vector<std::string>	target = collect_arguments(command.getParams()[0]);
	std::vector<std::string>	channel = collect_arguments(command.getParams()[1]);
	if (target.size() != 1 || channel.size() != 1)
	{
		std::cout << "Too may params" << std::endl;
		return ;
	}
	if (server.chanExist(channel) == false)
	{
		std::cerr << "Redirection 403" << std::endl;
		return;
	}
	if (on_channel(command.getSource(), server.getChan(channel[0])) == false)
	{
		std::cerr << "Redirection 442" << std::endl;
		return ;
	}
	if (is_operator(command.getSource(), server.getChan(channel[0])) == false)
	{
		std::cerr << "Redirection 482" << std::endl;
		return ;
	}
	if (correct_user(server, target[0]) == false)
	{
		std::cerr << "Redirection 401" << std::endl;
		return ;
	}
	if (on_channel(server.getUser(target[0]), server.getChan(channel[0])) == true)
	{
		std::cerr << "Redirection 443" << std::endl;
	}
	server.getChan(channel[0]).addInvite(target[0]);
	std::cout << "Redirection 341 à User command et message invite pour la cible" << std::endl;
	return;
}