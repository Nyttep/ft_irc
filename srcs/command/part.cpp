void    execute_PART(Command command, Server server)
{
    std::vector<std::string>    channel;
    if (arguments.empty() || argument[0].empty())
    {
        std::cerr << "Redirection 461" << std::endl;
    }
    channel = collect_arguments(argument[0]);

    for (size_t i = 0; i != channel.size(); ++i)
    {
        if (correct_chan(channel[i]) == true)
            // leave channel and send message to users on chan
    }
}