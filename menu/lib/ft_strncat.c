/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:26:51 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/02 15:21:43 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *str, char *src, unsigned int n)
{
	unsigned int a;
	unsigned int b;

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
