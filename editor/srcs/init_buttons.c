/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_buttons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 19:12:03 by tbratsla          #+#    #+#             */
/*   Updated: 2020/01/23 19:12:04 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	init_emenu_buttons3(t_editor *editor)
{
	editor->menu.clear_lvl.x = editor->width - MENU_WIDTH + 10;
	editor->menu.clear_lvl.x1 = editor->menu.clear_lvl.x + 16;
	editor->menu.clear_lvl.y = 320;
	editor->menu.clear_lvl.y1 = editor->menu.clear_lvl.y + 16;
	editor->menu.yes_button.x = 10;
	editor->menu.yes_button.x1 = editor->menu.yes_button.x + 96;
	editor->menu.yes_button.y = 60;
	editor->menu.yes_button.y1 = editor->menu.yes_button.y + 32;
	editor->menu.no_button.x = 130;
	editor->menu.no_button.x1 = editor->menu.no_button.x + 94;
	editor->menu.no_button.y = 60;
	editor->menu.no_button.y1 = editor->menu.no_button.y + 32;

}

void	init_emenu_buttons2(t_editor *editor)
{
	editor->menu.first_floor.x = editor->width - MENU_WIDTH + 10;
	editor->menu.first_floor.x1 = editor->menu.first_floor.x + 16;
	editor->menu.first_floor.y = 230;
	editor->menu.first_floor.y1 = editor->menu.first_floor.y + 16;
	editor->menu.second_floor.x = editor->width - MENU_WIDTH + 10;
	editor->menu.second_floor.x1 = editor->menu.second_floor.x + 16;
	editor->menu.second_floor.y = 260;
	editor->menu.second_floor.y1 = editor->menu.second_floor.y + 16;
	editor->menu.third_floor.x = editor->width - MENU_WIDTH + 10;
	editor->menu.third_floor.x1 = editor->menu.third_floor.x + 16;
	editor->menu.third_floor.y = 290;
	editor->menu.third_floor.y1 = editor->menu.third_floor.y + 16;
	editor->menu.return_butt.x = editor->width - MENU_WIDTH + 10;
	editor->menu.return_butt.x1 = editor->width - 10;
	editor->menu.return_butt.y = editor->height - 40;
	editor->menu.return_butt.y1 = editor->menu.return_butt.y + 32;
	editor->menu.save_butt.x = editor->width - MENU_WIDTH + 10;
	editor->menu.save_butt.x1 = editor->width - 10;
	editor->menu.save_butt.y = editor->height - 75;
	editor->menu.save_butt.y1 = editor->menu.save_butt.y + 32;
	editor->menu.load_butt.x = editor->width - MENU_WIDTH + 10;
	editor->menu.load_butt.x1 = editor->width - 10;
	editor->menu.load_butt.y = editor->height - 110;
	editor->menu.load_butt.y1 = editor->menu.load_butt.y + 32;
	init_emenu_buttons3(editor);
}

void	init_emenu_buttons(t_editor *editor)
{
	editor->menu.f_cb_coord.x = editor->width - MENU_WIDTH + 10;
	editor->menu.f_cb_coord.x1 = editor->menu.f_cb_coord.x + 16;
	editor->menu.f_cb_coord.y = 80;
	editor->menu.f_cb_coord.y1 = editor->menu.f_cb_coord.y + 16;
	editor->menu.s_cb_coord.x = editor->width - MENU_WIDTH + 10;
	editor->menu.s_cb_coord.x1 = editor->menu.s_cb_coord.x + 16;
	editor->menu.s_cb_coord.y = 110;
	editor->menu.s_cb_coord.y1 = editor->menu.s_cb_coord.y + 16;
	editor->menu.t_cb_coord.x = editor->width - MENU_WIDTH + 10;
	editor->menu.t_cb_coord.x1 = editor->menu.t_cb_coord.x + 16;
	editor->menu.t_cb_coord.y = 140;
	editor->menu.t_cb_coord.y1 = editor->menu.t_cb_coord.y + 16;
	editor->menu.del_cb_coord.x = editor->width - MENU_WIDTH + 10;
	editor->menu.del_cb_coord.x1 = editor->menu.del_cb_coord.x + 16;
	editor->menu.del_cb_coord.y = 170;
	editor->menu.del_cb_coord.y1 = editor->menu.del_cb_coord.y + 16;
	editor->menu.clo_cb_coord.x = editor->width - MENU_WIDTH + 150;
	editor->menu.clo_cb_coord.x1 = editor->menu.clo_cb_coord.x + 16;
	editor->menu.clo_cb_coord.y = 80;
	editor->menu.clo_cb_coord.y1 = editor->menu.clo_cb_coord.y + 16;
	editor->menu.select_b.x = editor->width - MENU_WIDTH + 150;
	editor->menu.select_b.x1 = editor->menu.select_b.x + 16;
	editor->menu.select_b.y = 110;
	editor->menu.select_b.y1 = editor->menu.select_b.y + 16;
	init_emenu_buttons2(editor);
}
