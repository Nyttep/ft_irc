/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:10:52 by pdubois           #+#    #+#             */
/*   Updated: 2023/09/20 18:10:52 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include "irc.hpp"

class Channel;
class Command;
class Server;

class User
{
	private :
		int						_fd;
		int						_port;

		std::string				_nName; // nickname
		std::string 			_uName; // username
		std::string 			_rName; // realname
		std::string				_hName; // hostname

		std::vector<Channel*>	_lChannel; // LocalChan
		std::vector<Channel*>	_gChannel; // GeneralChan

		bool					_pass;
		bool					_registered;

		std::string				_msg;
		std::string				_extra;

		User();

	public :
		User(const User& toCopy);
		User(int newFD);
		~User();
		User&				operator=(const User& rhs);
		std::string			getNName();
		void				setNName(std::string newNName);
		std::string			getUName();
		void				setUName(std::string newUName);
		std::string			getRName();
		void				setRName(std::string newRName);
		void				setHName(std::string newHName);
		std::string			getHName();
		std::string			getMsg();
		int					getFD();
		void				clearMsg();
		bool				isLogged();
		void				logIn();
		void				logOut();
		bool				formatRecvData(std::vector<char>& buff);
		bool				getPass();
		void				setPass(bool value);
		bool				getRegistered();
		void				setRegistered(bool value);
		bool				maxChannel(std::string channel);
		void				joinChan(Channel* chan);
		void				leaveAllChanPART(Command &command);
		void				quitChan(Channel& chan);
		void				sendToAllChan(std::string message);
		void				leaveAllChan();
};

#endif