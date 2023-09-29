#include "ft_irc.hpp"

std::string	trim(const std::string &src)
{
	std::string	whitespace = " \n\r\t\f\v";
	std::string	res = src;
	size_t	start, end;

	start = src.find_first_not_of(whitespace);
	end = src.find_last_not_of(whitespace);
	if (start != std::string::npos && start != 0)
		res = res.erase(0, start - 1);
	if (end != std::string::npos)
		res = res.erase(end + 1);
	return (res);
}

bool	isascii(const std::string src)
{
	for (size_t i = 0; i != src.length(); ++i)
	{
        if (static_cast<unsigned char>(src[i]) > 127)
            return false;
    }
    return true;
}

void	execute_INVITE(std::vector<std::string> client.args)
{
	if (client.args.empty())
		std::cout << "Redirection 461" << std::endl;
	// 
	
	
	//Succes
	std::cout << "Redirection 341" << std::endl;
}

void	execute_command(User& client)
{
	if (client.cmd == "NICK")
		execute_NICK(client.args);
	else if (client.cmd == "USER")
		execute_USER(client.args);
	else if (client.cmd == "PASS")
		execute_PASS(client.args);
	else if (client.cmd == "MODE")
		execute_MODE(client.args);
	else if (client.cmd == "JOIN")
		execute_JOIN(client.args);
	else if (client.cmd == "PART")
		execute_PART(client.args);
	else if (client.cmd == "PING")
		execute_PING(client.args);
	else if (client.cmd == "PONG")
		execute_PONG(client.args);
	else if (client.cmd == "KICK")
		execute_KICK(client.args);
	else if (client.cmd == "PRIVMSG")
		execute_PRIVMSG(client.args);
	else if (client.cmd == "QUIT")
		execute_QUIT(client.args);
	else if (client.cmd == "INVITE")
		execute_INVITE(client.args);
	else if (client.cmd == "TOPIC")
		execute_TOPIC(client.args);
	else
		std::cout << "Redirection 421" << std::endl;
}

int parser(Server& serv, User& client)
{
	std::string::size_type space;

	client.raw = trim(client.raw);
	space = client.raw.find(' ');
	client.cmd = client.raw.substr(0, space);
	client.raw.erase(0, client.cmd.length() + 1);
    while (!client.raw.empty())
    {
        client.raw = trim(client.raw);
        space = client.raw.find(' ');
        if (space != std::string::npos)
        {
            client.args.push_back(client.raw.substr(0, space));
            client.raw = client.raw.substr(space + 1);
        }
        else
        {
            client.args.push_back(client.raw);
			client.raw = "";
        }
    }
	std::cout << "client.cmd : " << client.cmd << "$" << std::endl;
    for (std::vector<std::string>::iterator it = client.args.begin(); it != client.args.end(); ++it)
    {
        std::cout << "Argument : " << *it << "$" << std::endl;
    }

	std::cout << "client.raw : " << client.raw << "$" << std::endl;

    execute_command(client);

    return 0;
}