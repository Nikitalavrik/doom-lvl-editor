/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 14:04:22 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/02 18:22:07 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t ldst;
	size_t lsrc;
	size_t k;

	ldst = ft_strlen(dst);
	lsrc = ft_strlen(src);
	k = ldst;
	if (dstsize < ldst)
		return (lsrc + dstsize);
	while (*src && k < dstsize - 1)
		dst[k++] = *src++;
	dst[k] = '\0';
	return (ldst + lsrc);
}
