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

#include "includes/doom.h"

void	rewrite_font(t_l *l)
{
	TTF_CloseFont(l->ttf);
	get_font_size(l);
	l->ttf = TTF_OpenFont("font/AmazDooMRight.ttf", l->font_size);
}

void	load_text_font(t_l *l)
{
	get_font_size(l);
	l->texture[1] = IMG_Load("img/1.bmp");
	l->texture[3] = IMG_Load("img/3.bmp");
	l->texture[5] = IMG_Load("img/01.png");
	l->texture[6] = IMG_Load("img/02.png");
	l->texture[7] = IMG_Load("img/55.png");
	l->texture[2] = IMG_Load("img/photoeditorsdk-export.bmp");
	l->texture[4] = IMG_Load("img/11.jpeg");
	l->ttf = TTF_OpenFont("font/AmazDooMRight.ttf", l->font_size);
}

int		main(void)
{
	t_l	*l;

	// printf("dfjhhdjfkdl\n");
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	l = (t_l*)malloc(sizeof(t_l));
	l->text_color = (SDL_Color){80, 10, 10, 0};
	l->m.flag_mus = 0;
	l->m.flag_soun = 0;
	l->m.flag_cont = 0;
	l->m.f_run = 0;
	l->m.f_diffic = 0;
	l->f_mult = 0;
	l->m.f_ser = 0;
	l->f_numpl = 0;
	l->m.num_play = 0;
	l->m.f_play = 0;
	level_edit(l);
	return (0);
}
