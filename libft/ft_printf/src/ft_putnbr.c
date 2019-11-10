/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 13:55:27 by nlavrine          #+#    #+#             */
/*   Updated: 2018/12/16 13:55:29 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

t_ull	ft_cast_type(long long n, char type)
{
	ssize_t	num;

	if (!type)
		n = (int)n;
	else if (type == L_TYPE)
		n = (long)n;
	else if (type == LL_TYPE)
		n = (long long)n;
	else if (type == H_TYPE)
		n = (short int)n;
	else if (type == HH_TYPE)
		n = (char)n;
	num = (n < 0) ? -n : n;
	return (num);
}

int		ft_fputnbr(long double num, t_format *form,\
									unsigned int base, char **ret)
{
	if (!form->precision && !num && form->type == 'i')
		return (0);
	if (num >= base)
		ft_fputnbr(num / base, form, base, ret);
	num = (t_ull)num % base;
	num += (num < 10) ? '0' : form->type - 33;
	*(*ret)++ = num;
	**ret = '\0';
	return (0);
}

int		precis_double(long double num, char **ret, t_format *form, int *i)
{
	int len;

	*i = 0;
	len = ft_count_dlen(num);
	form->tmp_precision = check_flags(*form, 'r');
	while ((form->tmp_precision || check_flags(*form, '0')) && (len < 64 ||\
	check_flags(*form, '0')) && len < form->precision)
	{
		*(*ret)++ = '0';
		(*i)++;
		len++;
	}
	return (*i);
}

int		check_double(long double num, char **ret, t_format form)
{
	long double tmp;
	int			whole_part;
	int			i;
	int			len;

	tmp = 1.0;
	len = precis_double(num, ret, &form, &i);
	while (num / tmp >= 10.0)
		tmp *= 10;
	while (i < form.precision)
	{
		if (i++ < 64 || !form.tmp_precision)
		{
			whole_part = (int)(num / tmp);
			*(*ret)++ = whole_part + '0';
			num -= (whole_part * tmp);
			tmp /= 10;
		}
		else
		{
			*(*ret)++ = '0';
			len++;
		}
	}
	return (len);
}

int		check_putnbr(long double n, t_format f, int base, char **ret)
{
	t_ull	num;
	int		ilen;

	ilen = init_len_num(&f, &num, n, base);
	if (!ilen)
		return (0);
	create_ret(ret, f, ilen);
	if (check_flags(f, '#') && f.type != 'i' && !check_flags(f, 'f'))
		*ret += ft_printsharp(f.type, num, f, ret);
	if (f.sign == 1 || ((n < 0 || (n >= 0 && check_flags(f, '+'))) &&\
														f.type == 'i'))
		*(*ret)++ = n < 0 || f.sign ? '-' : '+';
	if (n >= 0 && check_flags(f, ' ') && !check_flags(f, '+')\
												&& f.type == 'i' && !f.sign)
		*(*ret)++ = ' ';
	if ((ilen < f.precision || (check_flags(f, '0') &&\
								!check_flags(f, '-'))) && !check_flags(f, 'f'))
		ilen += ft_fill(ret, f, ilen);
	ilen += check_flags(f, 'f') ?\
	check_double(n, ret, f) : ft_fputnbr(num, &f, base, ret);
	*ret -= ilen;
	*ret = check_flags(f, '\'') && f.count_stars ? apost(*ret, &ilen, f) : *ret;
	return (ilen);
}
