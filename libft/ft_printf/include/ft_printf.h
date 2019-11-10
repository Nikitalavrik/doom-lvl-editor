/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 13:14:23 by nlavrine          #+#    #+#             */
/*   Updated: 2018/12/16 13:14:24 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include "../../libft.h"

# define WITHOUT_TYPE 	0
# define H_TYPE			1
# define HH_TYPE 		2
# define L_TYPE 		3
# define LL_TYPE		4
# define LD_TYPE		5
# define J_TYPE			7
# define U_TYPE			8

typedef unsigned long long t_ull;

typedef	struct		s_format
{
	int		sign;
	char	flags[7];
	int		width;
	int		begin;
	int		precision;
	int		length;
	int		type;
	int		len_prc;
	int		tmp_precision;
	int		count_stars;
	int		star_pos;
	int		end;
	int		dol_pos[3];
	int		count_args;
	int		error;
	va_list	copy_args;
}					t_format;

typedef	union		u_float
{
	double			f;
	struct			s_ieee754
	{
		unsigned long mantice : 52;
		unsigned long exponent : 11;
		unsigned long sign : 1;
	}				t_ieee754;
}					t_float;

int					ft_printf(const char *format, ...);

/*
** check func
*/

int					check_type(char c);
char				check_length(const char *str, int i, t_format form);
int					check_print(t_format form, va_list args,\
								char **tmp_ret, intmax_t tmp);
long long			check_args(va_list args, t_format *form, int option);
int					check_flags(t_format form, char flag);
int					check_inf(long double num, t_format form, char **ret);
int					check_unicode(wchar_t c, int *count, char **ret, int len);

/*
** parse and init start value func
*/

int					init_form(t_format *form, int *i, int len_format,\
													const char *str);
int					init_len_num(t_format *f, t_ull *num, long double n,\
													int base);
int					parse(const char *str, int *i, t_format *f, int len_format);
int					format_alight(char **str, t_format form, int tmp);
void				create_ret(char **ret, t_format f, int ilen);
int					init_strlen(int len_str, t_format *form,\
														char option, int *len);
char				*apost(char *ret, int *ilen, t_format f);

/*
** print func
*/

int					ft_printsharp(char type, t_ull n, t_format f, char **ret);
int					ft_fputchar(wchar_t c, char **ret, t_format *form);
int					ft_fputstr(char *str, t_format form, char **ret);
int					ft_putunicode(wchar_t *str, t_format form, char **ret);
int					print_pointer(void *adr, t_format form, char **ret);
int					ft_floatnum(long double num, t_format *form, char **ret);
int					check_putnbr(long double n, t_format f, int b, char **ret);
void				ft_formatsharp(char next_char);
char				*modify_unicode(wchar_t c, int *count);
int					put_error(t_format *f);

/*
** count len of variable func
*/

int					ft_count_ilen(t_ull n, int b, t_format form);
int					count_sharp(unsigned long long n, int type, t_format form,\
																	int len);
t_ull				ft_count_dlen(long double num);
int					len_bits(wchar_t num);
int					unicode_len(wchar_t *str);

/*
** cast func
*/

int					ft_fill(char **ret, t_format form, int ilen);
t_ull				ft_inverse(t_ull n, char type, int neg);
t_ull				ft_cast_type(long long n, char type);

/*
** libft func
*/

char				*ft_strmcat(char *s1, char *s2, size_t n);

#endif
