/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:12:02 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/04 15:38:52 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *str, const char *src)
{
	int a;
	int b;

	a = 0;
	b = 0;
	while (str[a])
		a++;
	while (src[b])
	{
		str[a] = src[b];
		a++;
		b++;
	}
	str[a] = '\0';
	return (str);
}
