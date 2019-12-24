/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 14:52:52 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/02 18:34:11 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char *temp;

	temp = s;
	temp = temp + ft_strlen(s);
	while (*temp != (char)c && temp != s)
		temp--;
	if (*temp == (char)c)
		return ((char *)temp);
	return (NULL);
}
