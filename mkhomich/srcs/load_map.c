/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:30:28 by mkhomich          #+#    #+#             */
/*   Updated: 2020/02/16 16:38:20 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

void	l_map(t_doom *doom, int fd, int nb)
{
	int n;
	int c;

	if (doom->sec[nb].max_sp)
	{
		n = -1;
		doom->sec[nb].sp =
		(t_tochsp*)malloc(sizeof(t_tochsp) * doom->sec[nb].max_sp);
		while (++n < doom->sec[nb].max_sp)
			read(fd, &doom->sec[nb].sp[n], sizeof(t_tochsp));
	}
	if (doom->sec[nb].max_toch)
	{
		c = -1;
		doom->sec[nb].pts = (int*)malloc(sizeof(int) * doom->sec[nb].max_toch);
		while (++c < doom->sec[nb].max_toch)
			read(fd, &doom->sec[nb].pts[c], sizeof(int));
	}
}

void	load_map(t_doom *doom, char *filename)
{
	int nb;
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd > 0)
	{
		// errors(7);
		nb = -1;
		read(fd, &doom->max_t, sizeof(int));
		doom->toch = (t_toch*)malloc(sizeof(t_toch) * doom->max_t);
		while (++nb < doom->max_t)
			read(fd, &doom->toch[nb], sizeof(t_toch));
		nb = -1;
		read(fd, &doom->max_s, sizeof(int));
		doom->sec = (t_sec*)malloc(sizeof(t_sec) * doom->max_s);
		while (++nb < doom->max_s)
		{
			read(fd, &doom->sec[nb], sizeof(t_sec));
			l_map(doom, fd, nb);
		}
		close(fd);
		// errors(5);
	}
}
