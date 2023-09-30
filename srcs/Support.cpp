#include "irc.hpp"

int	chanlimit(std::string prefixe)
{
	std::string chanlimit = CHANLIMIT;
	std::string	res;
	size_t begin = chanlimit.find(prefixe);
	if (begin != std::string::npos)
	{
		while (begin < chanlimit.length() && !isdigit(chanlimit[begin]))
			begin++;
		res = chanlimit.substr(begin, std::string::npos - begin);
		begin = std::atoi(res.c_str());
		if (begin != 0)
			return (begin);
	}
	return (INT_MAX - 1);
}

int	targmax(std::string target) /*modifier pour que saute le :*/
{
	std::string	targmax = TARGMAX;
	std::string	res;
	size_t begin = targmax.find(target + ':');
	if (begin != std::string::npos)
	{
		begin += target.length();
		size_t end = targmax.find(",", begin);
			res = targmax.substr(begin, end - begin);
			return (std::atoi(res.c_str()));
	}
	return (INT_MAX - 1);
}

bool	chantypes(char c)
{
	std::string	chantypes = CHANTYPES;
	size_t i = chantypes.find(c);
	if (i != std::string::npos)
		return (true);
	return (false);
}
