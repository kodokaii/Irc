/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cap.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:35:48 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/18 01:03:46 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IrcMessage.hpp"
#include "IrcServer.hpp"

class Cap
{
	public:
		static void	handle(IrcServer &server, IrcMessage &msg);
};