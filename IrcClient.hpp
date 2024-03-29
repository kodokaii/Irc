/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:06:54 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/27 11:30:19 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"

class IrcClient: public SocketTcpClient
{
	private:
		Config				&config;
		bool				registered;
		bool				hasGivenPassword;
		std::string			nick;
		std::string			username;
		std::string			realname;
		std::string			modes;

		std::map<std::string, IrcChannel*>	channels;

	public:
							IrcClient(Config &config);
							IrcClient(Config &config, int socketConnected);
							~IrcClient(void);
		bool				isRegistered(void) const;
		void				sendRaw(std::string msg) const;
		void				sendRpl(int rpl, std::string msg) const;
		void				hasRegistered(IrcServer &server);
		void				setHasGivenPassword(void);
		bool				getHasGivenPassword(void) const;
		void				setNick(const std::string &nick);
		void				setIdentity(const std::string &username, const std::string &realname);
		const std::string	&getUsername() const;
		const std::string	&getRealname() const;
		const std::string	&getNick() const;
		const std::string	&getModes() const;
		Config				&getConfig(void);

		const std::map<std::string, IrcChannel*>	&getChannels() const;
		void									addChannel(IrcChannel *channel);
		bool									isInChannel(IrcChannel *channel);
};
