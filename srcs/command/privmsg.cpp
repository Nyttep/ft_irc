#include "irc.hpp"

void	multiple_PRIVMSG(Command command, server, std::vector<std::string> *targets, size_t *i, std::string message)
{
	if (chantypes(targets[i][0]) == true)
	{
		if (server.chanExist(targets[i]) == false)
		{
			std::cerr << "Redirection 403" << std::endl;
			return ;
		}
		if (on_channel(command.getSource(), server.getChan(targets[i])) == false)
		{
			std::cerr << "Redirection 404" << std::endl;
			return ;
		}
	}
	else
	{
		if (correct_user(server, targets[i]) == false)
		{
			std::cerr << "Redirection 401" << std::endl;
			return ;
		}
	}
	std::string f_message = command.getSource().getNName() + " " + targets[i] + " " + message;
	// send f_message
}

void	store_message(Command command)
{
	std::string message;
	for (size_t i = 1; i != command.getParam().size(); ++i)
	{
		if (!command.getParam()[i].empty())
		{
			if (!message.empty())
				message += " ";
			message += (command.getParam()[i]);
		}
	}
	return (message);
}

void	execute_PRIVMSG(Command command, Server server)
{
   if (command.getParam().empty() || command.getParam().size() < 2)
	{
		std::cerr << "Redirection 461" << std::endl;
		return ;
	}
	if (command.getParam()[0].empty())
	{
		std::cerr << "Redirection 411" << std::endl;
		return;
	}
	std::vector<std::string>	targets;
	targets = collect_arguments(command.getParam()[0]);
	if (targets.size() > targmax("PRIVMSG:"))
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
		multiple_PRIVMSG(command, server, &targets, i, message);
	}
}
// FAIRE une RPL_TOOMANYTARGETS(407), pas dans le manuel