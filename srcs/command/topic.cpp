#include <iostream>
#include <string>
#include <cstdlib>

void	execute_TOPIC(std::vector<std::string> arguments)
{
	if (arguments.empty() || arguments.size() < 1 || arguments[0].empty())
	{
		std::cerr << "Redirection 461" << std::endl;
		return ;
	}
	if (correct_chan(arguments[0]) == false)
		return;
	if (argument.size() == 1)
	{
		if (!Channel->topic.empty())
			std::cout << "Redirection 331" << std::endl;
		else
			std::cout << "Redirection 332 suivi de 333" << std::endl;
	}
	else
	{
		if (channel.t == true && is_operator(client, channel) == false)
		{
			std::cerr << "Redirection 482" << std::endl;
		}
		std::string new_topic;
    	for (size_t i = 1; i < arguments.size(); ++i)
    	{
            new_topic += arguments[i];
            if (i < arguments.size() - 1)
                new_topic += " ";
    	}
		set_topic(new_topic);
	}
}