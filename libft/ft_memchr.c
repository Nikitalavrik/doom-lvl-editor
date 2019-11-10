/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:59:17 by nlavrine          #+#    #+#             */
/*   Updated: 2018/10/23 16:59:18 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	unsg_c;

	i = 0;
	unsg_c = (unsigned char)c;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == unsg_c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
