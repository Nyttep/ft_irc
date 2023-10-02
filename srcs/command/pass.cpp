#include "irc.hpp"

void	execute_PASS(Command &command, Server &server)
{
	if (command.getParams().empty() || command.getParams()[0].empty() || command.getParams().size())
	{
		if (command.getParams().size() > 1)
			std::cerr << "Too many arguments" << std::endl;
		else
			std::cerr << "Redirection 461" << std::endl;
		return ;
	}
	if (command.getParams()[0] != server.getPswd())
	{
		command.getSource()->setPass() == false;
		std::cerr << "Redirection 464" << std::endl;
		return ;
	}
	command.getSource()->setPass() == true;
}