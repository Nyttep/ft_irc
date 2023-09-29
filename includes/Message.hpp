/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:17:22 by pdubois           #+#    #+#             */
/*   Updated: 2023/09/27 18:31:00 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include "irc.hpp"

class Message
{
	private :
		Message(const Message& toCopy);
	public :
		std::string					raw;
		std::string					cmd;
		std::vector<std::string>	args;
		Message();
		~Message();
		Message&				operator=(const Message& rhs);
};

#endif