/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:52:38 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/09 13:51:53 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_sign(long int nb)
{
	if (nb < 0)
		nb = -nb;
	return (nb);
}

char		*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*str;

	len = ft_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = '\0';
	if (n < 0)
		sign = -1;
	else
		sign = 1;
	len--;
	while (len >= 0)
	{
		str[len] = ft_sign(n % 10) + '0';
		n = ft_sign(n / 10);
		len--;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}
