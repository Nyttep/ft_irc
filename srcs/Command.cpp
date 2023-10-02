#include "irc.hpp"

Command::Command()
{}

Command::~Command()
{}

Command::Command(const User &source) : _source(source)
{}

Command::Command(const Command& src)
{
	*this = src;
}

Command&	Command::operator=(const Command &src)
{
	_source = src._source;
	_verb = src._verb;
	_params = src._params;
	return (*this);
}

User&	Command::getSource()
{
	return (_source);
}

void	Command::setVerb(std::string verb)
{
	_verb = verb;
}

std::string	Command::getVerb()
{
	return (_verb);
}

void	Command::setParams(std::vector<std::string> params)
{
	_params = params;
}

void	Command::setPParams(int it, std::string string)
{
	_params[it] = string;
}

std::vector<std::string>	Command::getParams()
{
	return (_params);
}
