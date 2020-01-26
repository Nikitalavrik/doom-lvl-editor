/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_rec_net.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:38:15 by tbahlai           #+#    #+#             */
/*   Updated: 2019/10/10 14:38:16 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

void	send_net(t_doom *doom)
{
	int nb;
	int port;

	port = 1;
	while (doom->mult == 1 && port < doom->max_p)
	{
		nb = 0;
		while (nb < doom->max_p)
		{
			send(doom->soc.sock[port], &doom->play[nb],
				sizeof(t_play), 0);
			nb++;
		}
		port++;
	}
	if (doom->mult == 2)
		send(doom->soc.sock[0], &doom->play[doom->n_play],
			sizeof(t_play), 0);
}

void	rec_net(t_doom *doom)
{
	t_play	buf;

	if (doom->mult == 1)
		while (recv(doom->soc.sock[0], &buf, sizeof(t_play), 0) > 0)
			if (buf.id != doom->n_play)
				doom->play[buf.id] = buf;
	if (doom->mult == 2)
	{
		while (recv(doom->soc.sock[doom->n_play], &buf, sizeof(t_play), 0) > 0)
			if (buf.id != doom->n_play)
				doom->play[buf.id] = buf;
	}
	send_net(doom);
}
