/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 19:44:43 by nlavrine          #+#    #+#             */
/*   Updated: 2018/10/26 19:44:44 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_str_wordscount(char *tmp, char c)
{
	size_t	i;
	size_t	word_count;

	i = 0;
	word_count = 1;
	while (tmp[++i])
		word_count += (tmp[i] != c && tmp[i - 1] == c) ? 1 : 0;
	return (word_count);
}

static	size_t	iterate(char **out, size_t word_count, char *tmp, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = 0;
	while (i < word_count && ft_strcmp(&tmp[j], "") != 0)
	{
		while (tmp[j] == c)
			j++;
		len = ft_strlenc(&tmp[j], c);
		out[i] = ft_strnew(len);
		ft_memmove(out[i++], &tmp[j], len);
		j += len;
		len = 0;
	}
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	word_count;
	char	**out;
	char	*tmp;
	size_t	end;

	if (!(tmp = ft_strtrimc(s, c)) || !s)
		return (NULL);
	word_count = ft_str_wordscount(tmp, c) + 1;
	if (!(out = (char **)malloc(sizeof(char *) * word_count)))
		return (NULL);
	end = iterate(out, word_count, tmp, c);
	if (tmp)
		ft_memdel((void **)&tmp);
	out[end] = NULL;
	return (out);
}
