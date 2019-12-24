/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 12:21:26 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/23 18:22:58 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_gnl	*ckeck_fd(const int fd, t_gnl **list)
{
	t_gnl *node;

	node = *list;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	CHECKMEM(node = (t_gnl *)malloc(sizeof(t_gnl)));
	node->fd = fd;
	node->buf = NULL;
	node->next = *list;
	*list = node;
	return (node);
}

static char		*find_line(t_gnl *temp, char buf[BUFF_SIZE + 1])
{
	char	*old_str;
	char	*main_str;
	char	*all_buf;
	char	*sub;
	size_t	size;

	main_str = ft_strnew(0);
	while (!(all_buf = ft_strchr(buf, '\n')))
	{
		SWAP(old_str, main_str, ft_strjoin(main_str, buf));
		if (!(size = read(temp->fd, buf, BUFF_SIZE)))
		{
			ft_strdel(&(temp->buf));
			return (main_str);
		}
		buf[size] = '\0';
	}
	sub = ft_strsub(buf, 0, N_INDEX);
	SWAP(old_str, main_str, ft_strjoin(main_str, sub));
	free(sub);
	SWAP(old_str, temp->buf, ft_strsub(buf, N_INDEX + 1, BUFF_SIZE - N_INDEX));
	return (main_str);
}

int				get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static t_gnl	*list = NULL;
	t_gnl			*temp;
	size_t			size;

	if (fd < 0 || (read(fd, NULL, 0) == -1) || !line || BUFF_SIZE < 1)
		return (-1);
	temp = ckeck_fd(fd, &list);
	if (temp->buf && (ft_strlen(temp->buf)))
		ft_strcpy(buf, temp->buf);
	else
	{
		if (!(size = read(fd, buf, BUFF_SIZE)))
		{
			ft_strdel(&(temp->buf));
			ZERO;
		}
		buf[size] = '\0';
	}
	*line = find_line(temp, buf);
	YO;
}
