/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_err_command.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:40:19 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/04 19:07:39 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPL_ERR_COMMAND_HPP
# define RPL_ERR_COMMAND_HPP

# include "irc.hpp"

# define SERVERNAME "ft_irc"
# define VERSION "1.0"
# define HOSTNAME "127.0.0.1"

//# define RPL_WELCOME(client, nick) (":" + client + " 001 :Welcome to the " SERVERNAME " Network, " nick "\r\n")

# define US_PRIVMSG(ipaddress, client, message) (std::string(":") + ipaddress + " PRIVMSG " + client + " :" + message + "\r\n")
# define US_INVITE(ipaddress, client, channel) (std::string(":") + ipaddress + " INVITE " + client + " " + channel + "\r\n")
# define RPL_MODE(ipaddress, channel, modechar, parameter) (std::string(":") + ipaddress + " MODE " + channel + " " + modechar + " " + parameter + "\r\n")
# define US_MODE(ipaddress, channel, modechar, parameter) (std::string(":") + ipaddress + " MODE " + channel + " " + modechar + parameter + "\r\n")
# define US_JOIN(ipaddress, channel) (std::string(":") + ipaddress + " JOIN " + channel + "\r\n")
# define RPL_KICK(ipaddress, channel, target, message) (std::string(":") + ipaddress + " KICK " + channel + " " + target + message + "\r\n")
# define US_NICK(formername, newname) (std::string(":") + formername + " NICK " + newname + "\r\n")
# define US_PART(ipaddress, channel, message) (std::string(":") + ipaddress + " PART " + channel + " " + message + "\r\n")
# define RPL_PONG(ipaddress, token) (std::string(":") + ipaddress + " PONG " + token + "\r\n")
# define US_QUIT(ipaddress, message) (std::string(":") + ipaddress + " QUIT " + message + "\r\n")
# define RPL_ERROR(ipaddress, message) (std::string(":") + ipaddress + " ERROR " + message + "\r\n")
# define RPL_TOPICCHANGED(ipaddress, channel, message) (std::string("") + ipaddress + " TOPIC " + channel + " :" + message + "\r\n")

// 001
# define RPL_WELCOME(ipaddress, client, nick) (std::string(":") + ipaddress + " 001 " + client + " :Welcome to the " + SERVERNAME + " Network, " + nick + "\r\n")

// 002
# define RPL_YOURHOST(ipaddress, client) (std::string(":") + ipaddress + " 002 " + client + " :Your host is " + SERVERNAME + ", running version " + VERSION + "\r\n")

// 003
# define RPL_CREATED(ipaddress, client, datetime) (std::string(":") + ipaddress + " 003 " + client + " :This server was created" + datetime + "\r\n")

// 004
# define RPL_MYINFO(ipaddress, client, av_channel_mode) (std::string(":") + ipaddress + " 004 " + client + " " + SERVERNAME + " " + VERSION + " available user mode: available channel mode: " + av_channel_mode + "\r\n")

// 005
# define RPL_ISUPPORT(ipaddress, client, tokens) (std::string(":") + ipaddress + " 005 " + client + " " + tokens + " :are supported by this server\r\n")

// 010
# define RPL_BOUNCE(ipaddress, client, hostname, port, info) (std::string(":") + ipaddress + " 010 " + client + " " + hostname + " " + port + " :" + info + "\r\n")

// 212
# define RPL_STATSCOMMANDS(ipaddress, client, command, count) (std::string(":") + ipaddress + " 212 " + client + " " + command + " " + count + "\r\n")

// 219
# define RPL_ENDOFSTATS(ipaddress, client, stats_letter) (std::string(":") + ipaddress + " 219 " + client + " " + stats_letter + " :End of /STATS report\r\n")

// 221
# define RPL_UMODEIS(ipaddress, client, user_modes) (std::string(":") + ipaddress + " 221 " + client + " " + user_modes + "\r\n")

// 242
# define RPL_STATSUPTIME(ipaddress, client, days, hours, minutes, seconds) (std::string(":") + ipaddress + " 242 " + client + " :Server Up " + days + " days " + hours + ":" + minutes + ":" + seconds + "\r\n")

// 251
# define RPL_LUSERCLIENT(ipaddress, client, u, i, s) (std::string(":") + ipaddress + " 251 " + client + " :There are " + u + " users and " + i + " invisible on " + s + " servers\r\n")

// 252
# define RPL_USEROP(ipaddress, client, ops) (std::string(":") + ipaddress + " 252 " + client + " " + ops + " :operator(s) online\r\n")

// 253
# define RPL_LUSERUNKNOWN(ipaddress, client, connections) (std::string(":") + ipaddress + " 253 " + client + " " + connections + " :unknown connection(s)\r\n")

// 254
# define RPL_LUSERCHANNELS(ipaddress, client, channels) (std::string(":") + ipaddress + " 254 " + client + " " + channels + " :channels formed\r\n")

// 255
# define RPL_LUSERME(ipaddress, client, c, s) (std::string(":") + ipaddress + " 255 " + client + " :I have " + c + " clients and " + s + " servers\r\n")

// 256
# define RPL_ADMINME(ipaddress, client, server) (std::string(":") + ipaddress + " 256 " + client + " " + server + " :Administrative info\r\n")

// 257
# define RPL_ADMINLOC1(ipaddress, client, info) (std::string(":") + ipaddress + " 257 " + client + " :" + info + "\r\n")

// 258
# define RPL_ADMINLOC2(ipaddress, client, info) (std::string(":") + ipaddress + " 258 " + client + " :" + info + "\r\n")

// 259
# define RPL_ADMINEMAIL(ipaddress, client, info) (std::string(":") + ipaddress + " 259 " + client + " :" + info + "\r\n")

// 263
# define RPL_TRYAGAIN(ipaddress, client, command) (std::string(":") + ipaddress + " 263 " + client + " " + command + " :Please wait a while and try again\r\n")

// 265
# define RPL_LOCALUSERS(ipaddress, client, u, m) (std::string(":") + ipaddress + " 265 " + client + " :Current local users " + u + ", max " + m + "\r\n")

// 266
# define RPL_GLOBALUSERS(ipaddress, client, u, m) (std::string(":") + ipaddress + " 266 " + client + " :Current global users " + u + ", max " + m + "\r\n")

// 276
# define RPL_WHOISCERTFP(ipaddress, client, nick, fingerprint) (std::string(":") + ipaddress + " 276 " + client + " " + nick + " :has client certificate fingerprint " + fingerprint + "\r\n")

// 300
# define RPL_NONE(void) (std::string(":") + ipaddress + " 300 " + + "Undefined format\r\n")

// 301
# define RPL_AWAY(ipaddress, client, nick, message) (std::string(":") + ipaddress + " 301 " + client + " " + nick + " :" + message + "\r\n")

// 305
# define RPL_UNAWAY(ipaddress, client) (std::string(":") + ipaddress + " 305 " + client + " :You are no longer marked as being away\r\n")

// 306
# define RPL_NOWAWAY(ipaddress, client) (std::string(":") + ipaddress + " 306 " + client + " :You have been marked as being away\r\n")

// 307
# define RPL_WHOISREGNICK(ipaddress, client, nick) (std::string(":") + ipaddress + " 307 " + client + " " + nick + " :has identified for this nick\r\n")

// 311
# define RPL_WHOISUSER(ipaddress, client, nick, username, host, realname) (std::string(":") + client + " 311 " + nick + " " + username + " " + host + " * :" + realname + "\r\n")

// 312
# define RPL_WHOISSERVER(ipaddress, client, nick, server, server_info) (std::string(":") + ipaddress + " 312 " + client + " " + nick + " " + server + " :" + server_info + "\r\n")

// 313
# define RPL_WHOISOPERATOR(ipaddress, client, nick) (std::string(":") + ipaddress + " 313 " + client + " " + nick + " :is an IRC operator\r\n")

// 314
# define RPL_WHOWASUSER(ipaddress, client, nick, username, host, realname) (std::string(":") + ipaddress + " 314 " + client + " " + nick + " " + username + " " + host + " * :" + realname + "\r\n")

// 315
# define RPL_ENDOFWHO(ipaddress, client, mask) (std::string(":") + ipaddress + " 315 " + client + " " + mask + " :End of WHO list\r\n")

// 317
# define RPL_WHOISIDLE(ipaddress, client, nick, secs, signon) (std::string(":") + ipaddress + " 317 " + client + " " + nick + " " + secs + " " + signon + " : seconds idle, signon time\r\n")

// 318
# define RPL_ENDOFWHOIS(ipaddress, client, nick) (std::string(":") + ipaddress + " 318 " + client + " " + nick + " :End of /WHOIS list\r\n")

// 319
# define RPL_WHOISCHANNELS(ipaddress, client, nick, channel) (std::string(":") + ipaddress + " 319 " + client + " " + nick + " :" + channel + "\r\n")

// 320
# define RPL_WHOISSPECIAL(ipaddress, client, nick) (std::string(":") + ipaddress + " 320 " + client + " " + nick + " :blah blah blah\r\n")

// 321
# define RPL_LISTSTART(ipaddress, client) (std::string(":") + ipaddress + " 321 " + client + " Channel :Users Name\r\n")

// 322
# define RPL_LIST(ipaddress, client, channel, client_count, topic) (std::string(":") + ipaddress + " 322 " + client + " " + channel + " " +client_count + " :" + topic + "\r\n")

// 323
# define RPL_LISTEND(ipaddress, client) (std::string(":") + ipaddress + " 323 " + client + " :End of /LIST\r\n")

// 324
# define RPL_CHANNELMODEIS(ipaddress, client, channel, modestring) (std::string(":") + ipaddress + "324" + client + " " + channel + " " + modestring + "\r\n")

// 329
# define RPL_CREATIONTIME(ipaddress, client, channel, creationtime) (std::string(":") + ipaddress + " 329 " + client + " " + channel + " " + creationtime + "\r\n")

// 330
# define RPL_WHOISACCOUNT(ipaddress, client, nick, account) (std::string(":") + ipaddress + " 330 " + client + " " + nick + " " + account + " :is logged in as\r\n")

// 331
# define RPL_NOTOPIC(ipaddress, client, channel) (std::string(":") + ipaddress + " 331 " + client + " " + channel + " :No topic is set\r\n")

// 332
# define RPL_TOPIC(ipaddress, client, channel, topic) (std::string(":") + ipaddress + " 332 " + client + " " + channel + " :" + topic + "\r\n")

// 333
# define RPL_TOPICWHOTIME(ipaddress, client, channel, nick, setat) (std::string(":") + ipaddress + " 333 " + client + " " + channel + " " + nick + " " + setat + "\r\n")

// 336
# define RPL_INVITELIST(ipaddress, client, channel) (std::string(":") + ipaddress + " 336 " + client + " " + channel + "\r\n")

// 337
# define RPL_ENDOFINVITELIST(ipaddress, client) (std::string(":") + ipaddress + " 337 " + client + " :End of /INVITE list\r\n")

// 338
# define RPL_WHOISACTUALLY() /* A faire plus tard, pas compris*/

// 341
# define RPL_INVITING(ipaddress, client, nick, channel) (std::string(":") + ipaddress + " 341 " + client + " " + nick + " " + channel + "\r\n")

// 346
# define RPL_INVEXLIST(ipaddress, client, channel, mask) (std::string(":") + ipaddress + " 346 " + client + " " + channel + " " + mask + "\r\n")

// 347
# define RPL_ENDOFINVEXLIST(ipaddress, client, channel) (std::string(":") + ipaddress + " 347 " + client + " " + channel + " :End of channel Invite Exception List\r\n")

// 348
# define RPL_EXCEPTLIST(ipaddress, client, channel, mask) (std::string(":") + ipaddress + " 348 " + client + " " + channel + " " + mask + "\r\n")

// 349
# define RPL_ENDOFEXCEPTLIST(ipaddress, client, channel) (std::string(":") + ipaddress + " 349 " + client + " " + channel + " :End of channel exception list")

// 351
# define RPL_VERSION(ipaddress, client, comments) (std::string(":") + ipaddress + " 351 " + client + " " + VERSION + " " + ipaddress + " :" + comments + "\r\n")

// 352
# define RPL_WHOREPLY(ipaddress, client, channel, username, host, server, nick, flags, hopcount, realname) (std::string(":") + ipaddress + " 352 " + client + " " + channel + " " + username + " " + host + " " + server + " " + nick + " " + flags + " :" + hopcount + " " + realname + "\r\n")

// 353
# define RPL_NAMEREPLY(ipaddress, client, channel, nick) (std::string(":") + ipaddress + " 353 " + client + " = " + channel + " :" + nick + "\r\n")

// 364
# define RPL_LINKS(ipaddress, client, server, hopcount, server_info) (std::string(":") + ipaddress + " 364 " + client + " " + server + " :" + hopcount + " " + server_info + "\r\n")

// 365
# define RPL_ENDOFLINKS(ipaddress, client) (std::string(":") + ipaddress + " 365 " + client + " * :End of /LINKS list\r\n")

// 366
# define RPL_ENDOFNAMES(ipaddress, client, channel) (std::string(":") + ipaddress + " 366 " + client + " " + channel + " :End of /NAMES list\r\n")

// 367
# define RPL_BANLIST(ipaddress, client, channel, mask) (std::string(":") + ipaddress + " 367 " + client + " " + channel + " " + mask + "\r\n")

// 368
# define RPL_ENDOFBANLIST(ipaddress, client, channel) (std::string(":") + ipaddress + " 368 " + client + " " + channel + " :End of ban list\r\n")

// 369
# define RPL_ENDOFWHOWAS(ipaddress, client, nick) (std::string(":") + ipaddress + " 369 " + client + " " + nick + " :End of WHOWAS\r\n")

// 371
# define RPL_INFO(ipaddress, client, string) (std::string(":") + ipaddress + " 371 " + client + " :" + string + "\r\n")

// 372
# define RPL_MOTD(ipaddress, client, motd) (std::string(":") + ipaddress + " 372 " + client + " :" + motd + "\r\n")

// 374
# define RPL_ENDOFINFO(ipaddress, client) (std::string(":") + ipaddress + " 374 " + client + " :End of INFO list\r\n")

// 375
# define RPL_MODSTART(ipaddress, client, server) (std::string(":") + ipaddress + " 375 " + client + " :- " + server + " Message of the day - \r\n")

// 376
# define RPL_ENDOFMOTD(ipaddress, client) (std::string(":") + ipaddress + " 376 " + client + " : End of /MOTD command.\r\n")

// 378
# define RPL_WHOISHOST(ipaddress, client, nick) (std::string(":") + ipaddress + " 378 " + client + " " + nick + " :is connecting from *@localhost 127.0.0.1\r\n")

// 379
# define RPL_WHOISMODES(ipaddress, client, nick) (std::string(":") + ipaddress + " 379 " + client + " " + nick + " : is using modes +ailosw\r\n")

// 381
# define RPL_YOUREOPER(ipaddress, client) (std::string(":") + ipaddress + " 381 " + client + " :You are now an IRC operator\r\n")

// 382
# define RPL_REHASHING(ipaddress, client, config_files) (std::string(":") + ipaddress + " 382 " + client + " " + config_files + " :Rehashing\r\n")

// 391
# define RPL_TIME(ipaddress, client, server, timestamp, TS_offset, time) (std::string(":") + ipaddress + " 391 " + client + " " + server + " " + timestamp + " " + TS_offset + " :" + time + "\r\n")

// 400
# define ERR_UNKNOWNERROR(ipaddress, client, command, info) (std::string(":") + ipaddress + " 400 " + client + " " + command + " :" + info + "\r\n")

// 401
# define ERR_NOSUCHNICK(ipaddress, client, nickname) (std::string(":") + ipaddress + " 401 " + client + " " + nickname + " :No such nick/channel\r\n")

// 402
# define ERR_NOSUCHSERVER(ipaddress, client) (std::string(":") + ipaddress + " 402 " + client + ipaddress + " :No such server\r\n")

// 403
# define ERR_NOSUCHCHANNEL(ipaddress, client, channel) (std::string(":") + ipaddress + " 403 " + client + " " + channel + " :No such channel\r\n")

// 404
# define ERR_CANNOTSENDTOCHAN(ipaddress, client, channel) (std::string(":") + ipaddress + " 404 " + client + " " + channel + " :Cannot send to channel\r\n")

// 405
# define ERR_TOOMANYCHANNELS(ipaddress, client, channel) (std::string(":") + ipaddress + " 405 " + client + " " + channel + " :You have joined too many channels\r\n")

// 406
# define ERR_WASNOSUCHNICK(ipaddress, client) (std::string(":") + ipaddress + " 406 " + client + " :There was no such nickname\r\n")

// 407
# define ERR_TOOMANYTARGETS(ipaddress, client) (std::string(":") + ipaddress + " 407 " + client + " :You selected too many targets\r\n")

// 409
# define ERR_NOORIGIN(ipaddress, client) (std::string(":") + ipaddress + " 409 " + client + " :No origin specified\r\n")

// 411
# define ERR_NORECIPIENT(ipaddress, client, command) (std::string(":") + ipaddress + " 411 " + client + " :No recipient given " + command + "\r\n")

// 412
# define ERR_NOTEXTTOSEND(ipaddress, client) (std::string(":") + ipaddress + " 412 " + client + " :No text to send\r\n")

// 417
# define ERR_INPUTTOOLONG(ipaddress, client) (std::string(":") + ipaddress + " 417 " + client + " :Input line was too long\r\n")

// 421
# define ERR_UNKNOWNCOMMAND(ipaddress, client, command) (std::string(":") + ipaddress + " 421 " + client + " " + command + " :Unknown command\r\n")

// 422
# define ERR_NOMOTD(ipaddress, client) (std::string(":") + ipaddress + " 422 " + client + " :MOTD File is missing\r\n")

// 431
# define ERR_NONICKNAMEGIVEN(ipaddress, client) (std::string(":") + ipaddress + " 431 " + client + " :No nickname given\r\n")

// 432
# define ERR_ERRONEUSNICKNAME(ipaddress, client, nick) (std::string(":") + ipaddress + " 432 " + client + " " + nick + " :Erroneus nickname\r\n")

// 433
# define ERR_NICKNAMEINUSE(ipaddress, client, nick) (std::string(":") + ipaddress + " 433 " + client + " " + nick + " :Nickname is already in use\r\n")

// 436
# define ERR_NICKCOLLISION(ipaddress, client, nick, user, host) (std::string(":") + ipaddress + " 436 " + client + " " + nick + " :Nickname collision KILL from " + user + "@" + host + "\r\n")

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

// 465
# define ERR_YOUREBANNEDCREEP(ipaddress, client) (std::string(":") + ipaddress + " 465 " + client + " :You are banned from this server\r\n")

// 471
# define ERR_CHANNELISFULL(ipaddress, client, channel) (std::string(":") + ipaddress + " 471 " + client + " " + channel + " :Cannot join channel (+l)\r\n")

// 472
# define ERR_UNKNOWNMODE(ipaddress, client, modechar) (std::string(":") + ipaddress + " 472 " + client + " " + modechar + " :is unknown mode char to me\r\n")

// 473
# define ERR_INVITEONLYCHAN(ipaddress, client, channel) (std::string(":") + ipaddress + " 473 " + client + " " + channel + " :Cannot join channel (+i)\r\n")

// 474
# define ERR_BANNEDFROMCHAN(ipaddress, client, channel) (std::string(":") + ipaddress + " 474 " + client + " " + channel + " :Cannot join channel (+b)\r\n")

// 475
# define ERR_BADCHANNELKEY(ipaddress, client, channel) (std::string(":") + ipaddress + " 475 " + client + " " + channel + " :Cannot join channel (+k)\r\n")

// 476
# define ERR_BADCHANMASK(ipaddress, channel) (std::string(":") + ipaddress + " 476 " + channel + " :Bad Channel Mask\r\n")

// 481
# define ERR_NOPRIVILEGES(ipaddress, client) (std::string(":") + ipaddress + " 481 " + client + " :Permission Denied- You're not an IRC operator\r\n")

// 482
# define ERR_CHANPRIVSNEEDED(ipaddress, client, channel) (std::string(":") + ipaddress + " 482 " + client + " " + channel + " :You're not channel operator\r\n")

// 483
# define ERR_CANTKILLSERVER(ipaddress, client) (std::string(":") + ipaddress + " 483 " + client + " : You can't kill a server\r\n")

// 491
# define ERR_NOOPERHOST(ipaddress, client) (std::string(":") + ipaddress + " 491 " + client + " :No O-lines for your host\r\n")

// 501
# define ERR_UMODEUNKNOWNFLAG(ipaddress, client) (std::string(":") + ipaddress + " 501 " + client + " :Unknown MODE flag\r\n")

// 502
# define ERR_USERDONTMATCH(ipaddress, client) (std::string(":") + ipaddress + " 502 " + client + " :Can't change mode for other users\r\n")

// 524
# define ERR_HELPNOTFOUND(ipaddress, client, subject) (std::string(":") + ipaddress + " 524 " + client + " " + subject + " :No help available on this topic\r\n")

// 525
# define ERR_INVALIDKEY(ipaddress, client, target_chan) (std::string(":") + ipaddress + " 525 " + client + " " + target_chan + " :Key is not well-formed\r\n")

// 670
# define RPL_STARTTLS(ipaddress, client) (std::string(":") + ipaddress + " 670 " + client + " :STARTTLS successful, proceed with TLS handshake\r\n")

// 671
# define RPL_WHOISSECURE(ipaddress, client, nick) (std::string(":") + ipaddress + " 671 " + client + " " + nick + " :is using a secure connection\r\n")

// 691
# define ERR_STARTTLS(ipaddress, client) (std::string(":") + ipaddress + " 691 " + client + " :STARTTLS failed (Wrong moon phase)\r\n")

// 696
# define RPL_INVALIDMODEPARAM(ipaddress, client, target, mode_char, parameter, description) (std::string(":") + ipaddress + " 696 " + client + " " + target + " " + mode_char + " " + parameter + " :" + description + "\r\n")

// 704
# define RPL_HELPSTART(ipaddress, client, subject, line) (std::string(":") + ipaddress + " 704 " + client + " " + subject + " :" + line + "\r\n")

// 705
# define RPL_HELPTXT(ipaddress, client, subject, line) (std::string(":") + ipaddress + " 705 " + client + " " + subject + " :" + line + "\r\n")

// 706
# define RPL_ENDOFHELP(ipaddress, client, subject, line) (std::string(":") + ipaddress + " 706 " + client + " " + subject + " :" + line + "\r\n")

// 723
# define RPL_NOPRIVS(ipaddress, client, priv) (std::string(":") + ipaddress + " 723 " + client + " " + priv + " :Insufficient oper privileges\r\n")

// 900
# define RPL_LOGGEDIN(ipaddress, client, nick, user, host, account, username) (std::string(":") + ipaddress + " 900 " + client + " " + nick + "!" + user + "@" + host + " " + account + " :You are now logged in as " + username + "\r\n")

// 901
# define RPL_LOGGEDOUT(ipaddress, client, nick, user, host) (std::string(":") + ipaddress + " 901 " + client + " " + nick + "!" + user + "@" + host + " :You are now logged out\r\n")

// 902
# define ERR_NICKLOCKED(ipaddress, client) (std::string(":") + ipaddress + " 902 " + client + " :You must use a nick assigned to you\r\n")

// 903
# define RPL_SASLSUCCESS(ipaddress, client) (std::string(":") + ipaddress + " 903 " + client + ": SASL authentication successful\r\n")

// 904
# define ERR_SASLFAIL(ipaddress, client) (std::string(":") + ipaddress + " 904 " + client + " :SASL authentication failed\r\n")

// 905
# define ERR_SASLTOOLONG(ipaddress, client) (std::string(":") + ipaddress + " 905 " + client + " :SASL message too long\r\n")

// 906
# define ERR_SASLABORTED(ipaddress, client) (std::string(":") + ipaddress + " 906 " + client + " :SASL authentication aborted\r\n")

// 907
# define ERR_SASLALREADY(ipaddress, client) (std::string(":") + ipaddress + " 907 " + client + " : You have already authenticated using SASL\r\n")

// 908
# define RPL_SASLMECHS(ipaddress, client, mechanisms) (std::string(":") + ipaddress + " 908 " + client + " " + mechanisms + " :are available SASL mechanisms\r\n")

#endif
