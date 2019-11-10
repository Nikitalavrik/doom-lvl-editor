/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 13:49:46 by nlavrine          #+#    #+#             */
/*   Updated: 2018/12/16 13:49:47 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#define PLUS_INFINITE          (1.0f/0.0f)
#define MINUS_INFINITE         (-1.0f/0.0f)

int		count_coma_pos(long double n, t_format *f)
{
	int count;

	count = 0;
	if (n == 0)
		return (0);
	while (n >= 1000 || n <= -1000)
	{
		n /= 1000;
		count++;
	}
	f->count_stars = count;
	if (n / 100 > 1)
		return (3);
	if (n / 10 > 1)
		return (2);
	return (1);
}

int		init_len_num(t_format *f, t_ull *num, long double n, int b)
{
	int	ilen;

	ilen = 0;
	*num = (f->type == 'i') ? ft_cast_type(n, f->length) :
	ft_inverse((t_ull)n, f->length, n < 0);
	ilen = check_flags(*f, 'f') ? ft_count_dlen(n) : ft_count_ilen(*num, b, *f);
	ilen += ((n < 0 || check_flags(*f, '+') ||\
	check_flags(*f, ' ') || f->sign) && f->type == 'i' ? 1 : 0) +\
	count_sharp(*num, f->type, *f, ilen);
	f->precision += ((n < 0 || check_flags(*f, '+') ||\
	check_flags(*f, ' ')) && f->type == 'i' && !check_flags(*f, 'f')\
	&& (n || f->precision) ? 1 : 0) +\
	(count_sharp(*num, f->type, *f, ilen) < 2 ? 0 : 2);
	if (check_flags(*f, 'f') && check_flags(*f, '0') && !check_flags(*f, '-'))
		f->precision += f->width > ilen ? f->width - ilen : 0;
	f->star_pos = 0;
	f->count_stars = 0;
	if ((f->type == 'i' || f->type == 'u' || f->type == 'o') &&\
							check_flags(*f, '\'') && MB_CUR_MAX > 1)
	{
		f->star_pos = count_coma_pos(n, f);
		f->precision -= check_flags(*f, 'f') && (!check_flags(*f, '0') ||\
		f->width < 0 || check_flags(*f, '-')) ? 0 : f->count_stars;
	}
	return (ilen);
}

t_ull	ft_count_dlen(long double num)
{
	t_ull	count;

	if (!(num))
		return (1);
	count = 0;
	while ((num >= 1 || num <= -1) && num < PLUS_INFINITE\
	&& num > MINUS_INFINITE)
	{
		num /= 10;
		count++;
	}
	return (count);
}

int		ft_count_ilen(t_ull n, int base, t_format form)
{
	int	count;

	count = 0;
	if ((!n && form.precision) || check_flags(form, 'f'))
		return (1);
	while (n > 0)
	{
		n /= base;
		count++;
	}
	return (count);
}
