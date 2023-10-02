#include "irc.hpp"

size_t	chanlimit(char prefixe)
{
	std::string limit = CHANLIMIT;
	std::string	res;
	size_t begin = limit.find(prefixe);
	if (begin != std::string::npos)
	{
		while (begin < limit.length() && !isdigit(limit[begin]))
			begin++;
		res = limit.substr(begin, std::string::npos - begin);
		begin = std::atoi(res.c_str());
		if (begin != 0)
			return (begin);
		else
			return (INT_MAX - 1);
	}
	return (0);
}

size_t	targmax(std::string target)
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

bool	have_prefix(char c)
{
	std::string prefix = PREFIX;
	if (prefix.find(c) != std::string::npos)
		return (true);
	return (false);
}