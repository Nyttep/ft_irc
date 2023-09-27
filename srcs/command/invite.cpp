#include	<iostream>
#include    <cstring>
#include	<vector>

void	execute_INVITE(std::vector<std::string>  arguments)
{
	if (arguments.empty() || arguments.size() < 2 || arguments[0].empty() || arguments[1].empty())
	{
		std::cout << "Redirection 461" << std::endl;
		return (0);
	}
	if (correct_chan(arguments[0]) == false)
		return;
	if (channel.i == true && is_operator(client, channel) == false)
	{
		std::cerr << "Redirection 482" << std::endl;
		return ;
	}
	if (on_channel(channel, client) == false)
	{
		std::cerr << "Redirection 442" << std::endl;
	}
	if (on_channel(channel, target) == true)
	{
		std::cerr << "Redirection 443" << std::endl;
	}	
	//Succes
	std::cout << "Redirection 341 à User command et message invite pour la cible" << std::endl;
	return (0);
}