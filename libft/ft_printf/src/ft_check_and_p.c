/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 14:21:33 by nlavrine          #+#    #+#             */
/*   Updated: 2018/12/26 14:21:33 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int		print_pointer(void *adr, t_format form, char **ret)
{
	form.type = 'x';
	form.flags[3] = '#';
	form.flags[4] = 'p';
	if (form.precision == 0)
	{
		form.precision = -42;
		return (ft_fputstr("0x", form, ret));
	}
	return (check_putnbr((long)adr, form, 16, ret));
}

int		check_flags(t_format f, char flag)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (f.flags[i++] == flag)
			return (1);
	}
	return (0);
}

char	*apost(char *ret, int *ilen, t_format f)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = ft_memalloc(sizeof(char) * (*ilen + 1 + f.count_stars));
	while (ret[j] == '0' || ret[j] == '-' || ret[j] == ' ' || ret[j] == '+')
		str[i++] = ret[j++];
	f.star_pos += i;
	while (j < *ilen)
	{
		if (i == f.star_pos)
		{
			str[i] = ',';
			f.star_pos += 4;
			i++;
		}
		str[i] = ret[j];
		i++;
		j++;
	}
	*ilen += f.count_stars;
	free(ret);
	return (str);
}

int		check_unicode(wchar_t c, int *count, char **ret, int len)
{
	if ((c >= 0xd800 && c <= 0xdfff) || c > 0x10ffff)
	{
		*count = -1;
		return (0);
	}
	if (len <= 7 || MB_CUR_MAX == 1)
	{
		if (len <= 8)
		{
			*ret = (char *)ft_memalloc((*count)++);
			(*ret)[0] = (char)c;
		}
		else
			*count = -1;
		return (0);
	}
	return (1);
}

int		ft_printsharp(char type, t_ull n, t_format f, char **ret)
{
	if ((n == 0 && !check_flags(f, 'p')) || f.type == 'u')
		return (0);
	if (type == 'x')
		ft_strncat(*ret, "0x", 2);
	else if (type == 'X')
		ft_strncat(*ret, "0X", 2);
	else if (type == 'o')
		ft_strncat(*ret, "0", 1);
	return (type == 'o' ? 1 : 2);
}
