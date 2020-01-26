/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:25:31 by mkhomich          #+#    #+#             */
/*   Updated: 2020/01/26 16:31:58 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

void    init_sectors(t_doom *doom)
{
	int i;
	// load_map(doom);

	i = 0;
	while (i < doom->max_s)
	{
		grid_sec(doom, &doom->sec[i]);
		i++;
	}
	doom->z_buffer = (int*)malloc(sizeof(int) * WIDTH * HEIGHT);
}

void    init_minimap(t_doom *doom)
{
	doom->mmap.w = 200;
	doom->mmap.h = 200;
	doom->mmap.mmap = SDL_CreateRGBSurface(0,
										   doom->mmap.w, doom->mmap.h, 32, 0, 0, 0, 0);
}

void    init_player(t_doom *doom)
{
	doom->max_p = 4;
	doom->n_play = 0;
	doom->play = (t_play*)malloc(sizeof(t_play) * doom->max_p);
	doom->play[0].t.x = 10;
	doom->play[0].t.y = 20;
	doom->play[0].t.z = 10;
	doom->play[0].angle_x = 0;
	doom->play[0].angle_y = 270;
	doom->play[0].speed = 0.2f;
	doom->play[0].sp = 9;
	doom->play[0].weapons = 6;
	doom->play[0].heart = 34;
	doom->play[0].armor = 0;
	doom->play[0].count = 0;
	doom->play[0].f_move = 0;
	doom->play[0].shot = 8;
	doom->play[0].state = 0;
	doom->play[0].crouch = 0;
	doom->play[0].id = 0;
	doom->play[1].t.x = 190;
	doom->play[1].t.y = 5;
	doom->play[1].t.z = 10;
	doom->play[1].angle_x = 0;
	doom->play[1].angle_y = 90;
	doom->play[1].speed = 0.1f;
	doom->play[1].sp = 9;
	doom->play[1].weapons = 7;
	doom->play[1].heart = 34;
	doom->play[1].armor = 0;
	doom->play[1].count = 0;
	doom->play[1].f_move = 0;
	doom->play[1].shot = 8;
	doom->play[1].state = 0;
	doom->play[1].crouch = 0;
	doom->play[1].id = 1;
	doom->play[2].t.x = 190;
	doom->play[2].t.y = 5;
	doom->play[2].t.z = 190;
	doom->play[2].angle_x = 0;
	doom->play[2].angle_y = 90;
	doom->play[2].speed = 0.1f;
	doom->play[2].sp = 9;
	doom->play[2].weapons = 7;
	doom->play[2].heart = 34;
	doom->play[2].armor = 0;
	doom->play[2].count = 0;
	doom->play[2].f_move = 0;
	doom->play[2].shot = 8;
    doom->play[2].state = 0;
    doom->play[2].crouch = 0;
	doom->play[2].id = 2;
	doom->play[3].t.x = 10;
	doom->play[3].t.y = 5;
	doom->play[3].t.z = 190;
	doom->play[3].angle_x = 0;
	doom->play[3].angle_y = 270;
	doom->play[3].speed = 0.1f;
	doom->play[3].sp = 9;
	doom->play[3].weapons = 7;
	doom->play[3].heart = 34;
	doom->play[3].armor = 0;
	doom->play[3].count = 0;
	doom->play[3].f_move = 0;
	doom->play[3].shot = 8;
    doom->play[3].state = 0;
    doom->play[3].crouch = 0;
	doom->play[3].id = 3;
	doom->move.wsad[0] = 0;
	doom->move.wsad[1] = 0;
	doom->move.wsad[2] = 0;
	doom->move.wsad[3] = 0;
	doom->move.shot = 0;
	doom->move.mmap = 0;
	doom->move.jump = 0;
	doom->move.altern = 0;
}

void	init_music(t_doom *doom)
{
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 256);
	doom->muz.music = Mix_LoadMUS( "media/piople/Papa Roach - The Ending.ogg" );
	doom->muz.shot_pistol = Mix_LoadWAV( "media/piople/2.wav" );
}

void	init_pull(t_doom *doom)
{
	int nb;

	nb = 0;
	while (nb < MAX_PULL)
	{
		doom->pull[nb].status = 0;
		nb++;
	}
}

int 	init_full(t_doom *doom, char *str)
{
	doom->nb = 0;
	doom->soc.r = 0;
	doom->x_aim = IGRX;
	doom->y_aim = HEIGHT * 0.62;
	doom->gravity = 0.015;
	init_pull(doom);
	init_sectors(doom);
	if (ft_strcmp(str, "s") == 0 || str == NULL)
		init_player(doom);
	init_music(doom);
	doom->mult = 0;
	if (str)
		if (socket_init(doom, (*str == 's') ? 1 : ((*str == 'p') ? 2 : 0)) == 0)
			return (0);
	doom->play[doom->n_play].f_move = 0;
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	doom->window = SDL_CreateWindow("Hello SDL World",
									SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
									WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	init_skybox(doom);
	load_texture_wall(doom);
	doom->buff = (int*)malloc(sizeof(int) * 64);
	init_minimap(doom);
	if ((doom->l.ttf = TTF_OpenFont("../fonts/AmazDooMRight.ttf", 60)) == NULL)
		printf("xyi\n");
	doom->surface = SDL_GetWindowSurface(doom->window);
	Mix_PlayMusic( doom->muz.music, 0 );
	Mix_VolumeMusic(MIX_MAX_VOLUME / 8);
	return (1);
}