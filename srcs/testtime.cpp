#include <iostream>
#include <string>
#include <vector>

std::vector<std::string>	collect_arguments(std::string string)
{
	std::vector<std::string>	vector;
	std::string					buff;
	size_t						begin = 0, end = 0;

	while ((end = string.find(',', begin)) != std::string::npos)
	{
		buff = string.substr(begin, end - begin);
		vector.push_back(buff);
		begin = end +1; 
	}
    buff = string.substr(begin, end - begin);
    vector.push_back(buff);
	return (vector);
}

int main(int argc, char **argv) {

    if (argc != 2)
        return (0);
    std::string mess = argv[1];
    std::vector<std::string> res;

    res = collect_arguments(mess);
    for (std::vector<std::string>::iterator it = res.begin(); it != res.end(); ++it)
	{
		if (it->empty())
			std::cout << "Argument : (null)" << std::endl;
		else	
			std::cout << "Argument : \"" << *it << "\"" << std::endl;
	}
    return 0;
}