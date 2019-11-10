/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 13:14:10 by nlavrine          #+#    #+#             */
/*   Updated: 2018/12/16 13:14:11 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

char		*put_print(t_format *form, va_list args, int *print_len)
{
	intmax_t	tmp;
	char		*tmp_ret;

	tmp_ret = "\0";
	tmp = check_args(args, form, 1);
	tmp = check_print(*form, args, &tmp_ret, tmp);
	if ((form->width || tmp < form->precision) && tmp >= 0)
		tmp += format_alight(&tmp_ret, *form, tmp);
	*print_len += tmp;
	if (tmp < 0)
		*print_len = -42;
	else
		form->end = *print_len;
	return (tmp_ret);
}

void		put_param(t_format *form, int *print_len, char **ret, va_list args)
{
	char	*str;
	int		f_len;

	str = NULL;
	f_len = *print_len;
	str = put_print(form, args, print_len);
	if (*print_len < 0)
		return ;
	*ret = ft_realloc(*ret, f_len, *print_len + (*str ? 1 : 0));
	*ret += f_len;
	*ret = ft_strmcat(*ret, str, *print_len - f_len);
	*ret -= f_len;
	if (str && *str)
		ft_memdel((void **)(&str));
}

void		put_char(char **ret, int *print_len, char c)
{
	*ret = ft_realloc(*ret, *print_len, *print_len + 2);
	(*ret)[*print_len] = c;
	(*ret)[*print_len + 1] = '\0';
	(*print_len)++;
}

int			go_forward(char *str, char **ret, va_list args, t_format *f)
{
	int			str_len;
	int			f_len;
	int			i;
	int			len;

	i = 0;
	*ret = NULL;
	str_len = 0;
	len = f->error;
	while (i < len)
	{
		if (str[i] == '%')
		{
			i++;
			if ((f_len = parse(str, &i, f, len)) > 0 ||\
											(f->width > 0 && str[i]))
				put_param(f, &str_len, ret, args);
			if (str_len < 0 || f_len < 0 || str_len == -42)
				return (put_error(f));
		}
		else
			put_char(ret, &str_len, str[i]);
		i++;
	}
	return (str_len);
}

int			ft_printf(const char *format, ...)
{
	va_list		args;
	int			len_format;
	char		*ret;
	t_format	f;

	va_start(args, format);
	len_format = ft_strlen((char *)format);
	f.error = len_format;
	f.end = 0;
	va_copy(f.copy_args, args);
	len_format = go_forward((char *)format, &ret, args, &f);
	write(1, ret, len_format);
	va_end(f.copy_args);
	va_end(args);
	if (ret && *ret)
		ft_memdel((void **)(&ret));
	return (f.error == -1 ? -1 : len_format);
}
