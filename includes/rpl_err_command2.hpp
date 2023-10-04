/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_err_command.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:40:19 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/04 10:30:34 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPL_ERR_COMMAND_HPP
# define RPL_ERR_COMMAND_HPP

# include "irc.hpp"

# define SERVERNAME "ft_irc"
# define LOCALHOST "127.0.0.1"
# define VERSION "1.0"

//# define RPL_WELCOME(client, nick) (":" + client + " 001 :Welcome to the " SERVERNAME " Network, " nick "\r\n")

// 001
# define RPL_WELCOME(client, nick) (std::string(":")  + client + " 001 " + nick + " :Welcome to the " + SERVERNAME + " Network, " + nick + "\r\n")

// 002
# define RPL_YOURHOST(client) (std::string(":") + client + " 002 " + " :Your host is " + LOCALHOST + ", running version " + VERSION + "\r\n")

// 003
# define RPL_CREATED(client, datetime) (std::string(":") + client + " 003 :This server was created " + datetime + "\r\n")

// 004
# define RPL_MYINFO(client, av_channel_mode) (std::string(":") + client + " 004 " + SERVERNAME + " " + VERSION + " available user mode: available channel mode: " + av_channel_mode + "\r\n")

// 005
# define RPL_ISUPPORT(client, tokens) (std::string(":") + client + " 005 " + tokens + " :are supported by this server\r\n")

// 010
# define RPL_BOUNCE(client, hostname, port, info) (std::string(":") + " 010 " + client + " " + hostname + " " + port + " :" + info + "\r\n")

// 212
# define RPL_STATSCOMMANDS(client, command, count) (std::string(":") + " 212 " + client + " 212 " + command + " " + count + "\r\n")

// 219
# define RPL_ENDOFSTATS(client, stats_letter) (std::string(":") + client + " 219 " + stats_letter + " :End of /STATS report\r\n")

// 221
# define RPL_UMODEIS(client, user_modes) (std::string(":") + client + " 221 " + user_modes + "\r\n")

// 242
# define RPL_STATSUPTIME(client, days, hours, minutes, seconds) (std::string(":") + client + " 242 :Server Up " + days + " days " + hours + ":" + minutes + ":" + seconds + "\r\n")

// 251
# define RPL_LUSERCLIENT(client, u, i, s) (std::string(":") +  client + " 251 :There are " + u + " users and " + i + " invisible on " + s + " servers\r\n")

// 252
# define RPL_USEROP(client, ops) (std::string(":") + client + " 252 " + ops + " :operator(s) online\r\n")

// 253
# define RPL_LUSERUNKNOWN(client, connections) (std::string(":") + client + " 253 " + connections + " :unknown connection(s)\r\n")

// 254
# define RPL_LUSERCHANNELS(client, channels) (std::string(":") + client + " 254 " + channels + " :channels formed\r\n")

// 255
# define RPL_LUSERME(client, c, s) (std::string(":") + client + " 255 :I have " + c + " clients and " + s + " servers\r\n")

// 256
# define RPL_ADMINME(client, server) (std::string(":") + client + " 256 " + server + " :Administrative info\r\n")

// 257
# define RPL_ADMINLOC1(client, info) (std::string(":") + client + " 257 :" + info + "\r\n")

// 258
# define RPL_ADMINLOC2(client, info) (std::string(":") + client + " 258 :" + info + "\r\n")

// 259
# define RPL_ADMINEMAIL(client, info) (std::string(":") + client + " 259 :" + info + "\r\n")

// 263
# define RPL_TRYAGAIN(client, command) (std::string(":") + client + " 263 " + command + " :Please wait a while and try again\r\n")

// 265
# define RPL_LOCALUSERS(client, u, m) (std::string(":") + client + " 265 :Current local users " + u + ", max " + m + "\r\n")

// 266
# define RPL_GLOBALUSERS(client, u, m) (std::string(":") + client + " 266 :Current global users " + u + ", max " + m + "\r\n")

// 276
# define RPL_WHOISCERTFP(client, nick, fingerprint) (std::string(":") + client + " 276 " + nick + " :has client certificate fingerprint " + fingerprint + "\r\n")

// 300
# define RPL_NONE(void) (std::string(":") + " 300 " + + "Undefined format\r\n")

// 301
# define RPL_AWAY(client, nick, message) (std::string(":") + client + " 301 " + nick + " :" + message + "\r\n")

// 305
# define RPL_UNAWAY(client) (std::string(":") + client + " 305 :You are no longer marked as being away\r\n")

// 306
# define RPL_NOWAWAY(client) (std::string(":") + client + " 306 :You have been marked as being away\r\n")

// 307
# define RPL_WHOISREGNICK(client, nick) (std::string(":") + client + " 307 " + nick + " :has identified for this nick\r\n")

// 311
# define RPL_WHOISUSER(client, nick, username, host, realname) (std::string(":") + client + " 311 " + nick + " " + username + " " + host + " * :" + realname + "\r\n")

// 312
# define RPL_WHOISSERVER(client, nick, server, server_info) (std::string(":") + client + " 312 " + nick + " " + server + " :" + server_info + "\r\n")

// 313
# define RPL_WHOISOPERATOR(client, nick) (std::string(":") + client + " 313 " + nick + " :is an IRC operator\r\n")

// 314
# define RPL_WHOWASUSER(client, nick, username, host, realname) (std::string(":") + client + " 314 " + nick + " " + username + " " + host + " * :" + realname + "\r\n")

// 315
# define RPL_ENDOFWHO(client, mask) (std::string(":") + client + " 315 " + mask + " :End of WHO list\r\n")

// 317
# define RPL_WHOISIDLE(client, nick, secs, signon) (std::string(":") + client + " 317 " + nick + " " + secs + " " + signon + " : seconds idle, signon time\r\n")

// 318
# define RPL_ENDOFWHOIS(client, nick) (std::string(":") + client + " 318 " + nick + " :End of /WHOIS list\r\n")

// 319
# define RPL_WHOISCHANNELS(client, nick, channel) (std::string(":") + client + " 319 " + nick + " :" + channel + "\r\n")

// 320
# define RPL_WHOISSPECIAL(client, nick) (std::string(":") + client + " 320 " + nick + " :blah blah blah\r\n")

// 321
# define RPL_LISTSTART(client) (std::string(":") + client + " 321 Channel :Users Name\r\n")

// 322
# define RPL_LIST(client, channel, client_count, topic) (std::string(":") + client + " 322 " + channel + " " +client_count + " :" + topic + "\r\n")

// 323
# define RPL_LISTEND(client) (std::string(":") + client + " 323 :End of /LIST\r\n")

// 324
# define RPL_CHANNELMODEIS(client, channel, modestring) (std::string(":") + client + " 324 " + channel + " " + modestring + "\r\n")

// 329
# define RPL_CREATIONTIME(client, channel, creationtime) (std::string(":") + client + " 329 " + channel + " " + creationtime + "\r\n")

// 330
# define RPL_WHOISACCOUNT(client, nick, account) (std::string(":") + client + " 330 " + nick + " " + account + " :is logged in as\r\n")

// 331
# define RPL_NOTOPIC(client, channel) (std::string(":") + client + " 331 " + channel + " :No topic is set\r\n")

// 332
# define RPL_TOPIC(client, channel, topic) (std::string(":") + client + " 332 " + channel + " :" + topic + "\r\n")

// 333
# define RPL_TOPICWHOTIME(client, channel, nick, setat) (std::string(":") + client + " 333 " + channel + " " + nick + " " + setat + "\r\n")

// 336
# define RPL_INVITELIST(client, channel) (std::string(":") + client + " 336 " + channel + "\r\n")

// 337
# define RPL_ENDOFINVITELIST(client) (std::string(":") + client + " 337 :End of /INVITE list\r\n")

// 338
# define RPL_WHOISACTUALLY() /* A faire plus tard, pas compris*/

// 341
# define RPL_INVITING(client, nick, channel) (std::string(":") + client + " 341 " + nick + " " + channel + "\r\n")

// 346
# define RPL_INVEXLIST(client, channel, mask) (std::string(":") + client + " 346 " + channel + " " + mask + "\r\n")

// 347
# define RPL_ENDOFINVEXLIST(client, channel) (std::string(":") + client + " 347 " + channel + " :End of channel Invite Exception List\r\n")

// 348
# define RPL_EXCEPTLIST(client, channel, mask) (std::string(":") + client + " 348 " + channel + " " + mask + "\r\n")

// 349
# define RPL_ENDOFEXCEPTLIST(client, channel) (std::string(":") + client + " 349 " + channel + " :End of channel exception list")

// 351
# define RPL_VERSION(client, comments) (std::string(":") + client + " 351 " + VERSION + " " + " :" + comments + "\r\n")

// 352
# define RPL_WHOREPLY(client, channel, username, host, server, nick, flags, hopcount, realname) (std::string(":")  + client + " 352 " + channel + " " + username + " " + host + " " + server + " " + nick + " " + flags + " :" + hopcount + " " + realname + "\r\n")

// 353
# define RPL_NAMEREPLY(client, channel, nick) (std::string(":") + client + " 353 " + channel + " :" + nick + "\r\n")

// 364
# define RPL_LINKS(client, server, hopcount, server_info) (std::string(":") + client + " 364 " + server + " :" + hopcount + " " + server_info + "\r\n")

// 365
# define RPL_ENDOFLINKS(client) (std::string(":") + client + " 365 * :End of /LINKS list\r\n")

// 366
# define RPL_ENDOFNAMES(client, channel) (std::string(":") + client + " 366 " + channel + " :End of /NAMES list\r\n")

// 367
# define RPL_BANLIST(client, channel, mask) (std::string(":") + client + " 367 " + channel + " " + mask + "\r\n")

// 368
# define RPL_ENDOFBANLIST(client, channel) (std::string(":") + client + " 368 " + channel + " :End of ban list\r\n")

// 369
# define RPL_ENDOFWHOWAS(client, nick) (std::string(":") + client + " 369 " + nick + " :End of WHOWAS\r\n")

// 371
# define RPL_INFO(client, string) (std::string(":") + client + " 370 :" + string + "\r\n")

// 372
# define RPL_MOTD(client, motd) (std::string(":") + client + " 371 :" + motd + "\r\n")

// 374
# define RPL_ENDOFINFO(client) (std::string(":") + client + " 374 :End of INFO list\r\n")

// 375
# define RPL_MODSTART(client, server) (std::string(":") + client + " 375 :- " + server + " Message of the day - \r\n")

// 376
# define RPL_ENDOFMOTD(client) (std::string(":") + client + " 376 : End of /MOTD command.\r\n")

// 378
# define RPL_WHOISHOST(client, nick) (std::string(":") + client + " 378 " + nick + " :is connecting from *@localhost 127.0.0.1\r\n")

// 379
# define RPL_WHOISMODES(client, nick) (std::string(":") + client + " 379 " + nick + " : is using modes +ailosw\r\n")

// 381
# define RPL_YOUREOPER(client) (std::string(":") + client + " 381 :You are now an IRC operator\r\n")

// 382
# define RPL_REHASHING(client, config_files) (std::string(":") + client + " 382 " + config_files + " :Rehashing\r\n")

// 391
# define RPL_TIME(client, server, timestamp, TS_offset, time) (std::string(":") + client + " 391 " + server + " " + timestamp + " " + TS_offset + " :" + time + "\r\n")

// 400
# define ERR_UNKNOWNERROR(client, command, info) (std::string(":") + client + " 400 " + command + " :" + info + "\r\n")

// 401
# define ERR_NOSUCHNICK(client, nickname) (std::string(":") + client + " 401 " + nickname + " :No such nick/channel\r\n")

// 402
# define ERR_NOSUCHSERVER(client) (std::string(":") + client + " 402 :No such server\r\n")

// 403
# define ERR_NOSUCHCHANNEL(client, channel) (std::string(":") + client + " 403 " + channel + " :No such channel\r\n")

// 404
# define ERR_CANNOTSENDTOCHAN(client, channel) (std::string(":") + client + " 404 " + channel + " :Cannot send to channel\r\n")

// 405
# define ERR_TOOMANYCHANNELS(client, channel) (std::string(":")  + client + " 405 " + channel + " :You have joined too many channels\r\n")

// 406
# define ERR_WASNOSUCHNICK(client) (std::string(":") + client + " 406 :There was no such nickname\r\n")

// 407
# define ERR_TOOMANYTARGETS(client) (std::string(":") + client + " 407 :You selected too many targets\r\n")

// 409
# define ERR_NOORIGIN(client) (std::string(":") + client + " 409 :No origin specified\r\n")

// 411
# define ERR_NORECIPIENT(client, command) (std::string(":") + client + " 411 :No recipient given " + command + "\r\n")

// 412
# define ERR_NOTEXTTOSEND(client) (std::string(":") + client + " 412 :No text to send\r\n")

// 417
# define ERR_INPUTTOOLONG(client) (std::string(":") + client + " 417 :Input line was too long\r\n")

// 421
# define ERR_UNKNOWNCOMMAND(client, command) (std::string(":") + client + " 421 " + command + " :Unknown command\r\n")

// 422
# define ERR_NOMOTD(client) (std::string(":") + client + " 422 :MOTD File is missing\r\n")

// 431
# define ERR_NONICKNAMEGIVEN(client) (std::string(":") + client + " 431 :No nickname given\r\n")

// 432
# define ERR_ERRONEUSNICKNAME(client, nick) (std::string(":") + client + " 432 " + nick + " :Erroneus nickname\r\n")

// 433
# define ERR_NICKNAMEINUSE(client, nick) (std::string(":") + client + " 433 " + nick + " :Nickname is already in use\r\n")

// 436
# define ERR_NICKCOLLISION(client, nick, user, host) (std::string(":") + client + " 436 " + nick + " :Nickname collision KILL from " + user + "@" + host + "\r\n")

// 441
# define ERR_USERNOTINCHANNEL(client, nick, channel) (std::string(":") + client + " 441 " + nick + " " + channel + " :They aren't on that channel\r\n")

// 442
# define ERR_NOTONCHANNEL(client, channel) (std::string(":") + client + " 442 " + channel + " :You're not on that channel\r\n")

// 443
# define ERR_USERONCHANNEL(client, nick, channel) (std::string(":") + client + " 443 " + nick + " " + channel + " :is already on channel\r\n")

// 451
# define ERR_NOTREGISTERED(client) (std::string(":") + client + " 451 :You have not registered\r\n")

// 461
# define ERR_NEEDMOREPARAMS(client, command) (std::string(":") + client + " 461 " + command + " :Not enough parameters\r\n")

// 462
# define ERR_ALREADYREGISTERED(client) (std::string(":")  + client + " 462 :You may not reregister\r\n")

// 464
# define ERR_PASSWDMISMATCH(client) (std::string(":") + client + " 464 :Password incorrect\r\n")

// 465
# define ERR_YOUREBANNEDCREEP(client) (std::string(":") + client + " 465 :You are banned from this server\r\n")

// 471
# define ERR_CHANNELISFULL(client, channel) (std::string(":") + client + " 471 " + channel + " :Cannot join channel (+l)\r\n")

// 472
# define ERR_UNKNOWNMODE(client, modechar) (std::string(":")  + client + " 472 " + modechar + " :is unknown mode char to me\r\n")

// 473
# define ERR_INVITEONLYCHAN(client, channel) (std::string(":")  + client + " 473 " + channel + " :Cannot join channel (+i)\r\n")

// 474
# define ERR_BANNEDFROMCHAN(client, channel) (std::string(":") + client + " 474 " + channel + " :Cannot join channel (+b)\r\n")

// 475
# define ERR_BADCHANNELKEY(client, channel) (std::string(":")  + client + " 475 " + channel + " :Cannot join channel (+k)\r\n")

// 476
# define ERR_BADCHANMASK(channel) (std::string(":") + channel + " 476 :Bad Channel Mask\r\n")

// 481
# define ERR_NOPRIVILEGES(client) (std::string(":") + client + " 481 :Permission Denied- You're not an IRC operator\r\n")

// 482
# define ERR_CHANPRIVSNEEDED(client, channel) (std::string(":")  + client + " 482 " + channel + " :You're not channel operator\r\n")

// 483
# define ERR_CANTKILLSERVER(client) (std::string(":") + client + " 483 : You can't kill a server\r\n")

// 491
# define ERR_NOOPERHOST(client) (std::string(":") + client + " 491 :No O-lines for your host\r\n")

// 501
# define ERR_UMODEUNKNOWNFLAG(client) (std::string(":") + client + " 501 :Unknown MODE flag\r\n")

// 502
# define ERR_USERDONTMATCH(client) (std::string(":") + client + " 502 :Can't change mode for other users\r\n")

// 524
# define ERR_HELPNOTFOUND(client, subject) (std::string(":") + client + " 524 " + subject + " :No help available on this topic\r\n")

// 525
# define ERR_INVALIDKEY(client, target_chan) (std::string(":") + client + " 525 " + target_chan + " :Key is not well-formed\r\n")

// 670
# define RPL_STARTTLS(client) (std::string(":") + client + " 670 :STARTTLS successful, proceed with TLS handshake\r\n")

// 671
# define RPL_WHOISSECURE(client, nick) (std::string(":") + client + " 671 " + nick + " :is using a secure connection\r\n")

// 691
# define ERR_STARTTLS(client) (std::string(":") + client + " 691 :STARTTLS failed (Wrong moon phase)\r\n")

// 696
# define RPL_INVALIDMODEPARAM(client, target, mode_char, parameter, description) (std::string(":")  + client + " 696 " + target + " " + mode_char + " " + parameter + " :" + description + "\r\n")

// 704
# define RPL_HELPSTART(client, subject, line) (std::string(":") + client + " 704 " + subject + " :" + line + "\r\n")

// 705
# define RPL_HELPTXT(client, subject, line) (std::string(":") + client + " 705 " + subject + " :" + line + "\r\n")

// 706
# define RPL_ENDOFHELP(client, subject, line) (std::string(":") + client + " 706 " + subject + " :" + line + "\r\n")

// 723
# define RPL_NOPRIVS(client, priv) (std::string(":") + client + " 723 " + priv + " :Insufficient oper privileges\r\n")

// 900
# define RPL_LOGGEDIN(client, nick, user, host, account, username) (std::string(":") + client + " 900 " + nick + "!" + user + "@" + host + " " + account + " :You are now logged in as " + username + "\r\n")

// 901
# define RPL_LOGGEDOUT(client, nick, user, host) (std::string(":") + client + " 901 " + nick + "!" + user + "@" + host + " :You are now logged out\r\n")

// 902
# define ERR_NICKLOCKED(client) (std::string(":") + client + " 902 :You must use a nick assigned to you\r\n")

// 903
# define RPL_SASLSUCCESS(client) (std::string(":") + client + " 903 : SASL authentication successful\r\n")

// 904
# define ERR_SASLFAIL(client) (std::string(":") + client + " 904 :SASL authentication failed\r\n")

// 905
# define ERR_SASLTOOLONG(client) (std::string(":") + client + " 905 :SASL message too long\r\n")

// 906
# define ERR_SASLABORTED(client) (std::string(":") + client + " 906 :SASL authentication aborted\r\n")

// 907
# define ERR_SASLALREADY(client) (std::string(":") + client + " 907 : You have already authenticated using SASL\r\n")

// 908
# define RPL_SASLMECHS(client, mechanisms) (std::string(":") + client + " 908 " + mechanisms + " :are available SASL mechanisms\r\n")

#endif
