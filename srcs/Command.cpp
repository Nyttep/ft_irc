/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:42:31 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/02 16:42:32 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

Command::Command()
{}

Command::~Command()
{}

Command::Command(const User& source) : _source(source)
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

void	Command::setSource(User source)
{
	*_source = source;
}

User*	Command::getSource()
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
