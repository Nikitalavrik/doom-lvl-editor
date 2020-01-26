/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_socket.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:21:59 by tbahlai           #+#    #+#             */
/*   Updated: 2019/10/10 15:21:59 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

void	init_for_socket(t_doom *doom)
{
	doom->soc.sock = (int*)malloc(sizeof(int) * doom->max_p);
	doom->soc.addr = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in)
	* doom->max_p);
	doom->soc.sock[0] = socket(AF_INET, SOCK_DGRAM, 0);
	doom->soc.addr[0].sin_family = AF_INET;
	doom->soc.addr[0].sin_port = htons(3333);
	doom->soc.addr[0].sin_addr.s_addr = find_ip();
}

void	errors(int flag)
{
	if (flag == 1)
		ft_putendl("bind\n");
	else if (flag == 2)
		ft_putendl("socket\n");
	else if (flag == 3)
		ft_putendl("save_map_ok\n");
	else if (flag == 4)
		ft_putendl("save_map_error\n");
	else if (flag == 5)
		ft_putendl("load_map_ok\n");
	else if (flag == 6)
		ft_putendl("load_map_error\n");
	else if (flag == 7)
		ft_putendl("open_map_ok\n");
	exit(0);
}

void	set_socket_ip(t_doom *doom, int nb)
{
	doom->soc.sock[nb] = socket(AF_INET, SOCK_DGRAM, 0);
	check_ip(doom, nb);
	if (doom->soc.sock[nb] < 0)
		errors(2);
	fcntl(doom->soc.sock[nb], F_SETFL, O_NONBLOCK);
}

void	close_socket(t_doom *doom)
{
	close(doom->soc.sock[0]);
	errors(1);
}

int		socket_init(t_doom *doom, int flag)
{
	int nb;

	if (flag == 1)
	{
		init_for_socket(doom);
		if (bind(doom->soc.sock[0], (struct sockaddr *)&doom->soc.addr[0],
			sizeof(doom->soc.addr[0])) < 0)
			close_socket(doom);
		nb = 0;
		while (++nb < doom->max_p)
			set_socket_ip(doom, nb);
		fcntl(doom->soc.sock[0], F_SETFL, O_NONBLOCK);
		listen(doom->soc.sock[0], 1);
		nb = 0;
		while (++nb < doom->max_p)
			send(doom->soc.sock[nb], &nb, sizeof(int), 0);
		doom->mult = 1;
	}
	else if (flag == 2)
	{
		add_play(doom);
		doom->mult = 2;
	}
	return (1);
}
