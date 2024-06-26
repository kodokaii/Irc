/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:09:44 by cgodard           #+#    #+#             */
/*   Updated: 2024/04/06 02:08:49 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

DEFINE_CMD(Quit, {
	IrcClient		*client = msg.getClient();
	std::string		reason;

	if (N_PARAMS() > 0)
		reason = PARAM(0);
	quit(client, reason);
	server.disconnectClient(client->getFd());
})
