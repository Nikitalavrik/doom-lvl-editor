/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 16:53:29 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/03 14:48:36 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	char	*b;
	char	*a;

	b = (char*)haystack;
	a = (char *)needle;
	i = 0;
	if (needle[0] == '\0')
		return (&b[i]);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j])
		{
			j++;
			if (!a[j])
				return (&b[i]);
		}
		i++;
	}
	return (NULL);
}
