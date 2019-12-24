/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   butons.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 18:06:40 by tbahlai           #+#    #+#             */
/*   Updated: 2019/08/28 18:06:40 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	event(t_l *l)
{
	Uint32 *p;

	p = (Uint32*)l->sur->pixels;
	if ((l->event.key.type == SDL_KEYDOWN &&
		l->event.key.keysym.sym == SDLK_ESCAPE)
		|| l->event.type == SDL_QUIT)
		exit(1);
}
