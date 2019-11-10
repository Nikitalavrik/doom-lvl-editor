/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 16:58:19 by nlavrine          #+#    #+#             */
/*   Updated: 2019/03/25 16:58:21 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int			check_type(char c)
{
	if (c != 'i' && c != 'x' && c != 'X' && c != 'o' && c != 'U'
	&& c != 'u' && c != 'c' && c != 's' && c != 'p' && c != '%'\
	&& c != 'f' && c != 'F' && c != 'b' && c != 'S')
		return (1);
	return (0);
}

int			check_print(t_format f, va_list args, char **t, intmax_t tmp)
{
	if (f.type == 's')
		tmp = ft_fputstr(va_arg(args, char *), f, t);
	else if (f.type == 'S')
		tmp = ft_putunicode(va_arg(args, wchar_t *), f, t);
	else if (f.type == 'i')
		tmp = check_putnbr(f.length ? tmp : va_arg(args, int), f, 10, t);
	else if (f.type == 'x' || f.type == 'X')
		tmp = check_putnbr(f.length ? tmp : va_arg(args, int), f, 16, t);
	else if (f.type == 'p')
		tmp = print_pointer(va_arg(args, int *), f, t);
	else if (f.type == 'o')
		tmp = check_putnbr(f.length ? tmp : va_arg(args, int), f, 8, t);
	else if (f.type == 'u')
		tmp = check_putnbr(f.length ? tmp : va_arg(args, int), f, 10, t);
	else if (f.type == 'f' || f.type == 'F')
		tmp = ft_floatnum(f.length == LD_TYPE ? va_arg(args, long double) :\
	va_arg(args, double), &f, t);
	else if (f.type == '%')
		tmp = ft_fputchar(f.type, t, &f);
	else if (f.type == 'b')
		tmp = check_putnbr(va_arg(args, unsigned long long), f, 2, t);
	else
		tmp = ft_fputchar(f.type != 'c' ? f.type : va_arg(args, int), t, &f);
	return (tmp);
}

void		parse_stars(va_list args, t_format *f, int *iter)
{
	int			i;
	va_list		copy_args;

	i = 0;
	*iter = -1;
	va_copy(copy_args, args);
	if (f->count_stars)
	{
		while (i++ < f->count_stars - 1)
			f->len_prc = va_arg(copy_args, int);
		if (f->star_pos != 1 && f->star_pos)
			f->precision = f->len_prc;
		if (check_flags(*f, '*'))
		{
			f->len_prc = f->star_pos != 1 ? va_arg(copy_args, int) : f->len_prc;
			f->width = f->width ? f->width : f->len_prc;
			f->flags[6] = f->width < 0 ? '-' : '\0';
			f->width = f->width < 0 ? -f->width : f->width;
		}
		if (f->star_pos == 1)
			f->precision = va_arg(copy_args, int);
	}
}

long long	stars_grap(va_list args, t_format *f)
{
	int			i;
	int			j;
	va_list		copy_args;

	parse_stars(args, f, &i);
	if (!f->dol_pos[0] && !f->dol_pos[1] && !f->dol_pos[2] && !f->count_stars)
		return (check_args(args, f, 0));
	while (++i < 2 && (f->dol_pos[0] || f->dol_pos[1]))
	{
		j = -1;
		va_copy(copy_args, f->copy_args);
		while (++j < f->dol_pos[i])
			f->len_prc = va_arg(copy_args, int);
		if (i == 0 && f->dol_pos[0])
			f->precision = f->len_prc;
		else if (i == 1 && f->dol_pos[1])
			f->width = f->len_prc;
	}
	if (f->dol_pos[2])
		va_copy(args, f->copy_args);
	j = -1;
	f->dol_pos[2] = f->dol_pos[2] ? f->dol_pos[2] : 1;
	while (++j < f->dol_pos[2] - 1 + f->count_stars)
		f->len_prc = va_arg(args, int);
	return (check_args(args, f, 0));
}

long long	check_args(va_list args, t_format *f, int option)
{
	if (option)
		return (stars_grap(args, f));
	if (f->length == LD_TYPE && f->type != 'f' && f->type != 'F')
		f->length = WITHOUT_TYPE;
	if (!f->type || f->type == 's' || f->type == 'c' || f->type == 'p'\
	|| f->type == 'f' || f->type == 'U' || f->type == 'S')
		return (0);
	if (f->length == L_TYPE)
		return (va_arg(args, long));
	else if (f->length == LL_TYPE)
		return (va_arg(args, long long));
	else if (f->length == H_TYPE)
		return ((short)va_arg(args, int));
	else if (f->length == HH_TYPE)
		return ((char)va_arg(args, int));
	else if (f->length == J_TYPE)
		return (va_arg(args, intmax_t));
	else if (f->length == U_TYPE)
		return (va_arg(args, unsigned long));
	return (0);
}
