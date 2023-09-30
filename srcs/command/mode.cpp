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

void	mode_invite(Command command, Server server, std::vector<std::string> targets)
{
	if (command.getParams()[1][0] == '-')
		server.getChan(targets[0]).setI(false);
	else if (command.getParams(targets[0])[1][0] == '+')
		server.getChan().setI(true);
	else
		std::cerr << "Redirection 696" << std::endl;
}

void	mode_topic(Command command, Server server, std::vector<std::string> targets)
{
	if (command.getParams()[1][0] == '-')
		server.getChan(targets[0]).setT(false);
	else if (command.getParams()[1][0] == '+')
		server.getChan(targets[0]).setT(true);
	else
		std::cerr << "Redirection 696" << std::endl;
}

void	mode_operator(Command command, Server server, std::vector<std::string> targets)
{
	if (command.getParams().size() != 3 || command.getParams()[2].empty())
	{
		if (command.getParams().size() > 3)
			std::cerr << "Too many params" << std::endl;
		else
			std::cerr << "Redirection 696" << std::endl;
		return;
	}
	if (command.getParams()[1][0] == '+')
	{
		std::vector<std::string> new_operator = collect_arguments(command.getParams()[2]);
		if (new_operator.size() > 1) /*changer avec support.hpp MODE*/
		{
			std::cerr << "Redirection 407" << std::endl;
			return;
		}
		if (correct_user(server, new_operator[0]) == false)
		{
			std::cerr << "Redirection 401" << std::endl;
			return ;
		}
		if (on_channel(new_operator[0], server.getChan(targets[0])) == false)
		{
			std::cerr << "Redirection 441" << std::endl;
			return ;
		}
		if (is_operator(server.getUser(new_operator[0]), server.getChan(targets[0])) == true)
			return ;
		server.getChan(targets[0]).addOperator(server.getUser(new_operator[0]));
		server.getChan(targets[0]).removeUser(server.getUser(new_operator[0]));

	}
	else if (command.getParams().size()[1][0] == '-')
	{
		std::vector<std::string> operator = collect_arguments(command.getParams()[2]);
		if (operator.size() > TARGMAX)
		{
			std::cerr << "Redirection 407" << std::endl;
			return ;
		}
		if (correct_user(server, operator[0]) == false)
		{
			std::cerr << "Redirection 401" << std::endl;
			return ;
		}
		if (on_channel(operator[0], server.getChan(targets[0])) == false)
		{
			std::cerr << "Redirection 441" << std::endl;
			return ;
		}
		if (is_operator(server.getUSer(operator[0]), server.getChan(targets[0])) == false)
			return ;
		channel.removeOperator(getUser(target[0]));
		channel.addUser(getUser(target[0]));
	}
	else
	{
		std::cerr << "Redirection 696" << std::endl;
	}
}

void	mode_key(Command command, Server server, std::vector<std::string> targets)
{
	if (command.getParams()[1][0] == '+')
	{
		if (command.getParams().size() != 3 || command.getParams()[2].empty())
		{
			if (command.getParams().size() > 3)
				std::cerr << "Too many params" << std::endl;
			else
				std::cerr << "Redirection 696" << std::endl;
			return ;
		}
		server.getChan(targets[0]).setK(true);
		server.getChan(targets[0]).setKey(command.getParams()[2]);
	}
	else if (arguments[1][0] == '-')
	{
		server.getChan(targets[0]).setK(false);
		server.getChan(targets[0]).setKey("")
	}
	else
		std::cerr "Redirection 696" << std::endl;

}

void	mode_limit(Command command, Server server, std::vector<std::string> targets)
{
	if (command.getParam()[1][0] == '+')
	{
		if (command.getParam().size() != 3 || command.getParam()[2].empty())
		{
			if (command.getParam().size > 3)
				std::cerr << "Too many params" << std::endl;
			else
				std::cerr << "Redirection 696" << std::endl;
			return ;
		}
		int limit = command.getParam()[2].atoi(); /*Revoir le atoi pour plus d'efficacite*/
		if (limit < 0) 
		{
			std::cerr << "Redirection 696" << std::endl;
			return ;
		}
		server.getChan(targets[0]).setL(true);
		server.getChan(targets[0]).setLimit(limit);
	}
	else if (command.getParam()[1][0] == '-')
		server.getChan(targets[0]).setL(false);
	else
	{
		std::cerr << "Redirection 696" << std::endl;
	}
}

void	execute_MODE(Command command, Server server)
{
	if (command.getParams().empty() || command.getParams().size() < 1)
	{
		std::cerr << "Redirection 461" << std::endl;
		return ;
	}
	std::vector<std::string> targets = collect_arguments(arguments[0]);
	if (targets.size() > 1)
	{
		std::cerr << "Redirection 407" << std::endl;
		return ;
	}
	if (server.chanExist(targets[0]) == false)
	{
		std::cout << "Redirection 403" << std::endl;
		return ;
	}
	if (on_channel(command.getSource(), server.getChan(targets[0])) == false)
	{
		std::cerr << "Redirection 442" << std::endl;
		return ;
	}
	if (command.getParams().size() == 1)
	{
		std::string message = display_mode(server.getChan(targets[0]));
		std::cout << "Redirection 324" << std::endl;
	}
	else
	{
		if (is_operator(command.getSource(), server.getChan(targets[0])) == false)
		{
			std::cerr << "Redirection 482" << std::endl;
			return ;
		}
		if (command.getParams()[1].size() == 2) /*Avant analyser dans switch, approfondir le nb de mode passe*/
		{
			char c = command.getParams()[1][1];
			switch (c)
			{
				case 'i':
					mode_invite(command, server, targets);
					break;
				case 't':
					mode_topic(command, server, targets);
					break;
				case 'k':
					mode_key(command, server, targets);
					break;
				case 'o':
					mode_operator(command, server, targets);
					break;
				case 'l':
					mode_limit(command, server, targets);
					break;
				default:
					std::cerr << "Redirection 696" <<std::endl;
			}
		}
	}
}