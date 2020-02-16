/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 14:38:33 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/14 14:32:29 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *str, const char *src, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && src[i])
	{
		str[i] = src[i];
		i++;
	}
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}
