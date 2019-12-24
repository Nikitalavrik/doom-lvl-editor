/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:22:02 by tbahlai           #+#    #+#             */
/*   Updated: 2019/02/27 16:22:02 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_count_line(char *s)
{
	int i;
	int line;

	i = 0;
	line = 0;
	if (!s[i])
		return (-1);
	while (s[i])
	{
		if (s[i] == '\n')
			line++;
		i++;
	}
	return (line);
}
