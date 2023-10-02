#include "irc.hpp"

void	multiple_PRIVMSG(Command &command, Server &server, std::vector<std::string> targets, size_t i, std::string message)
{
	std::string	prefix;
	if (have_prefix(targets[i][0]) == true)
	{
		prefix = targets[i].substr(0, 1);
		targets[i].erase(0, 1);
	}
	if (chantypes(targets[i][0]) == true)
	{
		if (server.chanExist(targets[i]) == false)
		{
			std::cerr << "Redirection 403" << std::endl;
			return ;
		}
	}
	else
	{
		if (server.isUser(targets[i]) == false)
		{
			std::cerr << "Redirection 401" << std::endl;
			return ;
		}
	}
	std::string f_message = ":*" + command.getSource().getNName() + "* " + targets[i] + " : " + message + "\r\n";
	// send f_message
}

void	execute_PRIVMSG(Command &command, Server &server)
{
   if (command.getParams().empty() || command.getParams().size() < 2)
	{
		std::cerr << "Redirection 461" << std::endl;
		return ;
	}
	if (command.getParams()[0].empty())
	{
		std::cerr << "Redirection 411" << std::endl;
		return;
	}
	std::vector<std::string>	targets;
	targets = collect_arguments(command.getParams()[0]);
	if (targets.size() > targmax(command.getVerb()))
	{
		std::cerr << "Redirection 407" << std::endl;
		return ;
	}
	std::string message = store_message(command);
	if (message.empty())
	{
		std::cerr << "Redirection 412" << std::endl;
		return ;
	}
	for (size_t i = 0; i != targets.size(); ++i)
	{
		multiple_PRIVMSG(command, server, targets, i, message);
	}
}
// FAIRE une RPL_TOOMANYTARGETS(407), pas dans le manuel