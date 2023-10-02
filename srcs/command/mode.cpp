#include "irc.hpp"

// Mode Type B (Toujours des parametres): o
// Mode Type C (Parametre quand +, pas de param quand -): k l
// Mode Type D (pas de parametres): i t
std::string	display_modes(Channel chan)
{
	std::string message;
	if (chan.getI() == true)
	{
		if (message.empty())
			message = "+";
		message += "i";
	}
	if (chan.getT() == true)
	{
		if (message.empty())
			message = "+";
		message += "t";
	}
	if (chan.getK() == true)
	{
		if (message.empty())
			message = "+";
		message += "k";
	}
	if (chan.getO() == true)
	{
		if (message.empty())
			message = "+";
		message += "o";
	}
	if (chan.getL() == true)
	{
		if (message.empty())
			message = "+";
		message += "l"
	}
	return (message);
}

void	mode_invite(Command &command, Server &server)
{
	if (command.getParams()[1][0] == '-')
		server.getChan(command.getParams()[0]).setI(false);
	else if (command.getParams(command.getParams()[0])[1][0] == '+')
		server.getChan().setI(true);
	else
	{
		sendAll(RPL_INVALIDMODEPARAM("@"+command.getSource(), command.getParams()[0], command.getParams()[1], empty_param(command.getParams(), 2), " : Incorrect mode char ((+/-)(i/t/k/l/o))\r\n"), command.getSource());
		std::cerr << "Redirection 696" << std::endl;
	}
}

void	mode_topic(Command &command, Server &server)
{
	if (command.getParams()[1][0] == '-')
		server.getChan(command.getParams()[0]).setT(false);
	else if (command.getParams()[1][0] == '+')
		server.getChan(command.getParams()[0]).setT(true);
	else
	{
		sendAll(RPL_INVALIDMODEPARAM("@"+command.getSource(), command.getParams()[0], command.getParams()[1], empty_param(command.getParams(), 2), " : Incorrect mode char ((+/-)(i/t/k/l/o))\r\n"), command.getSource());
		std::cerr << "Redirection 696" << std::endl;
	}
}

void	mode_operator(Command &command, Server &server)
{
	if (command.getParams().size() < 3 || command.getParams()[2].empty())
	{
		sendAll(RPL_INVALIDMODEPARAM("@"+command.getSource(), command.getParams()[0], command.getParams()[1], empty_param(command.getParams(), 2), " : (+/-)o <target>\r\n"), command.getSource());
		std::cerr << "Redirection 696" << std::endl;
		return;
	}
	if (correct_nick_chan(command.getParams()[2]) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(command.getSource()->getNName(), command.getParams()[2]), command.getSource());
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}
	if (server.isUser(command.getParams()[2]) == false)
	{
		sendAll(ERR_NOSUCHNICK(command.getSource()->getNName(), command.getParams()[2]), command.getSource());
		std::cerr << "Redirection 401" << std::endl;
		return ;
	}
	if (server.getChan(command.getParams()[0]).onChannel(server.getUser(command.getParams()[2])) == false)
	{
		sendAll(ERR_USERNOTINCHANNEL(command.getSource()->getNName(), command.getParams()[2], command.getParams()[0]), command.getSource());
		std::cerr << "Redirection 441" << std::endl;
		return ;
	}
	if (command.getParams()[1][0] == '+')
	{
		if (server.getChan(command.getParams()[0]).isOperator(server.getUser(command.getParams()[2])) == true)
			return ;
		server.getChan(command.getParams()[0]).addOperator(server.getUser(command.getParams()[2]));
		server.getChan(command.getParams()[0]).removeUser(server.getUser(command.getParams()[2]));

	}
	else if (command.getParams().size()[1][0] == '-')
	{
		if (server.getChan(command.getParams()[0]).isOperator(server.getUser(command.getParams()[2])) == false)
			return ;
		server.getChan(command.getParams()[0]).removeOperator(getUser(target[0]));
		server.getChan(command.getParams()[0]).addUser(getUser(target[0]));
	}
	else
	{
		sendAll(RPL_INVALIDMODEPARAM("@"+command.getSource(), command.getParams()[0], command.getParams()[1], empty_param(command.getParams(), 2), " : Incorrect mode char ((+/-)(i/t/k/l/o))\r\n"), command.getSource());
		std::cerr << "Redirection 696" << std::endl;
	}
}

void	mode_key(Command &command, Server &server)
{
	if (command.getParams()[1][0] == '+')
	{
		if (command.getParams().size() < 3 || command.getParams()[2].empty())
		{
			sendAll(RPL_INVALIDMODEPARAM("@"+command.getSource(), command.getParams()[0], command.getParams()[1], empty_param(command.getParams(), 2), " : +k <key>\r\n"), command.getSource());
			std::cerr << "Redirection 696" << std::endl;
			return ;
		}
		server.getChan(command.getParams()[0]).setK(true);
		server.getChan(command.getParams()[0]).setKey(command.getParams()[2]);
	}
	else if (arguments[1][0] == '-')
	{
		server.getChan(command.getParams()[0]).setK(false);
		server.getChan(command.getParams()[0]).setKey("")
	}
	else
	{
		sendAll(RPL_INVALIDMODEPARAM("@"+command.getSource(), command.getParams()[0], command.getParams()[1], empty_param(command.getParams(), 2), " : Incorrect mode char ((+/-)(i/t/k/l/o))\r\n"), command.getSource());
		std::cerr "Redirection 696" << std::endl;
	}
}

void	mode_limit(Command command, Server server)
{
	if (command.getParam()[1][0] == '+')
	{
		if (command.getParam().size() < 3 || command.getParam()[2].empty())
		{
			sendAll(RPL_INVALIDMODEPARAM("@"+command.getSource(), command.getParams()[0], command.getParams()[1], empty_param(command.getParams(), 2), " : +l <limits>\r\n"), command.getSource());
			std::cerr << "Redirection 696" << std::endl;
			return ;
		}
		int limit = command.getParam()[2].atoi();
		if (limit < 0) 
		{
			sendAll(RPL_INVALIDMODEPARAM("@"+command.getSource(), command.getParams()[0], command.getParams()[1], empty_param(command.getParams(), 2), " : Invalid number\r\n"), command.getSource());
			std::cerr << "Redirection 696" << std::endl;
			return ;
		}
		if ((size_t)limit < server.getChan(command.getParams()[0].nbUser()))
		{
			sendAll(RPL_INVALIDMODEPARAM("@"+command.getSource(), command.getParams()[0], command.getParams()[1], empty_param(command.getParams(), 2), " : Limit below number of users\r\n"), command.getSource());
			std::cerr << "Redirection 696" << std::endl;
			return ;
		}
		server.getChan(command.getParams()[0]).setL(true);
		server.getChan(command.getParams()[0]).setLimit(limit);
	}
	else if (command.getParam()[1][0] == '-')
		server.getChan(command.getParams()[0]).setL(false);
	else
	{
		sendAll(RPL_INVALIDMODEPARAM("@"+command.getSource(), command.getParams()[0], command.getParams()[1], empty_param(command.getParams(), 2), " : Incorrect mode char ((+/-)(i/t/k/l/o))\r\n"), command.getSource());
		std::cerr << "Redirection 696" << std::endl;
	}
}

void	execute_MODE(Command &command, Server &server)
{
	if (command.getParams().empty() || command.getParams().size() < 1 || command.getParams()[0].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(command.getSource()->getNName(), command.getVerb()), command.getSource());
		std::cerr << "Redirection 461" << std::endl;
		return ;
	}
	if (correct_nick_chan(command.getParams()[0]) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(command.getSource()->getNName(), command.getParams()[0]), command.getSource());
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}
	if (server.chanExist(command.getParams()[0]) == false)
	{
		sendAll(ERR_NOSUCHCHANNEL(command.getSource()->getNName(), command.getParams()[0].getName()), command.getSource());
		std::cout << "Redirection 403" << std::endl;
		return ;
	}
	if (server.getChan(command.getParams()[0]).onChannel(command.getSource()) == false)
	{
		sendAll(ERR_NOTONCHANNEL(command.getSource()->getNName(), command.getParams()[0].getName()), command.getSource());
		std::cerr << "Redirection 442" << std::endl;
		return ;
	}
	if (command.getParams().size() == 1)
	{
		std::string message = display_mode(server.getChan(command.getParams()[0]));
		sendAll(RPL_CHANNELMODEIS(command.getSource()->getNName(), command.getParams()[0], message), command.getSource());
		std::cout << "Redirection 324" << std::endl;
	}
	else
	{
		if (server.getChan(command.getParams()[0]).isOperator(command.getSource()) == false)
		{
			sendAll(ERR_CHANPRIVSNEEDED(command.getSource()->getNName(), command.getParams()[0].getName()), command.getSource());
			std::cerr << "Redirection 482" << std::endl;
			return ;
		}
		if (command.getParams()[1].empty())
		{
			sendAll(RPL_INVALIDMODEPARAM("@"+command.getSource(), command.getParams()[0], command.getParams()[1], empty_param(command.getParams(), 2), " : Empty mode char ((+/-)(i,t,k,l,o))\r\n"), command.getSource());
			std::cerr << "Redirection 696" <<std::endl;
			return ;
		}
		
		if (analyse_param(command.getParams()[1]) == false)
		{
			// dans la fonction les sendAll
			std::cerr << "Redirection 696" << std::endl;
			return ;
		}
		char c = command.getParams()[1][1];
		switch (c)
		{
			case 'i':
				mode_invite(command, server);
				break;
			case 't':
				mode_topic(command, server);
				break;
			case 'k':
				mode_key(command, server);
				break;
			case 'o':
				mode_operator(command, server);
				break;
			case 'l':
				mode_limit(command, server);
				break;
			default:
				sendAll(RPL_INVALIDMODEPARAM("@"+command.getSource(), command.getParams()[0], command.getParams()[1], empty_param(command.getParams(), 2), " : Unknown mode char ((+/-)(i,t,k,l,o))\r\n"), command.getSource());
				std::cerr << "Redirection 696" <<std::endl;
		}
	}
}
