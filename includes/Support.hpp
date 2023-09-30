#ifndef SUPPORT_HPP
# define SUPPORT_HPP

# define CASEMAPPING "ascii"
# define CHANLIMIT "&#:4"
# define CHANMODES "i, t, k, o, l"
# define CHANNELLEN 24
# define CHANTYPES "&#"
# define KICKLEN 64
# define MAXLIST 5
# define MODES 1
# define NETWORK "IRC_NETWORK"
# define NICKLEN 16
# define PREFIX "@"
# define TARGMAX "PRIVMSG:3,JOIN:3,KICK:1,PART:3"
# define TOPICLEN 64
# define USERLEN 16

bool	chantypes(char c);
int		targmax(std::string target);
int		chanlimit(std::string prefixe);

#endif