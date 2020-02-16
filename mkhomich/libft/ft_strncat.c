/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:26:51 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/14 14:26:01 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *str, const char *src, size_t n)
{
	size_t a;
	size_t b;

	a = 0;
	b = 0;
	while (str[a])
		a++;
	while (src[b] && b < n)
	{
		str[a] = src[b];
		a++;
		b++;
	}
	str[a] = '\0';
	return (str);
}
