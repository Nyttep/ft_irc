#include <vector>
#include <string>
#include <iostream>

void    execute_USER(std::vector<std::string> arguments)
{
    if (arguments.empty() || arguments.size() < 4)
    {
        std::cerr << "Redirection 461" <<std::endl;
        return ;
    }
    std::vector<std::string>::iterator it;

    for (it = arguments.begin(); it != arguments.end(); ++it)
    {
        if ((*it).empty())
        {
            std::cerr << "Redirection 461" << std::endl;
        }
    }
    if (arguments[0].length() > USERLEN)
        arguments[0].substr(0, USERLEN);
    std::string real_name;
    for (size_t i = 3; i < arguments.size(); ++i)
    {
            real_name += arguments[i];
            if (i < arguments.size() - 1)
                real_name += " ";
    }

    // Vérifier si deja enregistrer 
    // if ()
//      std::cerr << "Redirection 462" << std::endl;
    // ajouter dans la classe User
}