/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floatnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 15:16:40 by nlavrine          #+#    #+#             */
/*   Updated: 2018/12/27 15:16:41 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

long double		round_d(long double num, t_format *form, long double *whole)
{
	int			i;
	long double	round_part;
	long double t;

	i = -1;
	round_part = 0.5;
	while (++i < form->precision && i < 64)
		round_part *= 0.1;
	i = -1;
	t = num;
	while (++i < form->precision + 1)
		t *= 10;
	if (!(!form->precision && (long long)t % 5 == 0\
								&& (long long)(*whole) % 2 == 0))
		num += round_part;
	if (num >= 1)
	{
		(*whole)++;
		num--;
	}
	i = -1;
	while (++i < form->precision && i < 64)
		num *= 10;
	form->sign = 0;
	return (num);
}

int				put_round(long double num, t_format *form, char **ret,\
														long double *whole)
{
	int			len;
	int			i;
	t_format	copy_form;

	*ret = NULL;
	form->precision = form->tmp_precision;
	form->precision = form->precision < 0 ? 6 : form->precision;
	copy_form = *form;
	i = -1;
	copy_form.flags[6] = 'r';
	while (++i < 5)
		if (copy_form.flags[i] == '+' || copy_form.flags[i] == ' ' ||\
			copy_form.flags[i] == '\'' || copy_form.flags[i] == '0')
			copy_form.flags[i] = '\0';
	num = round_d(num, form, whole);
	num = num < 1 ? 0 : num;
	if (check_flags(*form, '0'))
		form->width -= form->precision + (!form->precision &&\
			!check_flags(*form, '#') ? 0 : 1);
	if (form->precision == 0)
		return (0);
	len = check_putnbr(num, copy_form, 10, ret);
	return (len);
}

long double		get_whole(long double num)
{
	long double tmp;
	long double whole;
	int			i;

	i = 0;
	tmp = 1.0;
	whole = 0.0;
	while (num / 10.0L >= tmp)
		tmp *= 10.0L;
	while (num >= 1)
	{
		whole += (int)(num / tmp) * tmp;
		num -= (int)(num / tmp) * tmp;
		tmp /= 10;
		i++;
	}
	return (whole);
}

int				put_point(char **ret, char *str, int len1, int len2)
{
	*ret = ft_realloc(*ret, len1, len1 + len2 + 1);
	(*ret)[len1] = '.';
	*ret = ft_strncat(*ret, str, len2);
	ft_memdel((void**)&str);
	return (len2 + 1);
}

int				ft_floatnum(long double num, t_format *form, char **ret)
{
	long	double	whole_part;
	long	double	after_point;
	t_float			form_num;
	char			*str;
	int				len;

	str = NULL;
	num = form->length != LD_TYPE ? (double)num : num;
	if ((len = check_inf(num, *form, ret)))
		return (len);
	form_num.f = num;
	form->tmp_precision = form->precision;
	form->type = 'i';
	num = num < 0 ? -num : num;
	whole_part = get_whole(num);
	after_point = (num - (form->length != LD_TYPE ?\
							(double)whole_part : whole_part));
	form->flags[5] = 'f';
	after_point = put_round(after_point, form, &str, &whole_part);
	form->sign = form_num.t_ieee754.sign;
	form->precision = ft_count_dlen(whole_part);
	len = (t_ull)check_putnbr(whole_part, *form, 10, ret);
	if (form->tmp_precision != 0 || check_flags(*form, '#'))
		len += put_point(ret, str, len, after_point);
	return (len);
}
