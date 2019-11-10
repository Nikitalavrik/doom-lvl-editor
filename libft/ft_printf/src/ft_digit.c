/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 11:07:10 by nlavrine          #+#    #+#             */
/*   Updated: 2018/12/28 11:07:10 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#define PLUS_INFINITE          (1.0f/0.0f)
#define MINUS_INFINITE         (-1.0f/0.0f)

int			count_sharp(unsigned long long n, int type, t_format form,\
																	int len)
{
	if (!check_flags(form, '#'))
		return (0);
	if ((type == 'x' || type == 'X') && (form.precision || len) &&\
	(n || check_flags(form, 'p')))
		return (2);
	else if (type == 'o')
	{
		if (!n && form.precision)
			return (0);
		return (1);
	}
	return (0);
}

t_ull		ft_inverse(t_ull n, char type, int neg)
{
	t_ull tmp;

	if (neg)
	{
		tmp = UINT64_MAX;
		if (!type)
			tmp = (unsigned int)tmp;
		else if (type == L_TYPE)
			tmp = (unsigned long)tmp;
		else if (type == LL_TYPE)
			tmp = (unsigned long long)tmp;
		else if (type == H_TYPE)
			tmp = (unsigned short int)tmp;
		else if (type == HH_TYPE)
			tmp = (unsigned char)tmp;
		tmp = ((-n) ^ tmp) + 1;
	}
	else
		tmp = n;
	return (tmp);
}

int			check_inf(long double num, t_format form, char **ret)
{
	char	*str1;
	char	*str2;
	char	*str3;

	str1 = form.type == 'F' ? "NAN" : "nan";
	str2 = form.type == 'F' ? "INF" : "inf";
	if (check_flags(form, ' '))
		str2 = form.type == 'F' ? " INF" : " inf";
	if (check_flags(form, '+'))
		str2 = form.type == 'F' ? "+INF" : "+inf";
	str3 = form.type == 'F' ? "-INF" : "-inf";
	form.precision = -42;
	if (num != num)
		return (ft_fputstr(str1, form, ret));
	else if (num == PLUS_INFINITE)
		return (ft_fputstr(str2, form, ret));
	else if (num == MINUS_INFINITE)
		return (ft_fputstr(str3, form, ret));
	return (0);
}
