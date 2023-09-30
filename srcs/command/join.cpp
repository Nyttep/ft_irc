void    create_chan(Command command, Server server, std::vector<std::string> channels, std::vector<std::string> keys, size_t i)
{
    for (size_t j = 0; j != channels[i].length(); ++j)
	{
		if (channels[i][j] == ' ' || channels[i][j] == '^G' || channels[i][j] == ',')
		{
			std::cerr << "Creer une redirection ERR_ERRONEOUSCHANNAME, base sur 432" << std::endl;
			return ;
		}
	}
    server.addChan(Channel(channels[i]));
    server.getChan(channels[i]).addOperator(command.getSource());
    if (channels[i][0] == '#')
        server.getChan(channels[i]).setT(true);
    if (!keys.empty() && (keys.size() >= i) && !keys[i].empty())
    {
        server.getChan(channels[i]).setK(true);
        server.getChan(channels[i]).setKey(keys[i]);
    }
    // Rajouter les messages de bienvenue
}


void    join_chan(Command command, Server server, std::vector<std::string> channels, std::vector<std::string> keys, size_t i)
{
    if (server.getChan(channels[i]).getK() == true)
    { 
        if (!keys.empty() && (keys.size() >= i))
        {
            if (server.getChan(channels[i]).getKey() != keys[i])
            {
                std::cerr << "Redirection 475" << std::endl;
                return ;
            }
        }
        else
        {
            std::cerr << "Redirection 475" << std::endl;
            return ;
        }
    }
    if (server.getChan(channels[i]).getI() == true && (on_invite(command.getSource(), server.getChan(channels[i])) == false))
    {
        std::cerr << "Redirection 473" << std::endl;
        return ;
    }
    if (server.getChan(channel[i]).getL() == true && (max_user(server.getChan(channels[i])) == true))
    {
        std::cerr << "Redirection 471" << std::endl;
        return ;
    }
    if (max_channel(command.getSource(), channels[i]) == true)
    {   
        std::cerr << "Redirection 405" << std::endl;
        return ;
    }
    server.getChan(channels[i]).addUser(command.getSource());
// Rajouter messages bienvenue et avertir arrivee nouveau
}


void    execute_JOIN(Command command, Server server)
{
    // check arguments
    if (command.getParams().empty() || command.getParams().size() < 1 || command.getParams().size() > 2)
    {
        if (command.getParams().size() > 2)
            std::cerr << "Too many params" << std::endl;
        else
            std::cerr << "Redirection 461" << std::endl;
        return;
    }
    for (size_t i = 0; i != command.getParams().size(), ++i)
    {
        if (command.getParams()[0].empty())
            std::cerr << "Redirection 461" << std::endl;
    }
    // if (argument[0] == "0")
    // {
    //     // Commande qui quitte tous les chans
    // }
    
    // récupération de tous les chans et les keys
    std::vector<std::string>    channels = collect_arguments(command.getParams()[0]);
    if (command.getParams().size() > 1)
        std::vector<std::string>    keys = collect_arguments(command.getParams()[1]);
    for (size_t i = 0; i != channels.size(), ++i)
    {
        if (chantypes(channels[i][0]) == false)
            std::cerr << "Redirection 403" << std::endl;
        if (server.chanExist(channels[i]) == false)
            create_chan(command, server, channels, keys, i);
        else
            join_chan(command, server, channels, keys, i);
    }

// Success, un join message, suivi de RPL 332, RPL 333(optionnel), RPL 353 RPL 366
// Autre client ont un message ifnormant le nouvel arrivant
// Pas précision si l'utilisateur est déjà dans le chan, propose de passer sous silence
}