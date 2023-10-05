/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_err_command.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:40:19 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/05 17:00:03 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPL_ERR_COMMAND_HPP
# define RPL_ERR_COMMAND_HPP

# include "irc.hpp"

# define SERVERNAME "ft_irc"
# define VERSION "1.0"
# define HOSTNAME "127.0.0.1"


# define US_PRIVMSG(ipaddress, client, message) (std::string(":") + ipaddress + " PRIVMSG " + client + " :" + message + "\r\n")
# define RPL_NOTICE(ipaddress, client, message) (std::string(":") + ipaddress + " NOTICE " + client + " :" + message + "\r\n")
# define US_INVITE(ipaddress, client, channel) (std::string(":") + ipaddress + " INVITE " + client + " " + channel + "\r\n")
# define RPL_MODE(ipaddress, channel, modechar, parameter) (std::string(":") + ipaddress + " MODE " + channel + " " + modechar + parameter + "\r\n")
# define US_MODE(ipaddress, channel, modechar, parameter) (std::string(":") + ipaddress + " MODE " + channel + " " + modechar + parameter + "\r\n")
# define US_JOIN(ipaddress, channel) (std::string(":") + ipaddress + " JOIN " + channel + "\r\n")
# define US_KICK(ipaddress, channel, target, message) (std::string(":") + ipaddress + " KICK " + channel + " " + target + message + "\r\n")
# define US_NICK(formername, newname) (std::string(":") + formername + " NICK " + newname + "\r\n")
# define US_PART(ipaddress, channel, message) (std::string(":") + ipaddress + " PART " + channel + message + "\r\n")
# define RPL_PONG(ipaddress, token) (std::string(":") + ipaddress + " PONG " + token + "\r\n")
# define US_QUIT(ipaddress, message) (std::string(":") + ipaddress + " QUIT " + message + "\r\n")
# define RPL_ERROR(ipaddress, message) (std::string(":") + ipaddress + " ERROR " + message + "\r\n")

// 001
# define RPL_WELCOME(ipaddress, client, nick) (std::string(":") + ipaddress + " 001 " + client + " :Welcome to the " + SERVERNAME + " Network, " + nick + "\r\n")

// 002
# define RPL_YOURHOST(ipaddress, client) (std::string(":") + ipaddress + " 002 " + client + " :Your host is " + SERVERNAME + ", running version " + VERSION + "\r\n")

// 003
# define RPL_CREATED(ipaddress, client, datetime) (std::string(":") + ipaddress + " 003 " + client + " :This server was created " + datetime + "\r\n")

// 004
# define RPL_MYINFO(ipaddress, client, av_channel_mode) (std::string(":") + ipaddress + " 004 " + client + " " + SERVERNAME + " " + VERSION + " available user mode: available channel mode: " + av_channel_mode + "\r\n")

// 005
# define RPL_ISUPPORT(ipaddress, client, tokens) (std::string(":") + ipaddress + " 005 " + client + " " + tokens + " :are supported by this server\r\n")

// 324
# define RPL_CHANNELMODEIS(ipaddress, client, channel, modestring) (std::string(":") + ipaddress + "324" + client + " " + channel + " " + modestring + "\r\n")

// 329
# define RPL_CREATIONTIME(ipaddress, client, channel, creationtime) (std::string(":") + ipaddress + " 329 " + client + " " + channel + " " + creationtime + "\r\n")

// 331
# define RPL_NOTOPIC(ipaddress, client, channel) (std::string(":") + ipaddress + " 331 " + client + " " + channel + " :No topic is set\r\n")

// 332
# define RPL_TOPIC(ipaddress, client, channel, topic) (std::string(":") + ipaddress + " 332 " + client + " " + channel + " :" + topic + "\r\n")

// 336
# define RPL_INVITELIST(ipaddress, client, channel) (std::string(":") + ipaddress + " 336 " + client + " " + channel + "\r\n")

// 337
# define RPL_ENDOFINVITELIST(ipaddress, client) (std::string(":") + ipaddress + " 337 " + client + " :End of /INVITE list\r\n")

// 341
# define RPL_INVITING(ipaddress, client, nick, channel) (std::string(":") + ipaddress + " 341 " + client + " " + nick + " " + channel + "\r\n")

// 353
# define RPL_NAMEREPLY(ipaddress, client, channel, nick) (std::string(":") + ipaddress + " 353 " + client + " = " + channel + " :" + nick + "\r\n")

// 366
# define RPL_ENDOFNAMES(ipaddress, client, channel) (std::string(":") + ipaddress + " 366 " + client + " " + channel + " :End of /NAMES list\r\n")

// 400
# define ERR_UNKNOWNERROR(ipaddress, client, command, info) (std::string(":") + ipaddress + " 400 " + client + " " + command + " :" + info + "\r\n")

// 401
# define ERR_NOSUCHNICK(ipaddress, client, nickname) (std::string(":") + ipaddress + " 401 " + client + " " + nickname + " :No such nick\r\n")

// 403
# define ERR_NOSUCHCHANNEL(ipaddress, client, channel) (std::string(":") + ipaddress + " 403 " + client + " " + channel + " :No such channel\r\n")

// 404
# define ERR_CANNOTSENDTOCHAN(ipaddress, client, channel) (std::string(":") + ipaddress + " 404 " + client + " " + channel + " :Cannot send to channel\r\n")

// 405
# define ERR_TOOMANYCHANNELS(ipaddress, client, channel) (std::string(":") + ipaddress + " 405 " + client + " " + channel + " :You have joined too many channels\r\n")

// 407
# define ERR_TOOMANYTARGETS(ipaddress, client) (std::string(":") + ipaddress + " 407 " + client + " :You selected too many targets\r\n")

// 411
# define ERR_NORECIPIENT(ipaddress, client, command) (std::string(":") + ipaddress + " 411 " + client + " :No recipient given " + command + "\r\n")

// 412
# define ERR_NOTEXTTOSEND(ipaddress, client) (std::string(":") + ipaddress + " 412 " + client + " :No text to send\r\n")

// 417
# define ERR_INPUTTOOLONG(ipaddress, client) (std::string(":") + ipaddress + " 417 " + client + " :Input line was too long\r\n")

// 421
# define ERR_UNKNOWNCOMMAND(ipaddress, client, command) (std::string(":") + ipaddress + " 421 " + client + " " + command + " :Unknown command\r\n")

// 431
# define ERR_NONICKNAMEGIVEN(ipaddress, client) (std::string(":") + ipaddress + " 431 " + client + " :No nickname given\r\n")

// 432
# define ERR_ERRONEUSNICKNAME(ipaddress, client, nick) (std::string(":") + ipaddress + " 432 " + client + " " + nick + " :Erroneus nickname\r\n")

// 433
# define ERR_NICKNAMEINUSE(ipaddress, client, nick) (std::string(":") + ipaddress + " 433 " + client + " " + nick + " :Nickname is already in use\r\n")

// 441
# define ERR_USERNOTINCHANNEL(ipaddress, client, nick, channel) (std::string(":") + ipaddress + " 441 " + client + " " + nick + " " + channel + " :They aren't on that channel\r\n")

// 442
# define ERR_NOTONCHANNEL(ipaddress, client, channel) (std::string(":") + ipaddress + " 442 " + client + " " + channel + " :You're not on that channel\r\n")

// 443
# define ERR_USERONCHANNEL(ipaddress, client, nick, channel) (std::string(":") + ipaddress + " 443 " + client + " " + nick + " " + channel + " :is already on channel\r\n")

// 451
# define ERR_NOTREGISTERED(ipaddress, client) (std::string(":") + ipaddress + " 451 " + client + " :You have not registered\r\n")

// 461
# define ERR_NEEDMOREPARAMS(ipaddress, client, command) (std::string(":") + ipaddress + " 461 " + client + " " + command + " :Not enough parameters\r\n")

// 462
# define ERR_ALREADYREGISTERED(ipaddress, client) (std::string(":") + ipaddress + " 462 " + client + " :You may not reregister\r\n")

// 464
# define ERR_PASSWDMISMATCH(ipaddress, client) (std::string(":") + ipaddress + " 464 " + client + " :Password incorrect\r\n")

// 471
# define ERR_CHANNELISFULL(ipaddress, client, channel) (std::string(":") + ipaddress + " 471 " + client + " " + channel + " :Cannot join channel (+l)\r\n")

// 472
# define ERR_UNKNOWNMODE(ipaddress, client, modechar) (std::string(":") + ipaddress + " 472 " + client + " " + modechar + " :is unknown mode char to me\r\n")

// 473
# define ERR_INVITEONLYCHAN(ipaddress, client, channel) (std::string(":") + ipaddress + " 473 " + client + " " + channel + " :Cannot join channel (+i)\r\n")

// 475
# define ERR_BADCHANNELKEY(ipaddress, client, channel) (std::string(":") + ipaddress + " 475 " + client + " " + channel + " :Cannot join channel (+k)\r\n")

// 476
# define ERR_BADCHANMASK(ipaddress, channel) (std::string(":") + ipaddress + " 476 " + channel + " :Bad Channel Mask\r\n")

// 482
# define ERR_CHANPRIVSNEEDED(ipaddress, client, channel) (std::string(":") + ipaddress + " 482 " + client + " " + channel + " :You're not channel operator\r\n")

// 525
# define ERR_INVALIDKEY(ipaddress, client, target_chan) (std::string(":") + ipaddress + " 525 " + client + " " + target_chan + " :Key is not well-formed\r\n")

// 696
# define RPL_INVALIDMODEPARAM(ipaddress, client, target, mode_char, parameter, description) (std::string(":") + ipaddress + " 696 " + client + " " + target + " " + mode_char + " " + parameter + " :" + description + "\r\n")

#endif
