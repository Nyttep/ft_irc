#include <iostream>
#include <vector>
#include <string>

void    execute_QUIT(Command command, Server server)
{
    std::string	message = "Quit:";
    if (command.getParams().empty())
		message += " Disconnecting from IRC Server";
	else
	{
		for (size_t i = 0; i < command.getParams().size(); ++i)
    	{
            if (!command.getParam()[i].empty())
				message += " " + command.getParams()[i];
    	}
	}
	std::cout << "Envoie du message" << std::endl;
	// Fonction de deconnexion
}