#include <vector>
#include <string>
#include <iostream>

void    execute_USER(Command command, Server server)
{
    if (command.getParams().empty() || command.getParams().size() != 4 || command.getParams()[0].empty() || command.getParams()[1].empty() || command.getParams()[2].empty() || command.getParams()[3].empty())
    {
        if (command.getParams().size() > 4)
            std::cerr << "Toomanyparams" << std::endl;
        else
            std::cerr << "Redirection 461" << std::endl;
        return ;
    }
    if (command.getParams()[1] != "0" && command.getParams()[2] != "*")
    {
        std::cerr << "Redirection 400" << std::endl;
    }
    if (command.getParams()[0].length() > USERLEN)
    {
        command.setPParams(0, command.getParams()[0].erase(USERLEN, command.getParams()[0].length() - USERLEN));
    }
    std::string real_name;
    for (size_t i = 3; i < command.getParams().size(); ++i)
    {
        if (!command.getParam()[i].empty())
        {
            if (!real_name.empty())
                real_name += " ";
            real_name += (command.getParam()[i]);
        }
    }
    command.getSource().setUName(command.getParams()[0]);
    command.getSource().setRName(real_name);
}