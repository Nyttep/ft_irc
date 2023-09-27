void    execute_PING(std::vector<std::string>   string)
{
    if (arguments.empty() || arguments.size() < 1 || arguments[0].empty())
    {
        std::cerr << "Redirection 461" << std::endl;
    }
    std::string PONG = "PONG ";
    PONG += arguments[0];
    // renvoie au client PONG Avec "SERVER_NAME: ";
}