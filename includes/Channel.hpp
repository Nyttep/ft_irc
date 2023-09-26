/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:32:26 by pdubois           #+#    #+#             */
/*   Updated: 2023/09/20 17:32:26 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

class Channel //date creation ?
{
	private :
		std::string			_name;
		std::vector<User>	_operators;
		std::vector<User>	_users;
		std::vector<User>	_invite;

		std::string			_key;
		std::string			_topic;
		size_t				_limit;

		bool				_i;
		bool				_t;
		bool				_k;
		bool				_o;
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
};

#endif