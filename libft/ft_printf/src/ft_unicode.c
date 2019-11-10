/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unicode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 17:26:57 by nlavrine          #+#    #+#             */
/*   Updated: 2019/06/18 17:27:23 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int		unicode_len(wchar_t *str)
{
	int count;
	int	i;
	int	bits;

	count = 0;
	i = 0;
	while (str[i])
	{
		bits = len_bits(str[i]);
		if (bits <= 7 || MB_CUR_MAX == 1)
			count++;
		else if (bits <= 11 && MB_CUR_MAX > 1)
			count += 2;
		else if (bits <= 16 && MB_CUR_MAX > 2)
			count += 3;
		else if (bits > 16 && MB_CUR_MAX > 3)
			count += 4;
		i++;
	}
	return (count);
}

int		len_bits(wchar_t num)
{
	int		count;

	count = 0;
	while (num)
	{
		num /= 2;
		count++;
	}
	return (count);
}

char	*modify_unicode(wchar_t c, int *count)
{
	unsigned int	len;
	unsigned char	symbol;
	int				i;
	char			*ret;

	len = len_bits(c);
	*count = 0;
	ret = NULL;
	if (!check_unicode(c, count, &ret, len))
		return (ret);
	i = len > 16 && MB_CUR_MAX == 4 ? 4 : 3;
	i = len <= 11 && MB_CUR_MAX >= 2 ? 2 : i;
	ret = (char *)ft_memalloc(sizeof(char) * (i + 1));
	ret[(*count)] = (((unsigned int)c >> (6 * (i - 1))) << (25 + i) >> (25 + i))
	| (unsigned char)(192 + ((i != 2) ? (i - 1) * 16 : 0));
	while (--i)
	{
		symbol = ((unsigned int)c >> ((i - 1) * 6)) << 26 >> 26 | 128;
		ret[++(*count)] = symbol;
	}
	ret[++(*count)] = '\0';
	return (ret);
}

int		clear_ret(char *c, char **ret)
{
	free(c);
	free(*ret);
	return (-1);
}

int		ft_putunicode(wchar_t *str, t_format form, char **ret)
{
	int		len;
	int		len_str;
	int		i;
	char	*c;

	if (!form.precision)
		return (0);
	if (!str)
		return (ft_fputstr("(null)", form, ret));
	len_str = init_strlen(unicode_len(str), &form, 1, &len);
	if (!len_str)
		return (0);
	*ret = ft_memalloc(len_str + 1);
	while (str[++len] && form.tmp_precision < len_str)
	{
		c = modify_unicode(str[len], &i);
		if (i == -1)
			return (clear_ret(c, ret));
		form.tmp_precision += i;
		if (form.tmp_precision <= len_str)
			ft_strncat(*ret, c, i);
		else if (i != -1)
			len_str = form.tmp_precision - i;
	}
	return (len_str);
}
