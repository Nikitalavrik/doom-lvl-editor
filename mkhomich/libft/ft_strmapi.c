/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 18:37:17 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/03 18:43:53 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*str;
	size_t	l;

	i = 0;
	if (!s || !f)
		return (NULL);
	l = ft_strlen(s);
	str = malloc(sizeof(char) * (l + 1));
	if (!str)
		return (NULL);
	str[l] = '\0';
	while (s[i])
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	return (str);
}
