/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 11:56:55 by pdubois           #+#    #+#             */
/*   Updated: 2023/10/02 15:28:28 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	handleSig(int sigNum, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	g_sig = sigNum;
}

int	signals(struct sigaction &sa)
{
	std::memset(&sa, 0, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handleSig;
	if (sigemptyset(&(sa.sa_mask)) != 0)
	{
		std::cerr << "Error: sigemptyset: unexpected error\n";
		return (1);
	}
	if (sigaction(SIGINT, &sa, NULL) < 0)
	{
		std::perror("Error: sigaction: ");
		return (1);
	}
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
	{
		std::perror("Error: sigaction: ");
		return (1);
	}
	return (0);
}