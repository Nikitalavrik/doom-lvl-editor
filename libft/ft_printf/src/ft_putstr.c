/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 13:38:46 by nlavrine          #+#    #+#             */
/*   Updated: 2018/12/16 13:38:52 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int		ft_fputchar(wchar_t c, char **ret, t_format *form)
{
	int	len;
	int bits;

	bits = len_bits(c);
	if (c > 0x10ffff || (c < 0 && form->length == L_TYPE) ||\
											(c >= 0xd800 && c <= 0xdfff))
		return (-1);
	if (form->length == L_TYPE && bits >= 8)
	{
		*ret = modify_unicode(c, &len);
		return (len);
	}
	len = 1;
	if (c == '\0')
		form->flags[4] = 'c';
	*ret = (char *)malloc(sizeof(char) * (len + 1));
	(*ret)[len - 1] = c;
	if (c)
		(*ret)[len] = '\0';
	return (len);
}

int		ft_fill(char **ret, t_format form, int ilen)
{
	int	i;

	i = 0;
	form.width = form.precision >= 0 ? form.precision : form.width;
	while ((ilen + (i) < form.precision || (ilen + i < form.width &&\
	check_flags(form, '0'))))
	{
		*(*ret)++ = '0';
		i++;
	}
	return (i);
}

int		check_i_f_perc(char c)
{
	return (c != 'i' && c != 'x' && c != 'X' && c != 'o' && c != 'U'
	&& c != 'u' && c != 'p' && c != 'f' && c != 'F');
}

int		format_alight(char **str, t_format form, int len)
{
	int		i;
	int		ret;
	char	fill_char;

	ret = form.width - len;
	if (ret <= 0)
		return (0);
	*str = ft_realloc(*str, len, form.width + 1);
	i = (check_flags(form, '-') ? len - 1 : -1);
	if (++i < len)
		ft_memmove(&(*str)[ret + i], *str, len);
	i = check_flags(form, '-') ? len - 1 : -1;
	len = check_flags(form, '-') ? 0 : len;
	fill_char = (check_flags(form, '0') && ((!check_flags(form, '-')\
						&& check_i_f_perc(form.type)))) ? '0' : ' ';
	while (++i < form.width - len)
		(*str)[i] = fill_char;
	return (ret);
}

int		ft_fputstr(char *str, t_format form, char **ret)
{
	int		len;
	int		len_str;

	if (!form.precision)
		return (0);
	if (!str)
		str = "(null)";
	len_str = init_strlen(ft_strlen((char *)str), &form, 0, &len);
	if (!len_str)
		return (0);
	*ret = (char *)ft_memalloc(len_str + 1);
	while (str[++len] && (len < form.len_prc || form.len_prc < 0))
		(*ret)[len] = str[len];
	(*ret)[len] = '\0';
	return (len);
}
