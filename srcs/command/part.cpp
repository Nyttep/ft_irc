void    multiple_PART(Command command, Server server, std::vector<std::string> *channels, size_t *i)
{
        if (server.chanExist(channels[i]) == false)
        {
            std::cerr << "Redirectio 403" << std::endl;
            channels->erase(channels->begin() + i);
            --i;
            return ;
        }
        if (on_channel(command.getSource(), server.getChan(channels[i])) == false)
        {
            std::cerr << "Redirection 442" << std::endl;
            channels->erase(channels->begin() + i);
            --i;
            return ;
        }
        std::string message_channel = command.getSource().getNName() + " has left the channel " + channels[i];
        std::string messag_user = "You have left the channel " + channels[i];
        if (command.getParams().size > 1)
        {
            message_channel += " : ";
            for (size_t j = 1; j != command.getParam().size(); ++j)
            {
                if (!command.getParam()[j].empty())
                    message_channel += " " + command.getParam()[j];
            }
        }
        if (is_operator(command.getSource(), server.getChan(channels[i])) == true)
            server.getChan(channels[i]).removeOperator(command.getSource());
        else
            server.getChan(channels[i]).removeUser(command.getSource());
        std::cout << message_channel << std::endl;
        std::cout << message_user << std::endl;
}

void    execute_PART(Command command, Server server)
{
    std::vector<std::string>    channels;
    if (comman.getParams().empty() || command.getParams()[0].empty())
    {
        std::cerr << "Redirection 461" << std::endl;
        return ;
    }
    std::vector<std::string>    channels = collect_arguments(command.getParams()[0]);
    if (channels.size() > targmax("PART:"))
    {
        std::cerr << "Too many targets" << std::endl;
        return ;
    }
    for (size_t i = 0; i != channel.size(); ++i)
    {
        multiple_PART(command, server, &channels, &i);
    }
}