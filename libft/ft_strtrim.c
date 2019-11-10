/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 11:20:09 by nlavrine          #+#    #+#             */
/*   Updated: 2018/10/27 11:20:10 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
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
		while (s[i] <= 32 && s[i])
			i++;
		while (s[len - 1] <= 32 && s[len - 1])
			len--;
		if (!(ret = ft_strnew((len <= i) ? 0 : len - i)))
			return (NULL);
		while (i < len && (len - i))
			ret[j++] = s[i++];
		return (ret);
	}
	return (NULL);
}
