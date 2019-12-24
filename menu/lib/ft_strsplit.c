/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:05:38 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/09 12:39:17 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len_word(char const *s, char c)
{
	size_t i;

	i = 0;
	while (*(s + i) && *(s + i) != c)
		i++;
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str;
	size_t	a;
	size_t	b;

	if (!s || !c)
		return (NULL);
	b = ft_count_words((char*)s, c);
	if (!(str = (char **)ft_memalloc(sizeof(char*) * (b + 1))))
		return (NULL);
	a = 0;
	while (a < b)
	{
		while (*s && *s == c)
			s++;
		str[a] = ft_strsub(s, 0, ft_len_word(s, c));
		if (str[a] == NULL)
		{
			free(str[a]);
			return (NULL);
		}
		a++;
		s = s + ft_len_word(s, c);
	}
	str[a] = NULL;
	return (str);
}
