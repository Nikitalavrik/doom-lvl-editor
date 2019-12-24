/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 14:20:15 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/04 15:38:20 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *str, const char *src)
{
	int a;
	int b;

	a = 0;
	b = 0;
	while (src[a])
	{
		str[b] = src[a];
		a++;
		b++;
	}
	str[b] = '\0';
	return (str);
}
