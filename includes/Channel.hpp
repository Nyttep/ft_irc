/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:32:26 by pdubois           #+#    #+#             */
/*   Updated: 2023/09/20 17:32:26 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "irc.hpp"

class User;

class Channel //date creation ?
{
	private :
		std::string			_name;
		std::vector<User*>	_operators;
		std::vector<User*>	_users;
		std::vector<User*>	_invite;

		std::string			_key;
		std::string			_topic;
		size_t				_limit;

		bool				_i;
		bool				_t;
		bool				_k;
		bool				_l;

		Channel();
		Channel(const Channel& toCopy);

	public :
		Channel(std::string newName);
		~Channel();
		Channel&	operator=(const Channel& rhs);

		std::string	getName();
		User&		getUser(int	key);
		bool		addUser(int key, User value);
		bool		isInChannel(int key);
		bool		onChannel(User client);
		void		addOperator(User client);
		void		removeOperator(User client);
		bool		isOperator(User client);
		void		addInvite(User client);
		void		removeInvite(User client);
		bool		isInvite(User client);

		void		setKey(std::string key);
		std::string	getKey();
		void		setTopic(std::string topic);
		std::string	getTopic();
		void		setLimit(size_t limit);
		size_t		getLimit();

		void		setI(bool value);
		bool		getI();
		void		setT(bool value);
		bool		getT();
		void		setK(bool value);
		bool		getK();
		void		setL(bool value);
		bool		getL();

		bool		maxUser();
		size_t		nbUser();
		void		sendToChan(std::string message, std::string prefix);
		void		sendUsersList(User &user);
};

#endif