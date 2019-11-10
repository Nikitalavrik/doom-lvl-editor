/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 18:54:35 by nlavrine          #+#    #+#             */
/*   Updated: 2018/10/26 18:54:36 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(ret = ft_strnew(len + 1)))
		return (NULL);
	ft_strncpy(ret, s1, ft_strlen(s1));
	ft_strncpy(ret + ft_strlen(s1), s2, ft_strlen(s2));
	return (ret);
}
