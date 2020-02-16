/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 13:02:50 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/02 17:23:56 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*pdst;
	unsigned const char	*psrc;

	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	if ((int)len >= 0)
	{
		while (len--)
		{
			if (pdst <= psrc)
				*pdst++ = *psrc++;
			else
				pdst[len] = psrc[len];
		}
		return (dst);
	}
	return (NULL);
}
