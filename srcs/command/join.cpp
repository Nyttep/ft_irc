void    execute_JOIN(std::vector<std::string> arguments)
{
    // check arguments
    if (argument.empty() || arguments.size() < 1)
    {
        std::cerr << "Redirection 461" << std::endl;
    }
    for (size_t i = 0; i != arguments.size(), ++i)
    {
        if (arguments[i].empty())
        std::cerr << "Redirection 461" << std::endl;
    }
    // if (argument[0] == "0")
    // {
    //     // Commande qui quitte tous les chans
    // }
    
    // récupération de tous les chans et les keys
    std::vector<std::string>    channels;
    std::vector<std::string>    keys;

    channels = collect_arguments(arguments[0]);
    if (arguments.size() > 1)
        keys = collect_arguments(arguments[1]);
    
    for (size_t i = 0; i != channels.size(); ++i)
    {
        if (correct_chan(channels[i]) == false)
            break;
    }
    for (size_t i = 0; i !=channels.size(), ++i)
    {
        if (Channel[i]._k == true && (i <= keys.size() && Channel[i].key == keys[i]))
        // Ok key
        else
        {
            std::cerr << "Redirection 475" << std::endl;
        }
        if (Channel[i]._i == true && (on_invite(Clients, Channel[i]) == false))
            std::cerr << "Redirection 473" << std::endl;
        if (Channel[i]._l == true && (max_user(Channel[i]) == true))
            std::cerr << "Redirection 471" << std::endl;
        if (max_channel(Clients, channels[i]) == true)
            std::cerr << "Redirection 405" << std::endl;
    }

// Success, un join message, suivi de RPL 332, RPL 333(optionnel), RPL 353 RPL 366
// Autre client ont un message ifnormant le nouvel arrivant
// Pas précision si l'utilisateur est déjà dans le chan, propose de passer sous silence
}