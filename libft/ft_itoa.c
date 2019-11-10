/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 13:06:25 by nlavrine          #+#    #+#             */
/*   Updated: 2018/10/27 13:06:27 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_lenght_int(int n)
{
	size_t	count;

	count = (n <= 0) ? 1 : 0;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char			*ft_itoa(int n)
{
	size_t			len;
	char			*ret;
	unsigned int	unsign_n;

	len = ft_lenght_int(n);
	unsign_n = (n < 0) ? -n : n;
	if ((ret = ft_strnew(len)))
	{
		while (unsign_n)
		{
			ret[len - 1] = unsign_n % 10 + '0';
			unsign_n /= 10;
			len--;
		}
		if (len)
			ret[0] = '-';
		ret[0] = (ret[0] == '-' && !ret[1]) ? '0' : ret[0];
		return (ret);
	}
	return (NULL);
}
