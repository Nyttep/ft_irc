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
    if (on_channel(targets, server.getChan(command.getParam()[0])) == false)
    {
        std::cerr << "Redirection 441" << std::endl;
		return ;
    }
	if (is_operator(targets[0], server.getChan(command.getParams()[0])) == true)
		server.getChan(command.getParams()[0]).removerOperator(targets[0]);	
	else
		server.getChan(command.getParams()[0]).removeUser(targets[0]);
    std::string	message_chan = command.getSource().getNName() + " kicked " + targets[0] + " from " server.getChan(command.getParam()[0]).getName();
	std::string message_kick = command.getSource().getNName() + " kicked you from " + server.getChan(command.getParams()[0]).getName();
	if (command.getParam().size() == 2)
    {
		/* send default*/
		std::cout << message_chan << std::endl;
		std::cout << message_kick << std::endl;
    }
    else
    {
    	for (size_t i = 2; i <= command.getParam().size(); ++i)
    	{
            if (!command.getParams()[i].empty())
			{
			    message_chan += " " + command.getParams()[i];
                message_kick += " " + command.getParams()[i];
			}
		}
		// send message à la cible kicke
		std::cout << message_chan << std::endl;
		std::cout << message_kick << std::endl;
    }
}