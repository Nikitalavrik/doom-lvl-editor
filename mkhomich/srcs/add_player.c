/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:49:11 by tbahlai           #+#    #+#             */
/*   Updated: 2019/10/10 15:49:12 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

void	find_server(t_doom *doom)
{
	int n;
	int nb;
	int size;

	nb = 0;
	doom->play = (t_play*)malloc(sizeof(t_play) * (doom->max_p + 1));
	doom->soc.sock = (int*)malloc(sizeof(int) * doom->max_p);
	doom->soc.addr = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in)
	* doom->max_p);
	n = -1;
	while (++n < doom->max_p)
	{
		nb = 0;
		size = 0;
		while (recvfrom(doom->soc.skt, &size,
		sizeof(int), 0, NULL, NULL) <= 0 && nb < 10000)
			nb++;
		nb = 0;
		while (recvfrom(doom->soc.skt, &doom->play[size],
		sizeof(doom->play[size]), 0, NULL, NULL) <= 0 && nb < 10000)
			nb++;
	}
	close(doom->soc.skt);
	doom->soc.skt = socket(AF_INET, SOCK_DGRAM, 0);
	fcntl(doom->soc.skt, F_SETFL, O_NONBLOCK);
}

void	check_server(t_doom *doom)
{
	int nb;

	nb = 0;
	while (recvfrom(doom->soc.skt, &doom->max_p,
	sizeof(int), 0, NULL, NULL) <= 0 && nb < 10000)
		nb++;
	nb = 0;
	while (recvfrom(doom->soc.skt, &doom->n_play,
	sizeof(int), 0, NULL, NULL) <= 0 && nb < 10000)
		nb++;
	find_server(doom);
	if (bind(doom->soc.skt, (struct sockaddr *)&doom->soc.ads,
	sizeof(doom->soc.ads)) < 0)
	{
		printf("bind\n");
		close(doom->soc.skt);
		exit(0);
	}
	doom->soc.sock[0] = doom->soc.lstn;
	doom->soc.addr[0] = doom->soc.adl;
	doom->soc.sock[doom->n_play] = doom->soc.skt;
	doom->soc.addr[doom->n_play] = doom->soc.ads;
}

void	init_addrls(t_doom *doom, int fl)
{
	if (fl == 1)
	{
		doom->soc.ads.sin_family = AF_INET;
		doom->soc.ads.sin_port = htons(5555);
		doom->soc.ads.sin_addr.s_addr = find_ip();
		if (bind(doom->soc.skt, (struct sockaddr *)&doom->soc.ads,
		sizeof(doom->soc.ads)) < 0)
			exit(0);
		fcntl(doom->soc.skt, F_SETFL, O_NONBLOCK);
		fcntl(doom->soc.lstn, F_SETFL, O_NONBLOCK);
	}
	else
	{
		doom->soc.nb = 0;
		doom->soc.adl.sin_family = AF_INET;
		doom->soc.adl.sin_port = htons(3333);
		doom->soc.adl.sin_addr.s_addr =
		calc_ip(10, 111, doom->soc.r, doom->soc.m);
		connect(doom->soc.lstn, (struct sockaddr *)&doom->soc.adl,
		sizeof(doom->soc.adl));
		send(doom->soc.lstn, &doom->soc.ads, sizeof(struct sockaddr_in), 0);
	}
}

void	add_play(t_doom *doom)
{
	doom->soc.skt = socket(AF_INET, SOCK_DGRAM, 0);
	doom->soc.lstn = socket(AF_INET, SOCK_DGRAM, 0);
	init_addrls(doom, 1);
	doom->soc.size = 0;
	while (++doom->soc.r <= 12)
	{
		doom->soc.m = 0;
		while (++doom->soc.m <= 16)
		{
			init_addrls(doom, 2);
			while ((doom->soc.size = recvfrom(doom->soc.skt, &doom->soc.ads,
			sizeof(struct sockaddr_in), 0, NULL, NULL)) <= 0
			&& doom->soc.nb < 10000)
				doom->soc.nb++;
			if (doom->soc.size > 0)
			{
				check_server(doom);
				while (1)
					if (recvfrom(doom->soc.skt, &doom->soc.size,
					sizeof(int), 0, NULL, NULL) > 0)
						return ;
			}
		}
	}
	exit(0);
}
