#include <iostream>
#include <vector>
#include <string>

void    execute_QUIT(std::vector<std::string> arguments)
{
    std::string	message = "Quit: ";
    if (arguments.empty())
		message += "Disconnecting from IRC Server";
	else
	{
		for (size_t i = 1; i < arguments.size(); ++i)
    	{
            message += arguments[i];
            if (i < arguments.size() - 1)
                message += " ";
    	}
	}
	std::cout << "Envoie du message" << std::endl;
	// Fonction de deconnexion
}