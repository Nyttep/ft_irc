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
		if (client = channel.operators[i])
			break;
	}
	if (client != channel.operators[i])
	{
		std::cerr << "Redirection 482" << std::endl;
		return false;
	}
	return true;
}