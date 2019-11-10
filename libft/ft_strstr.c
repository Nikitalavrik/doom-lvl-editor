/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 14:08:12 by nlavrine          #+#    #+#             */
/*   Updated: 2018/10/26 14:08:13 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *neendle)
{
	size_t	i;
	size_t	dst_len;
	size_t	find_len;

	i = 0;
	dst_len = ft_strlen(haystack);
	find_len = ft_strlen(neendle);
	if (dst_len >= find_len)
		while (find_len <= dst_len && (haystack[i] || i == 0))
		{
			if (!ft_memcmp(haystack + i, neendle, find_len))
				return ((char *)(haystack + i));
			i++;
			dst_len--;
		}
	return (NULL);
}
