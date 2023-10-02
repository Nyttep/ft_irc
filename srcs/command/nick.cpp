#include "irc.hpp"

void	execute_NICK(Command command, Server server) /* prendre le serveur en paramètres */
{
		// Empty vector
	if (command.getParams().empty() || command.getParams()[0].empty())
	{
		if (command.getSource().getNName().empty())
			sendAll(ERR_NONICKNAMEGIVEN("guest"), command.getSource());
		else
			sendAll(ERR_NONICKNAMEGIVEN(command.getSource().getNName()), command.getSource());
		std::cerr << "Redirection 431" << std::endl;
		return ;
	}
	// Invalid character
	if (correct_nick_chan(command.getParams()[0]) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(command.getSource().getNName(), command.getParams()[0]), command.getSource());
		return ;
	}
	
	if (command.getParams()[0].length() > NICKLEN)
		command.setPParams(0, command.getParams()[0].erase(NICKLEN, command.getParams()[0].length() - NICKLEN));
	std::string	low_nick = command.getParams()[0];
	for (size_t i = 0; i != low_nick.length(); ++i)
		low_nick[i] = std::tolower(low_nick[i]);
	if (server.nicknameCollision(low_nick) == true)
	{
		if (command.getSource().getNName().empty())
			sendAll(ERR_NICKNAMEINUSE("guest", command.getParams()[0]), command.getSource());
		else
			sendAll(ERR_NICKNAMEINUSE(command.getSource().getNName(), command.getParams()[0]), command.getSource());
		std::cerr << "Redirection 433" << std::endl;
		return ;
	}
	if (command.getSource().getRegistered() == true)
	{
		std::string formername = command.getSource().getNName();
		command.getSource().setNName(command.getParams()[0]);
		std::string message = ":" + SERVERNAME + " :" + formername + " changed his nickname to " + command.getSource().getNName() + "\r\n";
		server.allUsersMessage(message);
	}
	else if (command.getSource().getUName().empty() && command.getSource().getRName().empty())
	{
		return ;
	}
	else
	{
		command.getSource().setRegistered(true);
		handshake(command, server);
	}
}