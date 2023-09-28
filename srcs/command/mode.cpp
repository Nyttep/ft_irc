std::string	display_modes(Channel chan)
{
	std::string message;
	if (channel.getI() == true)
	{
		message = "i: no argument";
	}
	if (channel.getT() == true)
	{
		if (!message.empty())
			message += ", ";
		message += "t: no argument";
	}
	if (channel.getK() == true)
	{
		if (!message.empty())
			message += ", ";
		message += "k: +k <key>, -k no arguments";
	}
	if (channel.getO() == true)
	{
		if (!message.empty())
			message += ", ";
		message += "o: +o <target>, -o <target>";
	}
	if (channel.getL() == true)
	{
		if (!message.empty())
			message += ", ";
		message += "l: +l <limit>, -l no argument"
	}
	return (message);
}

void	mode_invite(std::string arguements)
{
	if (arguments[1][0] == '-')
		channel.setI(false);
	else if (argument[1][0] == '+')
		channel.setI(true);
	else
		std::cerr << "Redirection 696" << std::endl;
}

void	mode_topic(std::string arguements)
{
	if (arguments[1][0] == '-')
		channel.setT(false);
	else if (argument[1][0] == '+')
		channel.setT(true);
	else
		std::cerr << "Redirection 696" << std::endl;
}

void	mode_key(std::string arguments)
{
	if (arguments[1][0] == '+')
	{
		if (arguments.size() < 3 || arguments[2].empty())
		{
			std::cerr "Redirection 696" << std::endl;
			return ;
		}
		channel.setK(true);
		channel.setKey(arguments[2]);
	}
	else if (arguments[1][0] == '-')
		channel.setK(false);
	else
		std::cerr "Redirection 696" << std::endl;

}

void	execute_MODE(std::vector<std::string> arguments)
{
	if (arguments.empty() || arguments.size() < 1)
		return ;
	std::vector<std::string> targets;
	if ((targets = collect_arguments(arguments[0])) > TARGMAX)
		std::cerr << "Redirection 407" << std::endl;
	if (correct_chan(targets[0]) == false)
	{
		std::cout << "Redirection 403" << std::endl;
	}
	if (argument.size() == 1)
	{
		std::string message = display_mode(chan);
		std::cout << "Redirection 324" << std::endl;
	}
	if (is_operator(client, channel) == false)
	{
		std::cerr << "Redirection 482" << std::endl;
	}
	if (arguments[1].size() == 2)
	{
		char c = arguments[1][1];
		switch (c)
		{
			case 'i':
				mode_invite(arguments);
				break;
			case 't':
				mode_topic(arguments);
				break;
			case 'k':
				mode_key(arguments);
				break;
			case 'o':
				mode_operator(arguments);
				break;
			case 'l':
				mode_limit(arguments);
				break;
			default:
				return ;
		}
	}
}
// Mode Type B (Toujours des parametres): o
// Mode Type C (Parametre quand +, pas de param quand -): k l
// Mode Type D (pas de parametres): i t