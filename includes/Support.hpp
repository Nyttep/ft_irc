/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Support.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:40:30 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/06 14:50:49 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUPPORT_HPP
# define SUPPORT_HPP

# include "irc.hpp"

# define NETWORK "IRC_NETWORK"
# define CASEMAPPING "ascii"
# define CHANTYPES "&#"
# define CHANLIMIT "&#:4"
# define CHANMODES ",o,kl,it"
# define PREFIX "@"
# define MODES 4
# define TARGMAX "PRIVMSG:3,JOIN:3,KICK:2,PART:3,NOTICE:3"
# define NICKLEN 16
# define USERLEN 16
# define CHANNELLEN 24
# define KICKLEN 64
# define TOPICLEN 64

class User;

bool	    chantypes(char c);
size_t	    targmax(std::string target);
size_t	    chanlimit(char prefixe);
bool	    have_prefix(char c);
std::string setUserAddress(User &user);

#endif
