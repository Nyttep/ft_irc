#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <string>
# include <vector>

class Command
{
	private:
	User						*_source;
	std::string					_verb;
	std::vector<std::string>	_params;

	Command();
	Command(const Command &src);

	public:
	Command(User source, std::string verb, std::vector<std::string> params);
	~Command();
	Command&				operator=(const Command& src);
	void					setSource(User client);
	User					getSource();
	void					setVerb(std::string verb);
	std::string				getVerb();
	void					setParams(std::vector<std::string> params);
	void					setPParams(int it, std::string string);
	std::vector<std::string>	getParams();
};

#endif