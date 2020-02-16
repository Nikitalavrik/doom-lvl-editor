/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 16:09:18 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/02 18:10:53 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *str1;
	char *str2;

	str1 = (char *)dst;
	str2 = (char *)src;
	if ((int)n >= 0)
	{
		while (n--)
		{
			*str1 = *str2;
			str1++;
			str2++;
		}
		return (dst);
	}
	return (NULL);
}
