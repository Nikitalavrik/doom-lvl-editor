/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 13:25:28 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/02 14:07:16 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *src;

	src = (unsigned char *)b;
	if ((int)len >= 0)
	{
		while (len--)
		{
			*src = (unsigned char)c;
			src++;
		}
		return (b);
	}
	return (NULL);
}
