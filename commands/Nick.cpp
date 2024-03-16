/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:09:44 by cgodard           #+#    #+#             */
/*   Updated: 2024/03/15 18:29:21 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/Nick.hpp"

		Nick::Nick()
{
}

		Nick::~Nick()
{
}

void	Nick::handle(IrcMessage &msg)
{
	if (msg.getParams().size() == 0)
	{
		std::cout << "missing params" << std::endl;
	}
}
