#include <iostream>
#include <ctime>
#include <string>
#include <sstream>

std::string	DateCreation()
{
	std::string str;
    std::stringstream stream;
	std::time_t time = std::time(NULL);

	std::tm *tm = std::localtime(&time);
    stream << tm->tm_hour << ":" << tm->tm_min << " " << tm->tm_mday << "/" << 1 + tm->tm_mon << "/" << tm->tm_year - 100;
    str += stream.str();
    return (str);
}

# define ERR_INPUTTOOLONG(client) (":" client " :Input line was too long\r\n")
# define SERVERNAME "ft_irc"

int main() {


    std::string dateHeure = DateCreation();
    std::cout << "Date et heure actuelles : " << dateHeure << std::endl;
    std::cout << ERR_INPUTTOOLONG(SERVERNAME) << std::endl;
    return 0;
}