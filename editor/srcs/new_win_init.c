/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_win_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 16:56:33 by tbratsla          #+#    #+#             */
/*   Updated: 2019/12/23 16:56:35 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	load_correct_scale_sprite(t_editor *editor)
{
	int i;

	i = 0;
	editor->new_win->editor_sprite = (t_sprite*)malloc(sizeof(t_sprite) * 7);
	while (i < 7)
	{
		editor->new_win->editor_sprite[i].text =\
		(t_text*)malloc(sizeof(t_text));
		i++;
	}
	editor->new_win->editor_sprite[0].text[0] =\
	convert_tex(IMG_Load("../sprite/monsters/people/walk/A1.png"), 128, 128);
	editor->new_win->editor_sprite[1].text[0] = convert_tex(\
	IMG_Load("../sprite/monsters/chargingdemon/walk/A1.bmp"), 128, 128);
	editor->new_win->editor_sprite[2].text[0] =\
	convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/A1.bmp"), 128, 128);
	editor->new_win->editor_sprite[3].text[0] =\
	convert_tex(IMG_Load("../sprite/BAR1B0.png"), 128, 128);
	editor->new_win->editor_sprite[4].text[0] =\
	convert_tex(IMG_Load("../sprite/armor.png"), 128, 128);
	editor->new_win->editor_sprite[5].text[0] =\
	convert_tex(IMG_Load("../sprite/medkit.png"), 128, 128);
	editor->new_win->editor_sprite[6].text[0] =\
	convert_tex(IMG_Load("../sprite/ammo.png"), 128, 128);
}

void	set_up_text(t_editor *editor, t_coord *coord)
{
	coord->x = editor->new_win->active_num.tex_num % 4 * 148 + 20;
	coord->y = editor->new_win->active_num.tex_num / 4 * 148 + 20;
	coord->x1 = coord->x + 128;
	coord->y1 = coord->y + 128;
}

void	init_new_win_param(t_editor *editor, void *param)
{
	editor->new_win->cam_y = 0;
	editor->new_win->delim_x = 148;
	editor->new_win->delim_y = 148;
	editor->new_win->events = ft_memalloc(sizeof(t_ev));
	editor->new_win->active_num.tex_num = -1;
	editor->new_win->ws_coord1 = get_input_coord(C_WIDTH + 210, 20);
	editor->new_win->ws_coord2 = get_input_coord(C_WIDTH + 210, 60);
	editor->new_win->ws_coord3 = get_input_coord(C_WIDTH + 210, 100);
	editor->new_win->ws_coord4 = get_input_coord(C_WIDTH + 210, 140);
	editor->new_win->param = param;
	editor->new_win->button_coord.x = C_WIDTH + 5;
	editor->new_win->button_coord.y = C_HEIGHT - 50;
	editor->new_win->button_coord.x1 = editor->new_win->button_coord.x + 300;
	editor->new_win->button_coord.y1 = editor->new_win->button_coord.y + 32;
}

void	create_new_win(t_editor *editor)
{
	int		i;

	i = 0;
	editor->new_win = ft_memalloc(sizeof(t_win));
	editor->new_win->win = SDL_CreateWindow("Textures",\
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 924, 712, 0);
	editor->new_win->sur = SDL_GetWindowSurface(editor->new_win->win);
	editor->new_win->win_id = SDL_GetWindowID(editor->new_win->win);
	if (editor->new_win->param_flag == 3)
		editor->new_win->mem_space = 612 * 712;
	else
		editor->new_win->mem_space = 148 * editor->doom->count_text / 4 + 20;
	editor->new_win->screen =\
	ft_memalloc(sizeof(Uint32 *) * editor->new_win->mem_space);
	while (i < editor->new_win->mem_space)
	{
		editor->new_win->screen[i] = ft_memalloc(sizeof(Uint32) * C_WIDTH);
		i++;
	}
}

void	new_win_init(t_editor *editor, void *param, int flag)
{
	create_new_win(editor);
	init_new_win_param(editor, param);
	if (flag == 1)
	{
		editor->new_win->param_par.line = (t_eline *)param;
		editor->new_win->active_num.tex_num =\
		editor->new_win->param_par.line->num_of_textures - 1;
		set_up_text(editor, &editor->new_win->active_num.coord);
	}
	else if (flag == 2)
	{
		editor->new_win->param_par.room = (t_room *)param;
		editor->new_win->active_num.tex_num =\
		editor->new_win->param_par.room->num_of_textures - 1;
		set_up_text(editor, &editor->new_win->active_num.coord);
	}
	else if (flag == 3)
	{
		editor->new_win->param_par.sprite = (t_esprite *)param;
		editor->new_win->active_num.tex_num =\
		editor->new_win->param_par.sprite->num_of_textures - 1;
		set_up_text(editor, &editor->new_win->active_num.coord);
	}
	editor->new_win->param_flag = flag;
	draw_right_menu(editor);
}
