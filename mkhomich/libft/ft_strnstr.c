/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:28:33 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/02 18:50:45 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (*haystack && len)
	{
		i = 0;
		if (*haystack == *needle)
		{
			while (*(haystack + i) == *(needle + i) && len - i)
			{
				i++;
				if (*(needle + i) == '\0')
					return ((char *)haystack);
			}
		}
		len--;
		haystack++;
	}
	return (NULL);
}
