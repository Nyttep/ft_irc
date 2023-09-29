void    execute_PRIVMSG(Command command, Server server)
{
   if (command.getParam().empty() || command.getParam().size() < 2)
    {
        std::cerr << "Redirection 461" << std::endl;
        return ;
    }
    if (command.getParam()[0].empty())
    {
        std::cerr << "Redirection 411" << std::endl;
        return;
    }
    std::vector<std::string>    targets;
    targets = collect_arguments(command.getParam()[0]);
    if (targets.size() > TARGMAX)
    {
        std::cerr << "Redirection 407" << std::endl;
        return ;
    }
    for (size_t i = 0; i != targets.size(); ++i)
    {
        if (chantypes(targets[i][0]) == true)
        {
            if (server.chanExist(targets[i]) == false)
                std::cerr << "Redirection 403" << std::endl;
            if (on_channel(command.getSource(), server.getChan(channel[0])) == false)
                std::cerr << "Redirection 404" << std::endl;   
        }
        else
        {
            if (correct_user(server, targets[i]) == false)
                std::cerr << "Redirection 401" << std::endl;
        }
    }
    std::string   message;
    for (size_t i = 1; i != command.getParam().size(); ++i)
    {
        if (!command.getParam()[i].empty())
        {
            if (!message.empty())
                message += " ";
            message += (command.getParam()[i]);
        }
    }
    if (message.empty())
    {
        std::cerr << "Redirection 412" << std::endl;
        return ;
    }
    // Envoi
}
// FAIRE une RPL_TOOMANYTARGETS(407), pas dans le manuel