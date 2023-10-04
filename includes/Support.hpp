/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Support.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:40:30 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/04 16:37:27 by pdubois          ###   ########.fr       */
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
# define MODES 1
# define PREFIX "@"
# define TARGMAX "PRIVMSG:3,MSG:3,JOIN:3,KICK:1,PART:3"
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
