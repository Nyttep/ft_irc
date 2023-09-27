bool	correct_chan(std::string arguments)
{
	if (arguments[0] != '#' && arguments[0] != '&')
	{
		std::cerr << "Reduirection 403" << std::endl;
		return false;
	}
	for (size_t i = 0; i!=/*vecteur de server des chans*/, ++i)
	{
		if (arguments == /*vecteur[i]*/)
			break;
	}
	if (arguments != /*vecteur[i]*/)
	{
		std::cerr << "Redirection 403" << std::endl;
		return false;
	}
	if (arguments[0] == '#')
	{
		for (size_t i = 0; i!=/*vecteur de user des chans general*/, ++i)
		{
			if (arguments == /*vecteur[i]*/)
				break;
		}
	}
	else
	{
		for (size_t i = 0; i!=/*vecteur de user des chans local*/, ++i)
		{
			if (arguments == /*vecteur[i]*/)
				break;
		}
	}
	if (arguments != /*vecteur[i]*/)
	{
		std::cerr << "Redirection 442" << std::endl;
		return false;
	}
	return true;
}

bool	is_operator(client, channel)
{
	for (size_t i = 0; i != channel.operators; ++i)
	{
		if (client == channel.operators[i])
			break;
	}
	if (client != channel.operators[i])
	{
		std::cerr << "Redirection 482" << std::endl;
		return false;
	}
	return true;
}

bool    on_channel(channel, client)
{
    for (size_t i = 0; i != channel.operators; ++i)
    {
        if (client == channel.operators[i])
            break;
    }
    if (client == channel.operators[i])
    {
        return true;
    }
    for (size_t i = 0; i != channel.users; ++i)
    {
        if (client == channel.users[i])
            break;
    }
    if (client == channel.users[i])
    {
        return true;
    }
	return false;
}

std::vector<std::string>	collect_arguments(std::string	string)
{
	std::vector<std::string>    vector;
    std::string                 buff;
    size_t                      begin = 0, end = 0;

    while ((end = string.find(',', begin)) != std::string::npos)
    {
        buff = string.substr(begin, end - begin);
        vector.push_back(buff);
        begin = end +1; 
    }
	return (vector);
}

bool on_invite(User client, Channel chan)
{
	std::vector<User>	invite = chan.getInvite()
	for (size_t i=0; invite.size(); ++i)
	{
		if (client.getNName() == invite[i])
			return true;
	}
	if (client.getNName() == invite[i])
		return true;
	return false;
}
bool	max_user(Channel chan)
{
	size_t 	nb_user = 0;
	std::vector<User> list = chan.getOperator();
	nb_user = list.size();
	list = chan.getUser();
	nb_user += list.size();
	if ((nb_user + 1) > chan.getlimit())
		return true;
	return false;
}

bool	max_channel(std::string chan, User user)
[
	std::vector<Channel>	list;
	if (chan[0] == '#')
		list = user.getGChannel();
	else
	{
		list = user.getLChannel();
	}
	if ((list.size() + 1) > CHANLIMIT)
		return true;
	return false;
]