/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:07:55 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/07 19:26:02 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	begin(const char *s)
{
	int bg;
	int i;

	i = 0;
	bg = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		i++;
		bg++;
	}
	return (bg);
}

static int	end(const char *s)
{
	int	en;
	int	len;

	len = ft_strlen(s) - 1;
	en = 0;
	while (s[len] == ' ' || s[len] == '\t' || s[len] == '\n')
	{
		len--;
		en++;
	}
	return (en);
}

char		*ft_strtrim(char const *s)
{
	char	*new;
	size_t	newlen;
	size_t	i;
	size_t	j;

	if (!s)
		return (0);
	i = 0;
	j = begin(s);
	new = NULL;
	if (ft_strlen(s) - begin(s) <= 0)
		newlen = 0;
	else
		newlen = ft_strlen(s) - begin(s) - end(s);
	new = (char*)malloc(sizeof(char) * (newlen + 1));
	if (!new)
		return (NULL);
	while (newlen-- > 0)
		new[i++] = s[j++];
	new[i] = '\0';
	return (new);
}
