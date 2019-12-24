/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:06:29 by tbahlai           #+#    #+#             */
/*   Updated: 2018/11/08 20:07:42 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_power(int n, int pow)
{
	int res;

	res = 1;
	if (pow == 0 || n == 1)
		return (1);
	if (pow < 0 || n == 0)
		return (0);
	while (pow != 0)
	{
		res *= n;
		pow--;
	}
	return (res);
}
