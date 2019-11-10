/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:02:44 by nlavrine          #+#    #+#             */
/*   Updated: 2019/03/30 14:02:45 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int			flags_ch(char c, char prev_c)
{
	return (c == '#' || c == '-' || c == '+' || c == ' ' ||\
		(c == '*' && prev_c != '.') ||\
		(c == '0' && !ft_isdigit(prev_c) && prev_c != '.')\
		|| c == '\'');
}

int			parse_dollar_and_star(const char *str, int i, t_format *f)
{
	if (str[i - 2] == '*' && (i >= 3 && str[i - 3] == '.') && !f->dol_pos[0])
		f->dol_pos[0] = ft_atoi(&str[i - 1]);
	else if (str[i - 2] == '*' && !f->dol_pos[1])
		f->dol_pos[1] = ft_atoi(&str[i - 1]);
	else if (!f->dol_pos[2])
		f->dol_pos[2] = ft_atoi(&str[i - 1]);
	if (str[i - 2] == '*' && str[i - 3] == '.' && i >= 4)
		i = -3;
	else if (str[i - 2] == '*' && i >= 3)
		i = -2;
	else if (i >= 2)
		i = -1;
	else
		i = 0;
	return (i);
}

int			parse(const char *str, int *i, t_format *f, int len_format)
{
	int		k;
	int		tmp;

	k = init_form(f, i, len_format, str);
	tmp = -1;
	while (k-- > f->begin)
	{
		f->count_stars += str[k] == '*' ? 1 : 0;
		if (str[k] == '$')
			k += parse_dollar_and_star(str, k, f);
		if (flags_ch(str[k], str[k - 1]))
			if (!check_flags(*f, str[k]))
				f->flags[++tmp] = str[k];
		if (str[k] == '*' && str[k - 1] == '.' && !f->star_pos)
			f->star_pos = f->count_stars;
		if (str[k] == '.' && f->precision == -42)
			f->precision = ft_atoi(&str[k + 1]);
		if (str[k - 1] != '.' && !ft_isdigit(str[k - 1]) &&\
											!check_flags(*f, '*'))
			f->width = !(f->width) ? ft_atoi(&str[k]) : f->width;
		f->length = check_length(str, k, *f) < f->length ? f->length :\
		check_length(str, k, *f);
	}
	f->type = f->type == 's' && f->length == L_TYPE ? 'S' : f->type;
	return (!f->type ? 0 : 1);
}

char		check_length(const char *str, int i, t_format f)
{
	int	tmp;

	tmp = 0;
	if (str[i] == 'l')
		tmp = str[i - 1] == 'l' ? LL_TYPE : L_TYPE;
	else if (str[i] == 'h')
		tmp = str[i - 1] == 'h' ? HH_TYPE : H_TYPE;
	else if (str[i] == 'L' && (f.type == 'f' || f.type == 'F'))
		tmp = LD_TYPE;
	else if (str[i] == 'j')
		tmp = J_TYPE;
	else if (str[i] == 'z')
		tmp = L_TYPE;
	else if (str[i] == 't')
		tmp = U_TYPE;
	return (tmp);
}

int			put_error(t_format *f)
{
	f->error = -1;
	return (f->end);
}
