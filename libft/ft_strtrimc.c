/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 12:16:09 by nlavrine          #+#    #+#             */
/*   Updated: 2018/10/27 12:16:09 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrimc(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*ret;

	i = 0;
	j = 0;
	if (s)
	{
		len = ft_strlen(s);
		while (s[i] == c && s[i])
			i++;
		while (s[len - 1] == c && s[len - 1])
			len--;
		if (!(ret = ft_strnew((len <= i) ? 0 : len - i)))
			return (NULL);
		while (i < len && (len - i))
			ret[j++] = s[i++];
		return (ret);
	}
	return (NULL);
}
