#ifndef RPL_ERR_COMMAND_HPP
# define RPL_ERR_COMMAND_HPP

# define SERVERNAME "ft_irc"
# define VERSION "1.0"

// 001
# define RPL_WELCOME(client, nick) (client + " :Welcome to the " + SERVERNAME + " Network, " + nick + "\r\n")

// 002
# define RPL_YOURHOST(client) (client + " :Your host is " + SERVERNAME + ", running version " + VERSION + "\r\n")

// 003
# define RPL_CREATED(client, datetime) (client + " :This server was created" + datetime + "\r\n")

// 004
# define RPL_MYINFO(client, av_user_mode, av_channel_mode, channel_with_parameter) (client + " " + SERVERNAME + " " + VERSION + " " + av_user_mode + " " + av_channel_mode + " " + channel_with_parameter + "\r\n")

// 005
# define RPL_ISUPPORT(client, tokens) (client + " " + tokens + " :are supported by this server\r\n")

// 010
# define RPL_BOUNCE(client, hostname, port, info) (client + " " + hostname + " " + port + " :" + info + "\r\n")

// 212
# define RPL_STATSCOMMANDS(client, command, count) (client + " " + command + " " + count + "\r\n")

// 219
# define RPL_ENDOFSTATS(client, stats_letter) (client + " " + stats_letter + " :End of /STATS report\r\n")

// 221
# define RPL_UMODEIS(client, user_modes) (client + " " + user_modes + "\r\n")

// 242
# define RPL_STATSUPTIME(client, days, hours, minutes, seconds) (client + " :Server Up " + days + " days " + hours + ":" + minutes + ":" + seconds + "\r\n")

// 251
# define RPL_LUSERCLIENT(client, u, i, s) (client + " :There are " + u + " users and " + i + " invisible on " + s + " servers\r\n")

// 252
# define RPL_USEROP(client, ops) (client + " " + ops + " :operator(s) online\r\n")

// 253
# define RPL_LUSERUNKNOWN(client, connections) (client + " " + connections + " :unknown connection(s)\r\n")

// 254
# define RPL_LUSERCHANNELS(client, channels) (client + " " + channels + " :channels formed\r\n")

// 255
# define RPL_LUSERME(client, c, s) (client + " :I have " + c + " clients and " + s + " servers\r\n")

// 256
# define RPL_ADMINME(client, server) (client + " " + server + " :Administrative info\r\n")

// 257
# define RPL_ADMINLOC1(client, info) (client + " :" + info + "\r\n")

// 258
# define RPL_ADMINLOC2(client, info) (client + " :" + info + "\r\n")

// 259
# define RPL_ADMINEMAIL(client, info) (client + " :" + info + "\r\n")

// 263
# define RPL_TRYAGAIN(client, command) (client + " " + command + " :Please wait a while and try again\r\n")

// 265
# define RPL_LOCALUSERS(client, u, m) (client + " :Current local users " + u + ", max " + m + "\r\n")

// 266
# define RPL_GLOBALUSERS(client, u, m) (client + " :Current global users " + u + ", max " + m + "\r\n")

// 276
# define RPL_WHOISCERTFP(client, nick, fingerprint) (client + " " + nick + " :has client certificate fingerprint " + fingerprint + "\r\n")

// 300
# define RPL_NONE(void) (+ "Undefined format\r\n")

// 301
# define RPL_AWAY(client, nick, message) (client + " " + nick + " :" + message + "\r\n")

// 305
# define RPL_UNAWAY(client) (client + " :You are no longer marked as being away\r\n")

// 306
# define RPL_NOWAWAY(client) (client + " :You have been marked as being away\r\n")

// 307
# define RPL_WHOISREGNICK(client, nick) (client + " " + nick + " :has identified for this nick\r\n")

// 311
# define RPL_WHOISUSER(client, nick, username, host, realname) (client + " " + nick + " " + username + " " + host + " * :" + realname + "\r\n")

// 312
# define RPL_WHOISSERVER(client, nick, server, server_info) (client + " " + nick + " " + server + " :" + server_info + "\r\n")

// 313
# define RPL_WHOISOPERATOR(client, nick) (client + " " + nick + " :is an IRC operator\r\n")

// 314
# define RPL_WHOWASUSER(client, nick, username, host, realname) (client + " " + nick + " " + username + " " + host + " * :" + realname + "\r\n")

// 315
# define RPL_ENDOFWHO(client, mask) (client + " " + mask + " :End of WHO list\r\n")

// 317
# define RPL_WHOISIDLE(client, nick, secs, signon) (client + " " + nick + " " + secs + " " + signon + " : seconds idle, signon time\r\n")

// 318
# define RPL_ENDOFWHOIS(client, nick) (client + " " + nick + " :End of /WHOIS list\r\n")

// 319
# define RPL_WHOISCHANNELS(client, nick, channel) (client + " " + nick + " :" + channel + "\r\n")

// 320
# define RPL_WHOISSPECIAL(client, nick) (client + " " + nick + " :blah blah blah\r\n")

// 321
# define RPL_LISTSTART(client) (client + " Channel :Users Name\r\n")

// 322
# define RPL_LIST(client, channel, client_count, topic) (client + " " + channel + " " +client_count + " :" + topic + "\r\n")

// 323
# define RPL_LISTEND(client) (client + " :End of /LIST\r\n")

// 324
# define RPL_CHANNELMODEIS(client, channel, modestring, mode_arguments) (client + " " + channel + " " + modestring + " " + mode_arguments + "\r\n")

// 329
# define RPL_CREATIONTIME(client, channel, creationtime) (client + " " + channel + " " + creationtime + "\r\n")

// 330
# define RPL_WHOISACCOUNT(client, nick, account) (client + " " + nick + " " + account + " :is logged in as\r\n")

// 331
# define RPL_NOTOPIC(client, channel) (client + " " + channel + " :No topic is set\r\n")

// 332
# define RPL_TOPIC(client, channel, topic) (client + " " + channel + " :" + topic + "\r\n")

// 333
# define RPL_TOPICWHOTIME(client, channel, nick, setat) (client + " " + channel + " " + nick + " " + setat + "\r\n")

// 336
# define RPL_INVITELIST(client, channel) (client + " " + channel + "\r\n")

// 337
# define RPL_ENDOFINVITELIST(client) (client + " :End of /INVITE list\r\n")

// 338
# define RPL_WHOISACTUALLY() /* A faire plus tard, pas compris/

// 341
# define RPL_INVITING(client, nick, channel) (client + " " + nick + " " + channel + "\r\n")

// 346
# define RPL_INVEXLIST(client, channel, mask) (client + " " + channel + " " + mask + "\r\n")

// 347
# define RPL_ENDOFINVEXLIST(client, channel) (client + " " + channel + " :End of channel Invite Exception List\r\n")

// 348
# define RPL_EXCEPTLIST(client, channel, mask) (client + " " + channel + " " + mask + "\r\n")

// 349
# define RPL_ENDOFEXCEPTLIST(client, channel) (client + " " + channel + " :End of channel exception list")

// 351
# define RPL_VERSION(client, comments) (client + " " + VERSION + " " + SERVERNAME + " :" + comments + "\r\n")

// 352
# define RPL_WHOREPLY(client, channel, username, host, server, nick, flags, hopcount, realname) (client + " " + channel + " " + username + " " + host + " " + server + " " + nick + " " + flags + " :" + hopcount + " " + realname + "\r\n")

// 353
# define RPL_NAMEREPLY(client, symbol, channel, nick) (client + " " + symbol + " " + channel + " :" + nick + "\r\n")

// 364
# define RPL_LINKS(client, server, hopcount, server_info) (client + " " + server + " :" + hopcount + " " + server_info + "\r\n")

// 365
# define RPL_ENDOFLINKS(client) (client + " * :End of /LINKS list\r\n")

// 366
# define RPL_ENDOFNAMES(client, channel) (client + " " + channel + " :End of /NAMES list\r\n")

// 367
# define RPL_BANLIST(client, channel, mask) (client + " " + channel + " " + mask + "\r\n")

// 368
# define RPL_ENDOFBANLIST(client, channel) (client + " " + channel + " :End of ban list\r\n")

// 369
# define RPL_ENDOFWHOWAS(client, nick) (client + " " + nick + " :End of WHOWAS\r\n")

// 371
# define RPL_INFO(client, string) (client + " :" + string + "\r\n")

// 372
# define RPL_MOTD(client, motd) (client + " :" + motd + "\r\n")

// 374
# define RPL_ENDOFINFO(client) (client + " :End of INFO list\r\n")

// 375
# define RPL_MODSTART(client, server) (client + " :- " + server + " Message of the day - \r\n")

// 376
# define RPL_ENDOFMOTD(client) (client + " : End of /MOTD command.\r\n")

// 378
# define RPL_WHOISHOST(client, nick) (client + " " + nick + " :is connecting from *@localhost 127.0.0.1\r\n")

// 379
# define RPL_WHOISMODES(client, nick) (client + " " + nick + " : is using modes +ailosw\r\n")

// 381
# define RPL_YOUREOPER(client) (client + " :You are now an IRC operator\r\n")

// 382
# define RPL_REHASHING(client, config_files) (client + " " + config_files + " :Rehashing\r\n")

// 391
# define RPL_TIME(client, server, timestamp, TS_offset, time) (client + " " + server + " " + timestamp + " " + TS_offset + " :" + time + "\r\n")

// 400
# define ERR_UNKNOWNERROR(client, command, subcommand, info) (client + " " + command + " " + subcommand + " :" + info + "\r\n")

// 401
# define ERR_NOSUCHNICK(client, nickname) (client + " " + nickname + " :No such nick/channel\r\n")

// 402
# define ERR_NOSUCHSERVER(client) (client SERVERNAME + " :No such server\r\n")

// 403
# define ERR_NOSUCHCHANNEL(client, channel) (client + " " + channel + " :No such channel\r\n")

// 404
# define ERR_CANNOTSENDTOCHAN(client, channel) (client + " " + channel + " :Cannot send to channel\r\n")

// 405
# define ERR_TOOMANYCHANNELS(client, channel) (client + " " + channel + " :You have joined too many channels\r\n")

// 406
# define ERR_WASNOSUCHNICK(client) (client + " :There was no such nickname\r\n")

// 409
# define ERR_NOORIGIN(client) (client + " :No origin specified\r\n")

// 411
# define ERR_NORECIPIENT(client, command) (client + " :No recipient given " + command + "\r\n")

// 412
# define ERR_NOTEXTTOSEND(client) (client + " :No text to send\r\n")

// 417
# define ERR_INPUTTOOLONG(client) (client + " :Input line was too long\r\n")

// 421
# define ERR_UNKNOWNCOMMAND(client, command) (client + " " + command + " :Unknown command\r\n")

// 422
# define ERR_NOMOTD(client) (client + " :MOTD File is missing\r\n")

// 431
# define ERR_NONICKNAMEGIVEN(client) (client + " :No nickname given\r\n")

// 432
# define ERR_ERRONEUSNICKNAME(client, nick) (client + " " + nick + " :Erroneus nickname\r\n")

// 433
# define ERR_NICKNAMEINUSE(client, nick) (client + " " + nick + " :Nickname is already in use\r\n")

// 436
# define ERR_NICKCOLLISION(client, nick, user, host) (client + " " + nick + " :Nickname collision KILL from " + user + "@" + host + "\r\n")

// 441
# define ERR_USERNOTINCHANNEL(client, nick, channel) (client + " " + nick + " " + channel + " :They aren't on that channel\r\n")

// 442
# define ERR_NOTONCHANNEL(client, channel) (client + " " + channel + " :You're not on that channel\r\n")

// 443
# define ERR_USERONCHANNEL(client, nick, channel) (client + " " + nick + " " + channel + " :is already on channel\r\n")

// 451
# define ERR_NOTREGISTERED(client) (client + " :You have not registered\r\n")

// 461
# define ERR_NEEDMOREPARAMS(client, command) (client + " " + command + " :Not enough parameters\r\n")

// 462
# define ERR_ALREADYREGISTERED(client) (client + " :You may not reregister\r\n")

// 464
# define ERR_PASSWDMISMATCH(client) (client + " :Password incorrect\r\n")

// 465
# define ERR_YOUREBANNEDCREEP(client) (client + " :You are banned from this server\r\n")

// 471
# define ERR_CHANNELISFULL(client, channel) (client + " " + channel + " :Cannot join channel (+l)\r\n")

// 472
# define ERR_UNKNOWNMODE(client, modechar) (client + " " + modechar + " :is unknown mode char to me\r\n")

// 473
# define ERR_INVITEONLYCHAN(client, channel) (client + " " + channel + " :Cannot join channel (+i)\r\n")

// 474
# define ERR_BANNEDFROMCHAN(client, channel) (client + " " + channel + " :Cannot join channel (+b)\r\n")

// 475
# define ERR_BADCHANNELKEY(client, channel) (client + " " + channel + " :Cannot join channel (+k)\r\n")

// 476
# define ERR_BADCHANMASK(channel) (channel + " :Bad Channel Mask\r\n")

// 481
# define ERR_NOPRIVILEGES(client) (client + " :Permission Denied- You're not an IRC operator\r\n")

// 482
# define ERR_CHANPRIVSNEEDED(client, channel) (client + " " + channel + " :You're not channel operator\r\n")

// 483
# define ERR_CANTKILLSERVER(client) (client + " : You can't kill a server\r\n")

// 491
# define ERR_NOOPERHOST(client) (client + " :No O-lines for your host\r\n")

// 501
# define ERR_UMODEUNKNOWNFLAG(client) (client + " :Unknown MODE flag\r\n")

// 502
# define ERR_USERDONTMATCH(client) (client + " :Can't change mode for other users\r\n")

// 524
# define ERR_HELPNOTFOUND(client, subject) (client + " " + subject + " :No help available on this topic\r\n")

// 525
# define ERR_INVALIDKEY(client, target_chan) (client + " " + target_chan + " :Key is not well-formed\r\n")

// 670
# define RPL_STARTTLS(client) (client + " :STARTTLS successful, proceed with TLS handshake\r\n")

// 671
# define RPL_WHOISSECURE(client, nick) (client + " " + nick + " :is using a secure connection\r\n")

// 691
# define RPL_STARTTLS(client) (client + " :STARTTLS failed (Wrong moon phase)\r\n")

// 696
# define RPL_INVALIDMODEPARAM(client, target, mode_char, parameter, description) (client + " " + target + " " + mode_char + " " + parameter + " :" + description + "\r\n")

// 704
# define RPL_HELPSTART(client, subject, line) (client + " " + subject + " :" + line + "\r\n")

// 705
# define RPL_HELPTXT(client, subject, line) (client + " " + subject + " :" + line + "\r\n")

// 706
# define RPL_ENDOFHELP(client, subject, line) (client + " " + subject + " :" + line + "\r\n")

// 723
# define RPL_NOPRIVS(client, priv) (client + " " + priv + " :Insufficient oper privileges\r\n")

// 900
# define RPL_LOGGEDIN(client, nick, user, host, account, username) (client + " " + nick + "!" + user + "@" + host + " " + account + " :You are now logged in as " + username + "\r\n")

// 901
# define RPL_LOGGEDOUT(client, nick, user, host) (client + " " + nick + "!" + user + "@" + host + " :You are now logged out\r\n")

// 902
# define ERR_NICKLOCKED(client) (client + " :You must use a nick assigned to you\r\n")

// 903
# define RPL_SASLSUCCESS(client) (client + ": SASL authentication successful\r\n")

// 904
# define ERR_SASLFAIL(client) (client + " :SASL authentication failed\r\n")

// 905
# define ERR_SASLTOOLONG(client) (client + " :SASL message too long\r\n")

// 906
# define ERR_SASLABORTED(client) (client + " :SASL authentication aborted\r\n")

// 907
# define ERR_SASLALREADY(client) (client + " : You have already authenticated using SASL\r\n")

// 908
# define RPL_SASLMECHS(client, mechanisms) (client + " " + mechanisms + " :are available SASL mechanisms\r\n")

#endif