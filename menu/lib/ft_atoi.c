/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 12:42:26 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/09 13:29:09 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		check(unsigned long long res)
{
	if (res > 2147483647)
	{
		ft_putstr("Error number");
		exit(0);
	}
}

int			ft_atoi(const char *str)
{
	unsigned long long	res;
	long long			k;

	res = 0;
	k = 1;
	if (!str)
		return (0);
	while (*str == ' ' || *str == '\n' || *str == '\t' || \
	*str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
	{
		k = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	check(res);
	return (res * k);
}
