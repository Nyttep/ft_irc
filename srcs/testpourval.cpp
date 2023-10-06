std::cout << "source :" << command.getSource()->getNName() << std::endl;
	if (command.getVerb().empty())
		std::cout << "verb : (null)" << std::endl;
	else	
		std::cout << "verb : \"" << command.getVerb() << "\"" << std::endl;
	for (size_t it = 0; it != command.getParams().size(); ++it)
	{
		if (command.getParams().empty())
			std::cout << "Argument : (null)" << std::endl;
		else	
			std::cout << "Argument : \"" << command.getParams()[it] << "\"" << std::endl;
	}