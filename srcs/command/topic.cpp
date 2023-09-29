#include <iostream>
#include <string>
#include <cstdlib>

void	execute_TOPIC(Command command, Server server)
{
	if (command.getParams().empty() || command.getParams().size() < 1 || command.getParams()[0].empty())
	{
		std::cerr << "Redirection 461" << std::endl;
		return ;
	}
	if (server.chanExist(command.getParams()[0]) == false)
	{
		std::cerr << "Redirection 403" << std::endl;
		return;
	}
	if (command.getParams().size() == 1)
	{
		if (server.getChan(command.getParams()[0]).getTopic().empty())
			std::cout << "Redirection 331" << std::endl;
		else
			std::cout << "Redirection 332 suivi de 333" << std::endl;
	}
	else
	{
		if (server.getChan(command.getParams()[0]).getT() == true && is_operator(command.getSource(), server.getChan(command.getParams()[0])) == false)
		{
			std::cerr << "Redirection 482" << std::endl;
			return;
		}
		std::string new_topic;
    	for (size_t i = 1; i < command.getParams().size(); ++i)
    	{
     		if (!command.getParam()[i].empty())
       		{
            	if (!new_topic.empty())
                	new_topic += " ";
            	new_topic += (command.getParam()[i]);
        	}
    	}
		if (new_topic.empty())
			server.getChan(command.getParam()[0]).setTopic("");
		else
			server.getChan(command.getParam()[0]).setTopic(new_topic);
	}
}