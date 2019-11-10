/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 17:27:21 by nlavrine          #+#    #+#             */
/*   Updated: 2019/03/25 17:27:22 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int		find_type(char c, char prev_c)
{
	char	*types;
	int		k;

	k = -1;
	types = "cspdiouxXfU%ZDSCbO";
	while (++k < 16)
	{
		if (c == types[k] || (c != 'l' && c != 'h' && c != ' ' && c != '#' &&
		c != '0' && c != '-' && c != '+' && c != '.' && c != 'z' && c != 'L' &&
		c != 'j' && c != '*' && !ft_isdigit(c) && c != '\'' && c != 't' &&\
		c != '$') || (c == '$' && !ft_isdigit(prev_c)))
			return (1);
	}
	return (0);
}

void	recast(t_format *form)
{
	if (form->type == 'U' || form->type == 'D' || form->type == 'O' ||\
									form->type == 'C')
		form->length = L_TYPE;
	form->type = form->type == 'd' ? 'i' : form->type;
	form->type = form->type == 'O' ? 'o' : form->type;
	form->type = form->type == 'D' ? 'i' : form->type;
	form->type = form->type == 'C' ? 'c' : form->type;
	form->type = form->type == 'U' ? 'u' : form->type;
}

int		init_form(t_format *form, int *i, int len_format, const char *str)
{
	int		k;
	int		key_len;

	k = -1;
	while (++k < 7)
		form->flags[k] = 0;
	k = -1;
	while (++k < 3)
		form->dol_pos[k] = 0;
	form->width = 0;
	form->precision = -42;
	form->length = 0;
	form->type = 0;
	form->begin = *i;
	form->sign = 0;
	form->count_stars = 0;
	form->star_pos = 0;
	form->len_prc = 0;
	key_len = *i;
	while (!find_type(str[key_len], str[key_len - 1]) && key_len < len_format)
		key_len++;
	form->type = key_len < len_format ? str[key_len] : 0;
	recast(form);
	*i = key_len;
	return (key_len);
}

void	create_ret(char **ret, t_format f, int ilen)
{
	if (f.precision > ilen)
		*ret = (char *)ft_memalloc(sizeof(char) * (f.precision + 1));
	else
		*ret = (char *)ft_memalloc(sizeof(char) * ((f.width > ilen &&\
		check_flags(f, '0') && f.precision < 0 && !check_flags(f, 'f')\
		? f.width : ilen) + 1));
}

int		init_strlen(int len_str, t_format *form, char option, int *len)
{
	*len = -1;
	len_str = (form->precision > 0 && form->precision < len_str) ?\
	form->precision : len_str;
	form->precision = len_str;
	if (option)
		form->tmp_precision = 0;
	else
		form->len_prc = form->precision;
	return (len_str);
}
