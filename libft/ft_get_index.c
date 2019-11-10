/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_index.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 12:06:19 by nlavrine          #+#    #+#             */
/*   Updated: 2018/10/31 12:06:20 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_get_index(char *tmp, char c)
{
	size_t	i;

	i = 0;
	if (!tmp)
		return (0);
	while (tmp[i] != c && tmp[i])
		i++;
	return ((tmp[i] == c) ? i + 1 : 0);
}
