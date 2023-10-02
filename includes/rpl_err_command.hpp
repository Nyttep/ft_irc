/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_err_command.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:40:19 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/02 19:09:55 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPL_ERR_COMMAND_HPP
# define RPL_ERR_COMMAND_HPP

# include "irc.hpp"

# define SERVERNAME "ft_irc"
# define VERSION "1.0"

//# define RPL_WELCOME(client, nick) (":" + client + " 001 :Welcome to the " SERVERNAME " Network, " nick "\r\n")

// 001
# define RPL_WELCOME(client, nick) (std::string(":") + SERVERNAME + " 001 " + client + " :Welcome to the " + SERVERNAME + " Network, " + nick + "\r\n")

// 002
# define RPL_YOURHOST(client) (std::string(":") + SERVERNAME + " 002 " + client + " :Your host is " + SERVERNAME + ", running version " + VERSION + "\r\n")

// 003
# define RPL_CREATED(client, datetime) (std::string(":") + SERVERNAME + " 003 " + client + " :This server was created" + datetime + "\r\n")

// 004
# define RPL_MYINFO(client, av_channel_mode) (std::string(":") + SERVERNAME + " 004 " + client + " " + SERVERNAME + " " + VERSION + " available user mode: available channel mode: " + av_channel_mode + "\r\n")

// 005
# define RPL_ISUPPORT(client, tokens) (std::string(":") + SERVERNAME + " 005 " + client + " " + tokens + " :are supported by this server\r\n")

// 010
# define RPL_BOUNCE(client, hostname, port, info) (std::string(":") + SERVERNAME + " 010 " + client + " " + hostname + " " + port + " :" + info + "\r\n")

// 212
# define RPL_STATSCOMMANDS(client, command, count) (std::string(":") + SERVERNAME + " 212 " + client + " " + command + " " + count + "\r\n")

// 219
# define RPL_ENDOFSTATS(client, stats_letter) (std::string(":") + SERVERNAME + " 219 " + client + " " + stats_letter + " :End of /STATS report\r\n")

// 221
# define RPL_UMODEIS(client, user_modes) (std::string(":") + SERVERNAME + " 221 " + client + " " + user_modes + "\r\n")

// 242
# define RPL_STATSUPTIME(client, days, hours, minutes, seconds) (std::string(":") + SERVERNAME + " 242 " + client + " :Server Up " + days + " days " + hours + ":" + minutes + ":" + seconds + "\r\n")

// 251
# define RPL_LUSERCLIENT(client, u, i, s) (std::string(":") + SERVERNAME + " 251 " + client + " :There are " + u + " users and " + i + " invisible on " + s + " servers\r\n")

// 252
# define RPL_USEROP(client, ops) (std::string(":") + SERVERNAME + " 252 " + client + " " + ops + " :operator(s) online\r\n")

// 253
# define RPL_LUSERUNKNOWN(client, connections) (std::string(":") + SERVERNAME + " 253 " + client + " " + connections + " :unknown connection(s)\r\n")

// 254
# define RPL_LUSERCHANNELS(client, channels) (std::string(":") + SERVERNAME + " 254 " + client + " " + channels + " :channels formed\r\n")

// 255
# define RPL_LUSERME(client, c, s) (std::string(":") + SERVERNAME + " 255 " + client + " :I have " + c + " clients and " + s + " servers\r\n")

// 256
# define RPL_ADMINME(client, server) (std::string(":") + SERVERNAME + " 256 " + client + " " + server + " :Administrative info\r\n")

// 257
# define RPL_ADMINLOC1(client, info) (std::string(":") + SERVERNAME + " 257 " + client + " :" + info + "\r\n")

// 258
# define RPL_ADMINLOC2(client, info) (std::string(":") + SERVERNAME + " 258 " + client + " :" + info + "\r\n")

// 259
# define RPL_ADMINEMAIL(client, info) (std::string(":") + SERVERNAME + " 259 " + client + " :" + info + "\r\n")

// 263
# define RPL_TRYAGAIN(client, command) (std::string(":") + SERVERNAME + " 263 " + client + " " + command + " :Please wait a while and try again\r\n")

// 265
# define RPL_LOCALUSERS(client, u, m) (std::string(":") + SERVERNAME + " 265 " + client + " :Current local users " + u + ", max " + m + "\r\n")

// 266
# define RPL_GLOBALUSERS(client, u, m) (std::string(":") + SERVERNAME + " 266 " + client + " :Current global users " + u + ", max " + m + "\r\n")

// 276
# define RPL_WHOISCERTFP(client, nick, fingerprint) (std::string(":") + SERVERNAME + " 276 " + client + " " + nick + " :has client certificate fingerprint " + fingerprint + "\r\n")

// 300
# define RPL_NONE(void) (std::string(":") + SERVERNAME + " 300 " + + "Undefined format\r\n")

// 301
# define RPL_AWAY(client, nick, message) (std::string(":") + SERVERNAME + " 301 " + client + " " + nick + " :" + message + "\r\n")

// 305
# define RPL_UNAWAY(client) (std::string(":") + SERVERNAME + " 305 " + client + " :You are no longer marked as being away\r\n")

// 306
# define RPL_NOWAWAY(client) (std::string(":") + SERVERNAME + " 306 " + client + " :You have been marked as being away\r\n")

// 307
# define RPL_WHOISREGNICK(client, nick) (std::string(":") + SERVERNAME + " 307 " + client + " " + nick + " :has identified for this nick\r\n")

// 311
# define RPL_WHOISUSER(client, nick, username, host, realname) (std::string(":") + SERVERNAME + " 311 " + client + " " + nick + " " + username + " " + host + " * :" + realname + "\r\n")

// 312
# define RPL_WHOISSERVER(client, nick, server, server_info) (std::string(":") + SERVERNAME + " 312 " + client + " " + nick + " " + server + " :" + server_info + "\r\n")

// 313
# define RPL_WHOISOPERATOR(client, nick) (std::string(":") + SERVERNAME + " 313 " + client + " " + nick + " :is an IRC operator\r\n")

// 314
# define RPL_WHOWASUSER(client, nick, username, host, realname) (std::string(":") + SERVERNAME + " 314 " + client + " " + nick + " " + username + " " + host + " * :" + realname + "\r\n")

// 315
# define RPL_ENDOFWHO(client, mask) (std::string(":") + SERVERNAME + " 315 " + client + " " + mask + " :End of WHO list\r\n")

// 317
# define RPL_WHOISIDLE(client, nick, secs, signon) (std::string(":") + SERVERNAME + " 317 " + client + " " + nick + " " + secs + " " + signon + " : seconds idle, signon time\r\n")

// 318
# define RPL_ENDOFWHOIS(client, nick) (std::string(":") + SERVERNAME + " 318 " + client + " " + nick + " :End of /WHOIS list\r\n")

// 319
# define RPL_WHOISCHANNELS(client, nick, channel) (std::string(":") + SERVERNAME + " 319 " + client + " " + nick + " :" + channel + "\r\n")

// 320
# define RPL_WHOISSPECIAL(client, nick) (std::string(":") + SERVERNAME + " 320 " + client + " " + nick + " :blah blah blah\r\n")

// 321
# define RPL_LISTSTART(client) (std::string(":") + SERVERNAME + " 321 " + client + " Channel :Users Name\r\n")

// 322
# define RPL_LIST(client, channel, client_count, topic) (std::string(":") + SERVERNAME + " 322 " + client + " " + channel + " " +client_count + " :" + topic + "\r\n")

// 323
# define RPL_LISTEND(client) (std::string(":") + SERVERNAME + " 323 " + client + " :End of /LIST\r\n")

// 324
# define RPL_CHANNELMODEIS(client, channel, modestring) (std::string(":") + SERVERNAME + "324" + client + " " + channel + " " + modestring + "\r\n")

// 329
# define RPL_CREATIONTIME(client, channel, creationtime) (std::string(":") + SERVERNAME + " 329 " + client + " " + channel + " " + creationtime + "\r\n")

// 330
# define RPL_WHOISACCOUNT(client, nick, account) (std::string(":") + SERVERNAME + " 330 " + client + " " + nick + " " + account + " :is logged in as\r\n")

// 331
# define RPL_NOTOPIC(client, channel) (std::string(":") + SERVERNAME + " 331 " + client + " " + channel + " :No topic is set\r\n")

// 332
# define RPL_TOPIC(client, channel, topic) (std::string(":") + SERVERNAME + " 332 " + client + " " + channel + " :" + topic + "\r\n")

// 333
# define RPL_TOPICWHOTIME(client, channel, nick, setat) (std::string(":") + SERVERNAME + " 333 " + client + " " + channel + " " + nick + " " + setat + "\r\n")

// 336
# define RPL_INVITELIST(client, channel) (std::string(":") + SERVERNAME + " 336 " + client + " " + channel + "\r\n")

// 337
# define RPL_ENDOFINVITELIST(client) (std::string(":") + SERVERNAME + " 337 " + client + " :End of /INVITE list\r\n")

// 338
# define RPL_WHOISACTUALLY() /* A faire plus tard, pas compris*/

// 341
# define RPL_INVITING(client, nick, channel) (std::string(":") + SERVERNAME + " 341 " + client + " " + nick + " " + channel + "\r\n")

// 346
# define RPL_INVEXLIST(client, channel, mask) (std::string(":") + SERVERNAME + " 346 " + client + " " + channel + " " + mask + "\r\n")

// 347
# define RPL_ENDOFINVEXLIST(client, channel) (std::string(":") + SERVERNAME + " 347 " + client + " " + channel + " :End of channel Invite Exception List\r\n")

// 348
# define RPL_EXCEPTLIST(client, channel, mask) (std::string(":") + SERVERNAME + " 348 " + client + " " + channel + " " + mask + "\r\n")

// 349
# define RPL_ENDOFEXCEPTLIST(client, channel) (std::string(":") + SERVERNAME + " 349 " + client + " " + channel + " :End of channel exception list")

// 351
# define RPL_VERSION(client, comments) (std::string(":") + SERVERNAME + " 351 " + client + " " + VERSION + " " + SERVERNAME + " :" + comments + "\r\n")

// 352
# define RPL_WHOREPLY(client, channel, username, host, server, nick, flags, hopcount, realname) (std::string(":") + SERVERNAME + " 352 " + client + " " + channel + " " + username + " " + host + " " + server + " " + nick + " " + flags + " :" + hopcount + " " + realname + "\r\n")

// 353
# define RPL_NAMEREPLY(client, channel, nick) (std::string(":") + SERVERNAME + " 353 " + client + " " + channel + " :" + nick + "\r\n")

// 364
# define RPL_LINKS(client, server, hopcount, server_info) (std::string(":") + SERVERNAME + " 364 " + client + " " + server + " :" + hopcount + " " + server_info + "\r\n")

// 365
# define RPL_ENDOFLINKS(client) (std::string(":") + SERVERNAME + " 365 " + client + " * :End of /LINKS list\r\n")

// 366
# define RPL_ENDOFNAMES(client, channel) (std::string(":") + SERVERNAME + " 366 " + client + " " + channel + " :End of /NAMES list\r\n")

// 367
# define RPL_BANLIST(client, channel, mask) (std::string(":") + SERVERNAME + " 367 " + client + " " + channel + " " + mask + "\r\n")

// 368
# define RPL_ENDOFBANLIST(client, channel) (std::string(":") + SERVERNAME + " 368 " + client + " " + channel + " :End of ban list\r\n")

// 369
# define RPL_ENDOFWHOWAS(client, nick) (std::string(":") + SERVERNAME + " 369 " + client + " " + nick + " :End of WHOWAS\r\n")

// 371
# define RPL_INFO(client, string) (std::string(":") + SERVERNAME + " 371 " + client + " :" + string + "\r\n")

// 372
# define RPL_MOTD(client, motd) (std::string(":") + SERVERNAME + " 372 " + client + " :" + motd + "\r\n")

// 374
# define RPL_ENDOFINFO(client) (std::string(":") + SERVERNAME + " 374 " + client + " :End of INFO list\r\n")

// 375
# define RPL_MODSTART(client, server) (std::string(":") + SERVERNAME + " 375 " + client + " :- " + server + " Message of the day - \r\n")

// 376
# define RPL_ENDOFMOTD(client) (std::string(":") + SERVERNAME + " 376 " + client + " : End of /MOTD command.\r\n")

// 378
# define RPL_WHOISHOST(client, nick) (std::string(":") + SERVERNAME + " 378 " + client + " " + nick + " :is connecting from *@localhost 127.0.0.1\r\n")

// 379
# define RPL_WHOISMODES(client, nick) (std::string(":") + SERVERNAME + " 379 " + client + " " + nick + " : is using modes +ailosw\r\n")

// 381
# define RPL_YOUREOPER(client) (std::string(":") + SERVERNAME + " 381 " + client + " :You are now an IRC operator\r\n")

// 382
# define RPL_REHASHING(client, config_files) (std::string(":") + SERVERNAME + " 382 " + client + " " + config_files + " :Rehashing\r\n")

// 391
# define RPL_TIME(client, server, timestamp, TS_offset, time) (std::string(":") + SERVERNAME + " 391 " + client + " " + server + " " + timestamp + " " + TS_offset + " :" + time + "\r\n")

// 400
# define ERR_UNKNOWNERROR(client, command, info) (std::string(":") + SERVERNAME + " 400 " + client + " " + command + " :" + info + "\r\n")

// 401
# define ERR_NOSUCHNICK(client, nickname) (std::string(":") + SERVERNAME + " 401 " + client + " " + nickname + " :No such nick/channel\r\n")

// 402
# define ERR_NOSUCHSERVER(client) (std::string(":") + SERVERNAME + " 402 " + client + SERVERNAME + " :No such server\r\n")

// 403
# define ERR_NOSUCHCHANNEL(client, channel) (std::string(":") + SERVERNAME + " 403 " + client + " " + channel + " :No such channel\r\n")

// 404
# define ERR_CANNOTSENDTOCHAN(client, channel) (std::string(":") + SERVERNAME + " 404 " + client + " " + channel + " :Cannot send to channel\r\n")

// 405
# define ERR_TOOMANYCHANNELS(client, channel) (std::string(":") + SERVERNAME + " 405 " + client + " " + channel + " :You have joined too many channels\r\n")

// 406
# define ERR_WASNOSUCHNICK(client) (std::string(":") + SERVERNAME + " 406 " + client + " :There was no such nickname\r\n")

// 407
# define ERR_TOOMANYTARGETS(client) (std::string(":") + SERVERNAME + " 407 " + client + " :You selected too many targets\r\n")

// 409
# define ERR_NOORIGIN(client) (std::string(":") + SERVERNAME + " 409 " + client + " :No origin specified\r\n")

// 411
# define ERR_NORECIPIENT(client, command) (std::string(":") + SERVERNAME + " 411 " + client + " :No recipient given " + command + "\r\n")

// 412
# define ERR_NOTEXTTOSEND(client) (std::string(":") + SERVERNAME + " 412 " + client + " :No text to send\r\n")

// 417
# define ERR_INPUTTOOLONG(client) (std::string(":") + SERVERNAME + " 417 " + client + " :Input line was too long\r\n")

// 421
# define ERR_UNKNOWNCOMMAND(client, command) (std::string(":") + SERVERNAME + " 421 " + client + " " + command + " :Unknown command\r\n")

// 422
# define ERR_NOMOTD(client) (std::string(":") + SERVERNAME + " 422 " + client + " :MOTD File is missing\r\n")

// 431
# define ERR_NONICKNAMEGIVEN(client) (std::string(":") + SERVERNAME + " 431 " + client + " :No nickname given\r\n")

// 432
# define ERR_ERRONEUSNICKNAME(client, nick) (std::string(":") + SERVERNAME + " 432 " + client + " " + nick + " :Erroneus nickname\r\n")

// 433
# define ERR_NICKNAMEINUSE(client, nick) (std::string(":") + SERVERNAME + " 433 " + client + " " + nick + " :Nickname is already in use\r\n")

// 436
# define ERR_NICKCOLLISION(client, nick, user, host) (std::string(":") + SERVERNAME + " 436 " + client + " " + nick + " :Nickname collision KILL from " + user + "@" + host + "\r\n")

// 441
# define ERR_USERNOTINCHANNEL(client, nick, channel) (std::string(":") + SERVERNAME + " 441 " + client + " " + nick + " " + channel + " :They aren't on that channel\r\n")

// 442
# define ERR_NOTONCHANNEL(client, channel) (std::string(":") + SERVERNAME + " 442 " + client + " " + channel + " :You're not on that channel\r\n")

// 443
# define ERR_USERONCHANNEL(client, nick, channel) (std::string(":") + SERVERNAME + " 443 " + client + " " + nick + " " + channel + " :is already on channel\r\n")

// 451
# define ERR_NOTREGISTERED(client) (std::string(":") + SERVERNAME + " 451 " + client + " :You have not registered\r\n")

// 461
# define ERR_NEEDMOREPARAMS(client, command) (std::string(":") + SERVERNAME + " 461 " + client + " " + command + " :Not enough parameters\r\n")

// 462
# define ERR_ALREADYREGISTERED(client) (std::string(":") + SERVERNAME + " 462 " + client + " :You may not reregister\r\n")

// 464
# define ERR_PASSWDMISMATCH(client) (std::string(":") + SERVERNAME + " 464 " + client + " :Password incorrect\r\n")

// 465
# define ERR_YOUREBANNEDCREEP(client) (std::string(":") + SERVERNAME + " 465 " + client + " :You are banned from this server\r\n")

// 471
# define ERR_CHANNELISFULL(client, channel) (std::string(":") + SERVERNAME + " 471 " + client + " " + channel + " :Cannot join channel (+l)\r\n")

// 472
# define ERR_UNKNOWNMODE(client, modechar) (std::string(":") + SERVERNAME + " 472 " + client + " " + modechar + " :is unknown mode char to me\r\n")

// 473
# define ERR_INVITEONLYCHAN(client, channel) (std::string(":") + SERVERNAME + " 473 " + client + " " + channel + " :Cannot join channel (+i)\r\n")

// 474
# define ERR_BANNEDFROMCHAN(client, channel) (std::string(":") + SERVERNAME + " 474 " + client + " " + channel + " :Cannot join channel (+b)\r\n")

// 475
# define ERR_BADCHANNELKEY(client, channel) (std::string(":") + SERVERNAME + " 475 " + client + " " + channel + " :Cannot join channel (+k)\r\n")

// 476
# define ERR_BADCHANMASK(channel) (std::string(":") + SERVERNAME + " 476 " + channel + " :Bad Channel Mask\r\n")

// 481
# define ERR_NOPRIVILEGES(client) (std::string(":") + SERVERNAME + " 481 " + client + " :Permission Denied- You're not an IRC operator\r\n")

// 482
# define ERR_CHANPRIVSNEEDED(client, channel) (std::string(":") + SERVERNAME + " 482 " + client + " " + channel + " :You're not channel operator\r\n")

// 483
# define ERR_CANTKILLSERVER(client) (std::string(":") + SERVERNAME + " 483 " + client + " : You can't kill a server\r\n")

// 491
# define ERR_NOOPERHOST(client) (std::string(":") + SERVERNAME + " 491 " + client + " :No O-lines for your host\r\n")

// 501
# define ERR_UMODEUNKNOWNFLAG(client) (std::string(":") + SERVERNAME + " 501 " + client + " :Unknown MODE flag\r\n")

// 502
# define ERR_USERDONTMATCH(client) (std::string(":") + SERVERNAME + " 502 " + client + " :Can't change mode for other users\r\n")

// 524
# define ERR_HELPNOTFOUND(client, subject) (std::string(":") + SERVERNAME + " 524 " + client + " " + subject + " :No help available on this topic\r\n")

// 525
# define ERR_INVALIDKEY(client, target_chan) (std::string(":") + SERVERNAME + " 525 " + client + " " + target_chan + " :Key is not well-formed\r\n")

// 670
# define RPL_STARTTLS(client) (std::string(":") + SERVERNAME + " 670 " + client + " :STARTTLS successful, proceed with TLS handshake\r\n")

// 671
# define RPL_WHOISSECURE(client, nick) (std::string(":") + SERVERNAME + " 671 " + client + " " + nick + " :is using a secure connection\r\n")

// 691
# define ERR_STARTTLS(client) (std::string(":") + SERVERNAME + " 691 " + client + " :STARTTLS failed (Wrong moon phase)\r\n")

// 696
# define RPL_INVALIDMODEPARAM(client, target, mode_char, parameter, description) (std::string(":") + SERVERNAME + " 696 " + client + " " + target + " " + mode_char + " " + parameter + " :" + description + "\r\n")

// 704
# define RPL_HELPSTART(client, subject, line) (std::string(":") + SERVERNAME + " 704 " + client + " " + subject + " :" + line + "\r\n")

// 705
# define RPL_HELPTXT(client, subject, line) (std::string(":") + SERVERNAME + " 705 " + client + " " + subject + " :" + line + "\r\n")

// 706
# define RPL_ENDOFHELP(client, subject, line) (std::string(":") + SERVERNAME + " 706 " + client + " " + subject + " :" + line + "\r\n")

// 723
# define RPL_NOPRIVS(client, priv) (std::string(":") + SERVERNAME + " 723 " + client + " " + priv + " :Insufficient oper privileges\r\n")

// 900
# define RPL_LOGGEDIN(client, nick, user, host, account, username) (std::string(":") + SERVERNAME + " 900 " + client + " " + nick + "!" + user + "@" + host + " " + account + " :You are now logged in as " + username + "\r\n")

// 901
# define RPL_LOGGEDOUT(client, nick, user, host) (std::string(":") + SERVERNAME + " 901 " + client + " " + nick + "!" + user + "@" + host + " :You are now logged out\r\n")

// 902
# define ERR_NICKLOCKED(client) (std::string(":") + SERVERNAME + " 902 " + client + " :You must use a nick assigned to you\r\n")

// 903
# define RPL_SASLSUCCESS(client) (std::string(":") + SERVERNAME + " 903 " + client + ": SASL authentication successful\r\n")

// 904
# define ERR_SASLFAIL(client) (std::string(":") + SERVERNAME + " 904 " + client + " :SASL authentication failed\r\n")

// 905
# define ERR_SASLTOOLONG(client) (std::string(":") + SERVERNAME + " 905 " + client + " :SASL message too long\r\n")

// 906
# define ERR_SASLABORTED(client) (std::string(":") + SERVERNAME + " 906 " + client + " :SASL authentication aborted\r\n")

// 907
# define ERR_SASLALREADY(client) (std::string(":") + SERVERNAME + " 907 " + client + " : You have already authenticated using SASL\r\n")

// 908
# define RPL_SASLMECHS(client, mechanisms) (std::string(":") + SERVERNAME + " 908 " + client + " " + mechanisms + " :are available SASL mechanisms\r\n")

#endif
