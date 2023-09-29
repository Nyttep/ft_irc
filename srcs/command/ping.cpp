void    execute_PING(Command command, Server server)
{
    if (command.getParams().empty() || command.getParams()[0].empty() || command.getParams().size() != 1)
    {
        if (command.getParams().size() > 1)
            std::cerr << "Too many Params" << std::endl;
        else
            std::cerr << "Redirection 461" << std::endl;
        return;
    }
    std::string PONG = "PONG " + SERVER_NAME + " " + command.getParams()[0];
}