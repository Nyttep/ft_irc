#ifndef SUPPORT_HPP
# define SUPPORT_HPP

# include "irc.hpp"

# define NETWORK "IRC_NETWORK"
# define CASEMAPPING "ascii"
# define CHANTYPES "&#"
# define CHANLIMIT "&#:4"
# define CHANMODES "i, t, k, o, l"
# define MODES 1
# define PREFIX "@"
# define TARGMAX "PRIVMSG:3,MSG:3,JOIN:3,KICK:1,PART:3"
# define NICKLEN 16
# define USERLEN 16
# define CHANNELLEN 24
# define KICKLEN 64
# define TOPICLEN 64

bool	chantypes(char c);
int		targmax(std::string target);
int		chanlimit(std::string prefixe);
bool	have_prefix(char c);

#endif