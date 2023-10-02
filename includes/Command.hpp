#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "irc.hpp"

class Command
{
	private:
	User						*_source;
	std::string					_verb;
	std::vector<std::string>	_params;

	Command();
	Command(const Command &src);

	public:
	Command(const User &source);
	~Command();
	Command&					operator=(const Command& src);
	void						setSource(User client);
	User*						getSource();
	void						setVerb(std::string verb);
	std::string					getVerb();
	void						setParams(std::vector<std::string> params);
	void						setPParams(int it, std::string string);
	std::vector<std::string>	getParams();
};

#endif