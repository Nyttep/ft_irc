#include <iostream>
#include <cstring>
#include <vector>

void    execute_PASS(std::vector<std::string> arguments)
{
    if (arguments.empty() || arguments[0].empty())
    {
        std::cerr << "Redirection 461" << std::endl;
    }
    if (client.registered == true)
    {
        std::cerr << "Redirection 462" << std::endl;
    }
    if (arguments[0] != Server.pass)
    {
        client.pass == false;
        std::cerr << "Redirection 464" << std::endl;
    }
    client.pass == true;
}