void    execute_KICK(std::vector<std::string> arguments)
{
    if (arguments.empty() || arguments.size() < 2 )
    {
        std::cerr << "Redirection 461 "<< std::endl;
    }
    for (size_t i = 0; i != arguments.size(); ++i)
    {
        if (arguments[i].empty())
        {
            std::cerr << "Redirection 461" << std::endl;
        }
    }
    if (correct_chan(argument[0]) == false)
    {
        std::cerr << "Redirection 403" << std::endl;
    }
    if (on_channel(client, chan) == false)
    {
        std::cerr << "Redirection 442" << std::endl;
    }
    if (is_operator(client, channel) == false)
    {
        std::cerr << "Redirection 482" << std::endl;
    }

    std::vector<std::string>    targets;
    targets = collect_arguments(arguments[1]);
    if (on_channel(client, target) == false)
    {
        std::cerr << "Redirection 441" << std::endl;
    }
    if (arguments.size() == 2)
    {
        // send un message par default à la cible kické
        for (size_t i = 0)
        std::cout << client << ": " << targets << "was kicked from the channel\r\n" << std::endl;
    }
    else
    {
        std::string comment;
    	for (size_t i = 2; i < arguments.size(); ++i)
    	{
            comment += arguments[i];
            if (i < arguments.size() - 1)
                comment += " ";
    	}
		// send message à la cible kické
        
    }
}