#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <string>
# include <vector>

class Command
{
	private:
    std::string					_tags;
	std::string					_source;
	std::string					_verb;
	std::vector<std::string>	_params;

	Command();
	Command(const Command &src);

	public:
	Command(std::string tags, std::string source, std::string verb, std::vector<std::string> params);
	~Command();
	Command&	operator=(const Command& src);
};

#endif