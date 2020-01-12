/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_managment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:56:57 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/29 18:11:44 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	null_editing_flags(t_flags *flags)
{
	flags->t_f.line = 0;
	flags->t_f.select = 0;
	flags->t_f.floor = 0;
	flags->t_f.sprite = 0;
}