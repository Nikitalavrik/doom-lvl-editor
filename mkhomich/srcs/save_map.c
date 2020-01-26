/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:08:55 by mkhomich          #+#    #+#             */
/*   Updated: 2019/11/25 11:02:31 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

void	check_file(t_doom *doom, int fd, int nb)
{
	int n;
	int c;

	// printf("max_sp = %i\n", doom->sec[nb].max_sp);
	if (doom->sec[nb].max_sp)
	{
		n = -1;
		while (++n < doom->sec[nb].max_sp)
			write(fd, &doom->sec[nb].sp[n], sizeof(t_tochsp));
	}
	// printf("max_toch = %i\n", doom->sec[nb].max_toch);
	if (doom->sec[nb].max_toch)
	{
		c = -1;
		while (++c < doom->sec[nb].max_toch)
			write(fd, &doom->sec[nb].pts[c], sizeof(int));
	}
}

void	save_map(t_doom *doom, char *filename)
{
	int nb;
	int fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd > 0)
	{
		nb = -1;
		write(fd, &doom->max_t, sizeof(int));
		while (++nb < doom->max_t)
			write(fd, &doom->toch[nb], sizeof(t_toch));
		nb = -1;
		write(fd, &doom->max_s, sizeof(int));
		// printf("1\n");
		while (++nb < doom->max_s)
		{
			write(fd, &doom->sec[nb], sizeof(t_sec));
			check_file(doom, fd, nb);
			// printf("nb = %i\n", nb);
		}
		// printf("2\n");
		close(fd);
		// errors(3);
	}
	else
		errors(4);
}

