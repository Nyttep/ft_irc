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
		std::map<int, User>	_users;
		Channel();
	public :
		Channel(std::string newName);
		Channel(const Channel& toCopy);
		~Channel();
		Channel&	operator=(const Channel& rhs);
		std::string	getName();
		User&		getUser(int	key);
		bool		addUser(int key, User value);
		bool		isInChannel(int key);
};

#endif