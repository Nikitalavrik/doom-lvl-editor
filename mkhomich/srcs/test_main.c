/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 16:04:59 by nlavrine          #+#    #+#             */
/*   Updated: 2020/03/01 15:13:32 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

int main(int argc, char **argv)
{
	int running;
	Uint32 startclock;
	Uint32 deltaclock;
	t_doom doom;
//	char *fps;

	if (argc == 2)
		running = init_full(&doom, argv[argc - 1]);
	else
		running = init_full(&doom, NULL);
	if (NULL == doom.window || running == -1)
		exit (1);
	deltaclock = 1;
	while (running)
	{
		startclock = SDL_GetTicks();
		check_render(&doom);
		bzero_all(&doom);
		skybox(&doom);
		raycasting(&doom);
		print_mob(&doom);
		print_sp_sec(&doom);
		if (you_win(&doom) == 0)
			draw_text(&doom, doom.w * 0.43, doom.h * 0.2, "YOU WIN!!!");
		if (doom.play[doom.n_play].heart)
		{
			vec_pull(&doom);
			print_weapons(&doom);
			if (doom.play[doom.n_play].weapons == 6)
			{
				print_aim(&doom);
				calc_uron(&doom);
			}
			print_hud(&doom);
		}
		else
			draw_text(&doom, doom.w * 0.46, doom.h * 0.2, "DEAD");
		if (doom.nb % 4 == 0)
			doom.sp[1].count++;
		if (doom.nb % 1 == 0)
			doom.sp[17].count++;
		rec_net(&doom);
		running = move(&doom);
		game(&doom);
		jump_pl(&doom, doom.n_play, 0);
		doom.play[doom.n_play].shot = 8;
//        lava(&doom.text[9], &doom);
		if (doom.nb % 5 == 0)
			doom.skybox.count++;
		if (doom.skybox.count >= doom.skybox.size.w)
			doom.skybox.count = 0;

		if (doom.nb >= 80)
			doom.nb = 0;
		if (doom.nb % 10 == 0)
			doom.sp[12].count++;
		doom.nb++;
		deltaclock = SDL_GetTicks() - startclock;
		if (deltaclock < 1000 / FPS)
			SDL_Delay(1000 / FPS - deltaclock);
		deltaclock = SDL_GetTicks() - startclock;
		draw_text(&doom, 10, 10, doom.fps[1000 / deltaclock]);
		SDL_UpdateWindowSurface(doom.window);
	}
	system("leaks doom-nukem");
	SDL_DestroyWindow(doom.window);
	SDL_Quit();
	return (0);
}
