#include <iostream>
#include <cstring>
#include <vector>

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

void	execute_INVITE(std::vector<std::string> arguments)
{
	if (arguments.empty())
		std::cout << "Redirection 461" << std::endl;
	// 
	
	
	//Succes
	std::cout << "Redirection 341" << std::endl;
}

void	execute_command(std::string command, std::vector<std::string> arguments)
{
	if (command == "NICK")
		execute_NICK(arguments);
	else if (command == "USER")
		execute_USER(arguments);
	else if (command == "PASS")
		execute_PASS(arguments);
	else if (command == "MODE")
		execute_MODE(arguments);
	else if (command == "JOIN")
		execute_JOIN(arguments);
	else if (command == "PART")
		execute_PART(arguments);
	else if (command == "PING")
		execute_PING(arguments);
	else if (command == "PONG")
		execute_PONG(arguments);
	else if (command == "KICK")
		execute_KICK(arguments);
	else if (command == "PRIVMSG")
		execute_PRIVMSG(arguments);
	else if (command == "QUIT")
		execute_QUIT(arguments);
	else if (command == "INVITE")
		execute_INVITE(arguments);
	else if (command == "TOPIC")
		execute_TOPIC(arguments);
	else
		std::cout << "Redirection 421" << std::endl;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (0);
    std::string reception = argv[1];
    std::string	command;
    std::vector<std::string> arguments;
	std::string::size_type space;

	reception = trim(reception);
	space = reception.find(' ');
	command = reception.substr(0, space);
	reception.erase(0, command.length() + 1);
    while (!reception.empty())
    {
        reception = trim(reception);
        space = reception.find(' ');
        if (space != std::string::npos)
        {
            arguments.push_back(reception.substr(0, space));
            reception = reception.substr(space + 1);
        }
        else
        {
            arguments.push_back(reception);
			reception = "";
        }
    }
	std::cout << "Command : " << command << "$" << std::endl;
    for (std::vector<std::string>::iterator it = arguments.begin(); it != arguments.end(); ++it)
    {
        std::cout << "Argument : " << *it << "$" << std::endl;
    }

	std::cout << "Reception : " << reception << "$" << std::endl;

    execute_command(command, arguments);

    return 0;
}