/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:00:46 by nlaerema          #+#    #+#             */
/*   Updated: 2024/03/21 01:19:49 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <queue>
#include <algorithm>
#include <sys/epoll.h>
#include "kdolib/kdolib.hpp"
#include "Config.hpp"
#include "IrcChannel.hpp"
#include "IrcServer.hpp"
#include "IrcClient.hpp"
#include "IrcMessage.hpp"
#include "commands/Nick.hpp"
#include "commands/Pass.hpp"
#include "commands/User.hpp"
#include "commands/Cap.hpp"
#include "commands/Ping.hpp"
#include "commands/Lusers.hpp"
#include "commands/Motd.hpp"
#include "commands/Join.hpp"
#include "commands/Mode.hpp"
#include "commands/Privmsg.hpp"
#include "commands/Quit.hpp"

#define IRC_NAME "ircserv"
