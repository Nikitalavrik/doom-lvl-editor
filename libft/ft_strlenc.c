/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlenc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 19:31:23 by nlavrine          #+#    #+#             */
/*   Updated: 2018/10/28 19:31:24 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlenc(char *tmp, char c)
{
	size_t	len;

	len = 0;
	if (!tmp)
		return (0);
	while (*(tmp + len) != c && *(tmp + len))
		len++;
	return (len);
}
