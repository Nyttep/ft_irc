bool	correct_user(Server server, std::string client)
{
	std::map<int, User> userlist = server.getUser();
	for(std::map<int, User>::iterator *it = userlist.begin(); it != userlist.end(); ++it)
	{
		if (client == *it->second.getNName())
			return true;
	}
	return false;
}

// verif si client est ope
bool	is_operator(User client, Channel channel)
{
	std::vector<User> operators = channel.getOperators();
	
	for (size_t i = 0; i != operators.size(); ++i)
	{
		if (client.getNName() == operators[i].getNName())
			return true;
	}
		return false;
}

// verifie si client sur chan
bool    on_channel(User client, Channel channel)
{
    std::vector<User>	users = channel.getOperators();
	for (size_t i = 0; i != users.size(); ++i)
    {
        if (client.getNName() == users[i].getNName())
            return true;
    }
	users = channel.getUser();
	for (size_t i = 0; i != users.size(); ++i)
    {
        if (client.getNName() == users[i].getNName())
            return true;
    }
	return false;
}

// collect les arguments qui sont separe par virgule
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

// verifie si client est dans la liste invite
bool on_invite(User client, Channel chan)
{
	std::vector<User>	invite = chan.getInvite()
	for (size_t i=0; i != invite.size(); ++i)
	{
		if (client.getNName() == invite[i])
			return true;
	}
	return false;
}

// si limit, verifie si client peut etre ajoute
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

// verifie le nb de chan le client est
bool	max_channel(User user, std::string chan)
[
	std::vector<Channel>	list;
	if (chan[0] == '#')
		list = user.getGChannel();
	else
		list = user.getLChannel();
	if ((list.size() + 1) > CHANLIMIT)
		return true;
	return false;
]