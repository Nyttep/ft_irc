void    execute_PRIVMSG(std::vector<std::string> arguments)
{
   if (argument.empty() || arguments.size() < 2)
    {
        std::cerr << "Redirection 461" << std::endl;
    }
    for (size_t i = 0; i != arguments.size(), ++i)
    {
        if (arguments[i].empty())
        std::cerr << "Redirection 461" << std::endl;
    }
    
}
// FAIRE une RPL_TOOMANYTARGETS(407), pas dans le manuel