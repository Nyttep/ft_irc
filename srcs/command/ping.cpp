#include "irc.hpp"

void	execute_PING(Command &command, Server &server)
{
	if (command.getParams().empty() || command.getParams()[0].empty() || command.getParams().size() != 1)
	{
		sendAll(ERR_NEEDMOREPARAMS(command.getSource()->getNName(), command.getVerb()), *command.getSource());
		std::cerr << "Redirection 461" << std::endl;
		return;
	}
	std::string PONG = ":" + SERVERNAME + " " + command.getSource.getNNAME() + ":PONG " + SERVERNAME + " " + command.getParams()[0];
	sendAll(PONG, *command.getSource());
}