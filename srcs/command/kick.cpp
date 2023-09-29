void    execute_KICK(Command command, Server server)
{
	if (command.getParams().empty() || command.getParams().size() < 2 || \
		command.getParams()[0].empty() || command.getParams()[1].empty())
	{
			std::cout << "Redirection 461" << std::endl;
		return ;
	}
    if (server.chanExist(command.getParam()[0]) == false)
    {
        std::cerr << "Redirection 403" << std::endl;
		return ;
    }
	if (on_channel(command.getSource(), server.getChan(command.getParam()[0])) == false)
	{
		std::cerr << "Redirection 442" << std::endl;
		return ;
	}
	if (is_operator(command.getSource(), server.getChan(command.getParam()[0])) == false)
	{
		std::cerr << "Redirection 482" << std::endl;
		return ;
	}
    std::vector<std::string>    targets = collect_arguments(command.getParams()[1]);
	if (targets.size() > targmax("KICK:"))
	{
		std::cerr << "Too many params" << std::endl;
		return ;
	}
	// Mettre une boucle qui verifie chaque target
    if (on_channel(targets, server.getChan(command.getParam()[0])) == false)
    {
        std::cerr << "Redirection 441" << std::endl;
		return ;
    }
    if (command.getParam().size() == 2)
    {
        std::cout << client << ": " << targets << "was kicked from the channel\r\n" << std::endl;
    }
    else
    {
        std::string comment;
    	for (size_t i = 2; i <= command.getParam().size(); ++i)
    	{
            comment += command.getParam()[i];
            if (i < command.getParam.size() - 1)
                comment += " ";
    	}
		// send message à la cible kicke
    }
}