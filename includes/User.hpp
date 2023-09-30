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

class User
{
	private :
		int						_fd;
		int						_port;

		std::string				_nName; // nickname
		std::string 			_uName; // username
		std::string 			_rName; // realname
		std::string				_hName; // hostname

		std::vector<Channel>	_lChannel; // LocalChan
		std::vector<Channel>	_gChannel; // GeneralChan

		bool					_pass;
		bool					_registered;

		std::string			_msg;
		std::string			_extra;
	public :
		User();
		User(const User& toCopy);

	public :
		User(std::string newNName, std::string newUName);
		User(std::string newNName, std::string newUName, std::string newRName);
		~User();
		User&				operator=(const User& rhs);
		std::string			getNName();
		void				setNName(std::string newNName);
		std::string			getUName();
		void				setUName(std::string newUName);
		std::string			getRName();
		void				setRName(std::string newRName);
		std::string			getMsg();
		void				clearMsg();
		bool				isOP();
		bool				isLogged();
		void				logIn();
		void				logOut();
		void				makeOP();
		void				removeOP();
		bool				formatRecvData(std::vector<char>& buff);
};

#endif