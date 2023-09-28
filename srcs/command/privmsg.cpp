void    execute_PRIVMSG(std::vector<std::string> arguments)
{
   if (argument.empty() || arguments.size() < 2)
    {
        std::cerr << "Redirection 461" << std::endl;
    }
    if (arguments[0].empty())
    {
        std::cerr << "Redirection 411" << std::endl;
    }
    if (arguments[1].empty())
    {
        std::cerr << "Redirection 412" << std::endl;
    }
    std::vector<std::string>    targets;
    targets = collect_arguments(arguments[0]);
    if (targets.size() > TARGMAX)
        std::cerr << "Redirection 407" << std::endl;
    for (size_t i = 0; i != targets.size(); ++i)
    {
        if (targets[i][0] == '#' || targets[i][0] == '&')
        {
            if (correct_chan(targets) == false)
                std::cerr << "Redirection 403" << std::endl;
            if (on_channel(channel, client) == false)
                std::cerr << "Redirection 404" << std::endl;
            
        }
        else
        {
            if (correct_user(targets) == false)
                std::cerr << "Redirection 401" << std::endl;
        }
    }
    std::vector<std::string>    message;
    for (size_t i = 1; i != arguments.size(); ++i)
    {
        message.append(arguments[i]);
    }
    // send message
}
// FAIRE une RPL_TOOMANYTARGETS(407), pas dans le manuel