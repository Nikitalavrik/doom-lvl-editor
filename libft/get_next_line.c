/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 15:56:34 by nlavrine          #+#    #+#             */
/*   Updated: 2018/10/28 15:56:36 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strfromcpy(char *s1, char *s2, size_t from)
{
	char	*ret;
	size_t	len;

	len = ft_strlen(s2 + from);
	ret = ft_memmove(s1, s2 + from, len);
	ret[len] = '\0';
	return (ret);
}

void	check_tmp(char **line, char *tmp, size_t *size, int ret)
{
	*size += (!ret) ? ft_strlenc(tmp, '\n') : (size_t)ret;
	*line = ft_realloc(*line, ft_strlen(*line), *size);
	*line = ft_strcat(*line, tmp);
}

int		get_find_and_clear(char **tmp, int finded, int ret)
{
	ft_bzero(*tmp + ret, BUFF_SIZE - ret);
	finded = ft_get_index(*tmp, '\n');
	finded = (!finded) ? ret + 1 : finded;
	return (finded);
}

int		get_next_line(const int fd, char **line)
{
	static	char	*tmp[OPEN_MAX + 1];
	size_t			size;
	int				finded;
	int				ret;

	if ((read(fd, tmp[4096], 0) != 0) || !line)
		return (-1);
	tmp[fd] = (!tmp[fd]) ? ft_strnew(BUFF_SIZE) : tmp[fd];
	finded = ft_get_index(tmp[fd], '\n');
	size = 1;
	ret = 0;
	*line = ft_strnew(1);
	while (!finded)
	{
		check_tmp(line, tmp[fd], &size, ret);
		if ((!(ret = read(fd, tmp[fd], BUFF_SIZE))) && !*tmp[fd])
			return (0);
		finded = ft_get_index(tmp[fd], '\n');
		if (ret != BUFF_SIZE)
			finded = get_find_and_clear(&tmp[fd], finded, ret);
	}
	*line = ft_realloc(*line, size, size + finded - 1);
	*line = ft_strncat(*line, tmp[fd], finded - 1);
	ft_strfromcpy(tmp[fd], tmp[fd], finded);
	return (1);
}
