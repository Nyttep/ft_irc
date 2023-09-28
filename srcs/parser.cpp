#include <iostream>
#include <cstring>
#include <vector>

// IMPORTANT: Traiter le :, pas fait.

std::string	trim(const std::string &src)
{
	std::string	whitespace = " \n\r\t\f\v";
	std::string crlf = "\r\n";
	std::string	res = src;
	size_t	start, end;

	start = res.find_first_not_of(whitespace);
	if (start != std::string::npos && start != 0)
		res = res.erase(0, start);
	end = res.find_last_not_of(crlf);
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

// void	execute_command(std::string command, std::vector<std::string> arguments)
// {
// 	if (command == "NICK")
// 		execute_NICK(arguments);
// 	else if (command == "USER")
// 		execute_USER(arguments);
// 	else if (command == "PASS")
// 		execute_PASS(arguments);
// 	else if (command == "MODE")
// 		execute_MODE(arguments);
// 	else if (command == "JOIN")
// 		execute_JOIN(arguments);
// 	else if (command == "PART")
// 		execute_PART(arguments);
// 	else if (command == "PING")
// 		execute_PING(arguments);
// 	else if (command == "PONG")
// 		execute_PONG(arguments);
// 	else if (command == "KICK")
// 		execute_KICK(arguments);
// 	else if (command == "PRIVMSG")
// 		execute_PRIVMSG(arguments);
// 	else if (command == "QUIT")
// 		execute_QUIT(arguments);
// 	else if (command == "INVITE")
// 		execute_INVITE(arguments);
// 	else if (command == "TOPIC")
// 		execute_TOPIC(arguments);
// 	else
// 		std::cout << "Redirection 421" << std::endl;
// }

bool only_space(std::string string)
{
	size_t	i = 0;
	while (string[i])
	{
		if (string[i] != ' ')
			return (false);
		i++;
	}
	return (true);
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
	if (space != std::string::npos)
		reception.erase(0, space);
    while (!reception.empty())
    {
        reception = trim(reception);
        space = reception.find(' ');
        if (reception[0] == ':')
		{
			if (only_space(reception.substr(1, reception.length())) == true)
			{
				arguments.push_back("");
				reception = "";
			}
			else if (reception[1] == ' ')
			{
				arguments.push_back(reception.substr(0, space));
				reception = reception.substr(space + 1);
			}
			else
			{
				reception.erase(0, 1);
				arguments.push_back(reception);
				reception = "";
			}
		}
		else if (space != std::string::npos)
        {
           	arguments.push_back(reception.substr(0, space));
			reception = reception.substr(space + 1);
        }
        else
        {
			if (only_space(reception) == true)
				arguments.push_back("");
			else
			{
           		arguments.push_back(reception);
			}
			reception = "";
        }
    }
	std::cout << "Command : " << command << "$" << std::endl;
    for (std::vector<std::string>::iterator it = arguments.begin(); it != arguments.end(); ++it)
    {
        std::cout << "Argument : " << *it << "$" << std::endl;
    }

	std::cout << "Reception : " << reception << "$" << std::endl;
	if (arguments.size() > 15)
		return (0);
    // execute_command(command, arguments);

    return (0);
}