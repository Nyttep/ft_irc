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

class User
{
	private :
		std::string		_nName; // nickname
		std::string 	_uName; // username
		std::string 	_rName; // realname
		std::string		_msg;
		std::string		_buff;
		std::string		_extra;
		bool			_isOP;
		bool			_isLogged;
	public :
		User();
		User(std::string newNName, std::string newUName);
		User(std::string newNName, std::string newUName, std::string newRName);
		User(const User& toCopy);
		~User();
		User&		operator=(const User& rhs);
		std::string	getNName();
		void		setNName(std::string newNName);
		std::string	getUName();
		void		setUName(std::string newUName);
		std::string	getRName();
		void		setRName(std::string newRName);
		std::string	getBuff();
		std::string	getMsg();
		void		clearMsg();
		void		clearBuff();
		bool		isOP();
		bool		isLogged();
		void		logIn();
		void		logOut();
		void		makeOP();
		void		removeOP();
		bool		formatRecvData();
};

#endif