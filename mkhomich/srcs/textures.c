/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:35:19 by mkhomich          #+#    #+#             */
/*   Updated: 2020/02/16 16:28:59 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

void    load_tex_int(int *tex, SDL_Surface *surface, int w, int h)
{
    int x;
    int y;
    int *buf;

    y = 0;
    while (y < h)
    {
        x = 0;
        while (x < w)
        {
            buf = surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;
            tex[x + y * w] = *buf;
            x++;
        }
        y++;
    }
}

t_text    convert_tex(SDL_Surface *dst, int w, int h)
{
    t_text		res;
    SDL_Surface *src;

    if (w <= 0 || h <= 0)
	{
    	w = dst->w;
    	h = dst->h;
	}
    if (dst != NULL)
    {
		SDL_SetSurfaceBlendMode(dst, SDL_BLENDMODE_NONE);
        src = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_ARGB8888);
        SDL_BlitScaled(dst, NULL, src, NULL);
        SDL_FreeSurface(dst);
        res.tex = (int*)malloc(sizeof(int) * w * h);
        load_tex_int(res.tex, src, w, h);
		SDL_FreeSurface(src);
        res.w = w;
        res.h = h;
    }
    else
    	res.tex = 0;
    return (res);
}

void    save_text(t_doom *doom)
{
	int nb;
	int fd;
	int n;

	fd = open("texture.data", O_WRONLY|O_TRUNC|O_CREAT, 0666);
	if (fd > 0)
	{
		nb = 0;
		write(fd, &doom->count_text, sizeof(int));
		while (nb < doom->count_text)
		{
			write(fd, &doom->text[nb].w, sizeof(int));
			write(fd, &doom->text[nb].h, sizeof(int));
			write(fd, &doom->text[nb].tex[0], sizeof(int) * (doom->text[nb].w * doom->text[nb].h));
			nb++;
		}
		nb = 0;
		write(fd, &doom->count_sp, sizeof(int));
		while (nb < doom->count_sp)
		{
			write(fd, &doom->sp[nb], sizeof(t_sprite));
			n = 0;
			while (n < doom->sp[nb].frame)
			{
				write(fd, &doom->sp[nb].text[n].w, sizeof(int));
				write(fd, &doom->sp[nb].text[n].h, sizeof(int));
				write(fd, &doom->sp[nb].text[n].tex[0], sizeof(int) * (doom->sp[nb].text[n].w * doom->sp[nb].text[n].h));
				n++;
			}
			nb++;
		}
		close(fd);
	}
}

void    read_text(t_doom *doom, char *file)
{
	int fd;
	int nb;
	int n;

	fd = open(file, O_RDONLY);
	if (fd > 0)
	{
		read(fd, &doom->count_text, sizeof(int));
		doom->text = (t_text*)malloc(sizeof(t_text) * doom->count_text);
		nb = 0;
		while (nb < doom->count_text)
		{
			read(fd, &doom->text[nb].w, sizeof(int));
			read(fd, &doom->text[nb].h, sizeof(int));
			doom->text[nb].tex = (int*)malloc(sizeof(int) * (doom->text[nb].w * doom->text[nb].h));
			read(fd, &doom->text[nb].tex[0], sizeof(int) * (doom->text[nb].w * doom->text[nb].h));
			nb++;
		}
		nb = 0;
		read(fd, &doom->count_sp, sizeof(int));
		doom->sp = (t_sprite*)malloc(sizeof(t_sprite) * doom->count_sp);
		while (nb < doom->count_sp)
		{
			read(fd, &doom->sp[nb], sizeof(t_sprite));
			doom->sp[nb].text = (t_text*)malloc(sizeof(t_text) * doom->sp[nb].frame);
			n = 0;
			while (n < doom->sp[nb].frame)
			{
				read(fd, &doom->sp[nb].text[n].w, sizeof(int));
				read(fd, &doom->sp[nb].text[n].h, sizeof(int));
				doom->sp[nb].text[n].tex = (int*)malloc(sizeof(int) * (doom->sp[nb].text[n].w * doom->sp[nb].text[n].h));
				read(fd, &doom->sp[nb].text[n].tex[0], sizeof(int) * (doom->sp[nb].text[n].w * doom->sp[nb].text[n].h));
				n++;
			}
			nb++;
		}
		close(fd);
	}
}

void    load_texture_wall(t_doom *doom)
{
//		read_text(doom, "texture.data");
	doom->count_text = 32;
	doom->text = (t_text*)malloc(sizeof(t_text) * (doom->count_text + 1));
	doom->text[1] = convert_tex(IMG_Load("../text/1.bmp"), 128, 128);
	doom->text[2] = convert_tex(IMG_Load("../text/2.bmp"), 128, 128);
	doom->text[3] = convert_tex(IMG_Load("../text/3.bmp"), 128, 128);
	doom->text[4] = convert_tex(IMG_Load("../text/4.bmp"), 128, 128);
	doom->text[5] = convert_tex(IMG_Load("../text/5.bmp"), 128, 128);
	doom->text[6] = convert_tex(IMG_Load("../text/6.bmp"), 128, 128);
	doom->text[7] = convert_tex(IMG_Load("../text/7.bmp"), 128, 128);
	doom->text[8] = convert_tex(IMG_Load("../text/8.bmp"), 128, 128);
	doom->text[9] = convert_tex(IMG_Load("../text/9.bmp"), 128, 128);
	doom->text[10] = convert_tex(IMG_Load("../text/10.bmp"), 128, 128);
	doom->text[11] = convert_tex(IMG_Load("../text/11.bmp"), 128, 128);
	doom->text[12] = convert_tex(IMG_Load("../text/12.bmp"), 128, 128);
	doom->text[13] = convert_tex(IMG_Load("../text/13.bmp"), 128, 128);
	doom->text[14] = convert_tex(IMG_Load("../text/14.bmp"), 128, 128);
	doom->text[15] = convert_tex(IMG_Load("../text/15.bmp"), 128, 128);
	doom->text[16] = convert_tex(IMG_Load("../text/16.bmp"), 128, 128);
	doom->text[17] = convert_tex(IMG_Load("../text/17.bmp"), 128, 128);
	doom->text[18] = convert_tex(IMG_Load("../text/18.bmp"), 128, 128);
	doom->text[19] = convert_tex(IMG_Load("../text/19.bmp"), 128, 128);
	doom->text[20] = convert_tex(IMG_Load("../text/20.png"), 128, 128);
	doom->text[21] = convert_tex(IMG_Load("../text/Abenakiite.png"), 128, 128);
	doom->text[22] = convert_tex(IMG_Load("../text/Alabaster.png"), 128, 128);
	doom->text[23] = convert_tex(IMG_Load("../text/Alunite.png"), 128, 128);
	doom->text[24] = convert_tex(IMG_Load("../text/Andesite.png"), 128, 128);
	doom->text[25] = convert_tex(IMG_Load("../text/Anhydrite.png"), 128, 128);
	doom->text[26] = convert_tex(IMG_Load("../text/Anthracite.png"), 128, 128);
	doom->text[27] = convert_tex(IMG_Load("../text/Arsenic.png"), 128, 128);
	doom->text[28] = convert_tex(IMG_Load("../text/Asbestos.png"), 128, 128);
	doom->text[29] = convert_tex(IMG_Load("../text/AuriferousQuartz.png"), 128, 128);
	doom->text[30] = convert_tex(IMG_Load("../text/red_stained_glass.png"), 128, 128);
	doom->text[31] = convert_tex(IMG_Load("../text/0002.png"), 128, 128);
	doom->count_sp = 20;
	doom->sp = (t_sprite*)malloc(sizeof(t_sprite) * (doom->count_sp + 1));
	doom->sp[0].count = 0;
	doom->sp[0].frame = 1;
	doom->sp[0].zoom = ((float)doom->w / 11000);
	doom->sp[0].f_hud = 1;
	doom->sp[0].text = (t_text*)malloc(sizeof(t_text) * (doom->sp[0].frame + 1));
	doom->sp[0].text[0] = convert_tex(IMG_Load("../sprite/heart.png"), 0, 0);
	doom->sp[1].count = 0;
	doom->sp[1].frame = 20;
	doom->sp[1].zoom = ((float)doom->w / 3000);
	doom->sp[1].f_hud = 1;
	doom->sp[1].text = (t_text*)malloc(sizeof(t_text) * (doom->sp[1].frame + 1));
	doom->sp[1].text[0] = convert_tex(IMG_Load("../sprite/pulse/00.gif"), 0, 0);
	doom->sp[1].text[1] = convert_tex(IMG_Load("../sprite/pulse/01.gif"), 0, 0);
	doom->sp[1].text[2] = convert_tex(IMG_Load("../sprite/pulse/02.gif"), 0, 0);
	doom->sp[1].text[3] = convert_tex(IMG_Load("../sprite/pulse/03.gif"), 0, 0);
	doom->sp[1].text[4] = convert_tex(IMG_Load("../sprite/pulse/04.gif"), 0, 0);
	doom->sp[1].text[5] = convert_tex(IMG_Load("../sprite/pulse/05.gif"), 0, 0);
	doom->sp[1].text[6] = convert_tex(IMG_Load("../sprite/pulse/06.gif"), 0, 0);
	doom->sp[1].text[7] = convert_tex(IMG_Load("../sprite/pulse/07.gif"), 0, 0);
	doom->sp[1].text[8] = convert_tex(IMG_Load("../sprite/pulse/08.gif"), 0, 0);
	doom->sp[1].text[9] = convert_tex(IMG_Load("../sprite/pulse/09.gif"), 0, 0);
	doom->sp[1].text[10] = convert_tex(IMG_Load("../sprite/pulse/10.gif"), 0, 0);
	doom->sp[1].text[11] = convert_tex(IMG_Load("../sprite/pulse/11.gif"), 0, 0);
	doom->sp[1].text[12] = convert_tex(IMG_Load("../sprite/pulse/12.gif"), 0, 0);
	doom->sp[1].text[13] = convert_tex(IMG_Load("../sprite/pulse/13.gif"), 0, 0);
	doom->sp[1].text[14] = convert_tex(IMG_Load("../sprite/pulse/14.gif"), 0, 0);
	doom->sp[1].text[15] = convert_tex(IMG_Load("../sprite/pulse/15.gif"), 0, 0);
	doom->sp[1].text[16] = convert_tex(IMG_Load("../sprite/pulse/16.gif"), 0, 0);
	doom->sp[1].text[17] = convert_tex(IMG_Load("../sprite/pulse/17.gif"), 0, 0);
	doom->sp[1].text[18] = convert_tex(IMG_Load("../sprite/pulse/18.gif"), 0, 0);
	doom->sp[1].text[19] = convert_tex(IMG_Load("../sprite/pulse/19.gif"), 0, 0);
	doom->sp[2].count = 34;
	doom->sp[2].frame = 35;
	doom->sp[2].zoom = ((float)doom->w / 2000.0);
	doom->sp[2].f_hud = 1;
	doom->sp[2].text = (t_text*)malloc(sizeof(t_text) * (doom->sp[2].frame + 1));
	doom->sp[2].text[0] = convert_tex(IMG_Load("../sprite/procent_heart/00.gif"), 0, 0);
	doom->sp[2].text[1] = convert_tex(IMG_Load("../sprite/procent_heart/01.gif"), 0, 0);
	doom->sp[2].text[2] = convert_tex(IMG_Load("../sprite/procent_heart/02.gif"), 0, 0);
	doom->sp[2].text[3] = convert_tex(IMG_Load("../sprite/procent_heart/03.gif"), 0, 0);
	doom->sp[2].text[4] = convert_tex(IMG_Load("../sprite/procent_heart/04.gif"), 0, 0);
	doom->sp[2].text[5] = convert_tex(IMG_Load("../sprite/procent_heart/05.gif"), 0, 0);
	doom->sp[2].text[6] = convert_tex(IMG_Load("../sprite/procent_heart/06.gif"), 0, 0);
	doom->sp[2].text[7] = convert_tex(IMG_Load("../sprite/procent_heart/07.gif"), 0, 0);
	doom->sp[2].text[8] = convert_tex(IMG_Load("../sprite/procent_heart/08.gif"), 0, 0);
	doom->sp[2].text[9] = convert_tex(IMG_Load("../sprite/procent_heart/09.gif"), 0, 0);
	doom->sp[2].text[10] = convert_tex(IMG_Load("../sprite/procent_heart/10.gif"), 0, 0);
	doom->sp[2].text[11] = convert_tex(IMG_Load("../sprite/procent_heart/11.gif"), 0, 0);
	doom->sp[2].text[12] = convert_tex(IMG_Load("../sprite/procent_heart/12.gif"), 0, 0);
	doom->sp[2].text[13] = convert_tex(IMG_Load("../sprite/procent_heart/13.gif"), 0, 0);
	doom->sp[2].text[14] = convert_tex(IMG_Load("../sprite/procent_heart/14.gif"), 0, 0);
	doom->sp[2].text[15] = convert_tex(IMG_Load("../sprite/procent_heart/15.gif"), 0, 0);
	doom->sp[2].text[16] = convert_tex(IMG_Load("../sprite/procent_heart/16.gif"), 0, 0);
	doom->sp[2].text[17] = convert_tex(IMG_Load("../sprite/procent_heart/17.gif"), 0, 0);
	doom->sp[2].text[18] = convert_tex(IMG_Load("../sprite/procent_heart/18.gif"), 0, 0);
	doom->sp[2].text[19] = convert_tex(IMG_Load("../sprite/procent_heart/19.gif"), 0, 0);
	doom->sp[2].text[20] = convert_tex(IMG_Load("../sprite/procent_heart/20.gif"), 0, 0);
	doom->sp[2].text[21] = convert_tex(IMG_Load("../sprite/procent_heart/21.gif"), 0, 0);
	doom->sp[2].text[22] = convert_tex(IMG_Load("../sprite/procent_heart/22.gif"), 0, 0);
	doom->sp[2].text[23] = convert_tex(IMG_Load("../sprite/procent_heart/23.gif"), 0, 0);
	doom->sp[2].text[24] = convert_tex(IMG_Load("../sprite/procent_heart/24.gif"), 0, 0);
	doom->sp[2].text[25] = convert_tex(IMG_Load("../sprite/procent_heart/25.gif"), 0, 0);
	doom->sp[2].text[26] = convert_tex(IMG_Load("../sprite/procent_heart/26.gif"), 0, 0);
	doom->sp[2].text[27] = convert_tex(IMG_Load("../sprite/procent_heart/27.gif"), 0, 0);
	doom->sp[2].text[28] = convert_tex(IMG_Load("../sprite/procent_heart/28.gif"), 0, 0);
	doom->sp[2].text[29] = convert_tex(IMG_Load("../sprite/procent_heart/29.gif"), 0, 0);
	doom->sp[2].text[30] = convert_tex(IMG_Load("../sprite/procent_heart/30.gif"), 0, 0);
	doom->sp[2].text[31] = convert_tex(IMG_Load("../sprite/procent_heart/31.gif"), 0, 0);
	doom->sp[2].text[32] = convert_tex(IMG_Load("../sprite/procent_heart/32.gif"), 0, 0);
	doom->sp[2].text[33] = convert_tex(IMG_Load("../sprite/procent_heart/33.gif"), 0, 0);
	doom->sp[2].text[34] = convert_tex(IMG_Load("../sprite/procent_heart/34.gif"), 0, 0);
	doom->sp[3].count = 0;
	doom->sp[3].frame = 1;
	doom->sp[3].zoom = ((float)doom->w / 7000);
	doom->sp[3].f_hud = 1;
	doom->sp[3].text = (t_text*)malloc(sizeof(t_text) * (doom->sp[3].frame + 1));
	doom->sp[3].text[0] = convert_tex(IMG_Load("../sprite/armor.png"), 0, 0);
	doom->sp[4].count = 34;
	doom->sp[4].frame = 35;
	doom->sp[4].zoom = ((float)doom->w / 1000.0);;
	doom->sp[4].f_hud = 1;
	doom->sp[4].text = (t_text*)malloc(sizeof(t_text) * (doom->sp[4].frame + 1));
	doom->sp[4].text[0] = convert_tex(IMG_Load("../sprite/procent_armor/00.gif"), 0, 0);
	doom->sp[4].text[1] = convert_tex(IMG_Load("../sprite/procent_armor/01.gif"), 0, 0);
	doom->sp[4].text[2] = convert_tex(IMG_Load("../sprite/procent_armor/02.gif"), 0, 0);
	doom->sp[4].text[3] = convert_tex(IMG_Load("../sprite/procent_armor/03.gif"), 0, 0);
	doom->sp[4].text[4] = convert_tex(IMG_Load("../sprite/procent_armor/04.gif"), 0, 0);
	doom->sp[4].text[5] = convert_tex(IMG_Load("../sprite/procent_armor/05.gif"), 0, 0);
	doom->sp[4].text[6] = convert_tex(IMG_Load("../sprite/procent_armor/06.gif"), 0, 0);
	doom->sp[4].text[7] = convert_tex(IMG_Load("../sprite/procent_armor/07.gif"), 0, 0);
	doom->sp[4].text[8] = convert_tex(IMG_Load("../sprite/procent_armor/08.gif"), 0, 0);
	doom->sp[4].text[9] = convert_tex(IMG_Load("../sprite/procent_armor/09.gif"), 0, 0);
	doom->sp[4].text[10] = convert_tex(IMG_Load("../sprite/procent_armor/10.gif"), 0, 0);
	doom->sp[4].text[11] = convert_tex(IMG_Load("../sprite/procent_armor/11.gif"), 0, 0);
	doom->sp[4].text[12] = convert_tex(IMG_Load("../sprite/procent_armor/12.gif"), 0, 0);
	doom->sp[4].text[13] = convert_tex(IMG_Load("../sprite/procent_armor/13.gif"), 0, 0);
	doom->sp[4].text[14] = convert_tex(IMG_Load("../sprite/procent_armor/14.gif"), 0, 0);
	doom->sp[4].text[15] = convert_tex(IMG_Load("../sprite/procent_armor/15.gif"), 0, 0);
	doom->sp[4].text[16] = convert_tex(IMG_Load("../sprite/procent_armor/16.gif"), 0, 0);
	doom->sp[4].text[17] = convert_tex(IMG_Load("../sprite/procent_armor/17.gif"), 0, 0);
	doom->sp[4].text[18] = convert_tex(IMG_Load("../sprite/procent_armor/18.gif"), 0, 0);
	doom->sp[4].text[19] = convert_tex(IMG_Load("../sprite/procent_armor/19.gif"), 0, 0);
	doom->sp[4].text[20] = convert_tex(IMG_Load("../sprite/procent_armor/20.gif"), 0, 0);
	doom->sp[4].text[21] = convert_tex(IMG_Load("../sprite/procent_armor/21.gif"), 0, 0);
	doom->sp[4].text[22] = convert_tex(IMG_Load("../sprite/procent_armor/22.gif"), 0, 0);
	doom->sp[4].text[23] = convert_tex(IMG_Load("../sprite/procent_armor/23.gif"), 0, 0);
	doom->sp[4].text[24] = convert_tex(IMG_Load("../sprite/procent_armor/24.gif"), 0, 0);
	doom->sp[4].text[25] = convert_tex(IMG_Load("../sprite/procent_armor/25.gif"), 0, 0);
	doom->sp[4].text[26] = convert_tex(IMG_Load("../sprite/procent_armor/26.gif"), 0, 0);
	doom->sp[4].text[27] = convert_tex(IMG_Load("../sprite/procent_armor/27.gif"), 0, 0);
	doom->sp[4].text[28] = convert_tex(IMG_Load("../sprite/procent_armor/28.gif"), 0, 0);
	doom->sp[4].text[29] = convert_tex(IMG_Load("../sprite/procent_armor/29.gif"), 0, 0);
	doom->sp[4].text[30] = convert_tex(IMG_Load("../sprite/procent_armor/30.gif"), 0, 0);
	doom->sp[4].text[31] = convert_tex(IMG_Load("../sprite/procent_armor/31.gif"), 0, 0);
	doom->sp[4].text[32] = convert_tex(IMG_Load("../sprite/procent_armor/32.gif"), 0, 0);
	doom->sp[4].text[33] = convert_tex(IMG_Load("../sprite/procent_armor/33.gif"), 0, 0);
	doom->sp[4].text[34] = convert_tex(IMG_Load("../sprite/procent_armor/34.gif"), 0, 0);
	doom->sp[5].count = 7;
	doom->sp[5].frame = 8;
	doom->sp[5].zoom = ((float)doom->w / 3000);
	doom->sp[5].f_hud = 1;
	doom->sp[5].text = (t_text*)malloc(sizeof(t_text) * (doom->sp[5].frame + 1));
	doom->sp[5].text[0] = convert_tex(IMG_Load("../sprite/procent_shot/00.gif"), 0, 0);
	doom->sp[5].text[1] = convert_tex(IMG_Load("../sprite/procent_shot/01.gif"), 0, 0);
	doom->sp[5].text[2] = convert_tex(IMG_Load("../sprite/procent_shot/02.gif"), 0, 0);
	doom->sp[5].text[3] = convert_tex(IMG_Load("../sprite/procent_shot/03.gif"), 0, 0);
	doom->sp[5].text[4] = convert_tex(IMG_Load("../sprite/procent_shot/04.gif"), 0, 0);
	doom->sp[5].text[5] = convert_tex(IMG_Load("../sprite/procent_shot/05.gif"), 0, 0);
	doom->sp[5].text[6] = convert_tex(IMG_Load("../sprite/procent_shot/06.gif"), 0, 0);
	doom->sp[5].text[7] = convert_tex(IMG_Load("../sprite/procent_shot/07.gif"), 0, 0);
	doom->sp[6].count = 0;
	doom->sp[6].frame = 7;
	doom->sp[6].zoom = ((float)doom->w / 450);
	doom->sp[6].f_hud = 1;
	doom->sp[6].text = (t_text*)malloc(sizeof(t_text) * (doom->sp[6].frame + 1));
	doom->sp[6].text[0] = convert_tex(IMG_Load("../sprite/weapons/pistol_1/1.png"), 0, 0);
	doom->sp[6].text[1] = convert_tex(IMG_Load("../sprite/weapons/pistol_1/2.png"), 0, 0);
	doom->sp[6].text[2] = convert_tex(IMG_Load("../sprite/weapons/pistol_1/3.png"), 0, 0);
	doom->sp[6].text[3] = convert_tex(IMG_Load("../sprite/weapons/pistol_1/4.png"), 0, 0);
	doom->sp[6].text[4] = convert_tex(IMG_Load("../sprite/weapons/pistol_1/5.png"), 0, 0);
	doom->sp[6].text[5] = convert_tex(IMG_Load("../sprite/weapons/pistol_1/6.png"), 0, 0);
	doom->sp[6].text[6] = convert_tex(IMG_Load("../sprite/weapons/pistol_1/7.png"), 0, 0);
	doom->sp[7].count = 0;
	doom->sp[7].frame = 27;
	doom->sp[7].zoom = ((float)doom->w / 450);
	doom->sp[7].f_hud = 1;
	doom->sp[7].text = (t_text*)malloc(sizeof(t_text) * (doom->sp[4].frame + 1));
	doom->sp[7].text[0] = convert_tex(IMG_Load("../sprite/weapons/grenade/0.png"), 0, 0);
	doom->sp[7].text[1] = convert_tex(IMG_Load("../sprite/weapons/grenade/1.png"), 0, 0);
	doom->sp[7].text[2] = convert_tex(IMG_Load("../sprite/weapons/grenade/2.png"), 0, 0);
	doom->sp[7].text[3] = convert_tex(IMG_Load("../sprite/weapons/grenade/3.png"), 0, 0);
	doom->sp[7].text[4] = convert_tex(IMG_Load("../sprite/weapons/grenade/4.png"), 0, 0);
	doom->sp[7].text[5] = convert_tex(IMG_Load("../sprite/weapons/grenade/5.png"), 0, 0);
	doom->sp[7].text[6] = convert_tex(IMG_Load("../sprite/weapons/grenade/6.png"), 0, 0);
	doom->sp[7].text[7] = convert_tex(IMG_Load("../sprite/weapons/grenade/7.png"), 0, 0);
	doom->sp[7].text[8] = convert_tex(IMG_Load("../sprite/weapons/grenade/8.png"), 0, 0);
	doom->sp[7].text[9] = convert_tex(IMG_Load("../sprite/weapons/grenade/9.png"), 0, 0);
	doom->sp[7].text[10] = convert_tex(IMG_Load("../sprite/weapons/grenade/10.png"), 0, 0);
	doom->sp[7].text[11] = convert_tex(IMG_Load("../sprite/weapons/grenade/11.png"), 0, 0);
	doom->sp[7].text[12] = convert_tex(IMG_Load("../sprite/weapons/grenade/12.png"), 0, 0);
	doom->sp[7].text[13] = convert_tex(IMG_Load("../sprite/weapons/grenade/13.png"), 0, 0);
	doom->sp[7].text[14] = convert_tex(IMG_Load("../sprite/weapons/grenade/14.png"), 0, 0);
	doom->sp[7].text[15] = convert_tex(IMG_Load("../sprite/weapons/grenade/15.png"), 0, 0);
	doom->sp[7].text[16] = convert_tex(IMG_Load("../sprite/weapons/grenade/16.png"), 0, 0);
	doom->sp[7].text[17] = convert_tex(IMG_Load("../sprite/weapons/grenade/17.png"), 0, 0);
	doom->sp[7].text[18] = convert_tex(IMG_Load("../sprite/weapons/grenade/18.png"), 0, 0);
	doom->sp[7].text[19] = convert_tex(IMG_Load("../sprite/weapons/grenade/19.png"), 0, 0);
	doom->sp[7].text[20] = convert_tex(IMG_Load("../sprite/weapons/grenade/20.png"), 0, 0);
	doom->sp[7].text[21] = convert_tex(IMG_Load("../sprite/weapons/grenade/21.png"), 0, 0);
	doom->sp[7].text[22] = convert_tex(IMG_Load("../sprite/weapons/grenade/22.png"), 0, 0);
	doom->sp[7].text[23] = convert_tex(IMG_Load("../sprite/weapons/grenade/23.png"), 0, 0);
	doom->sp[7].text[24] = convert_tex(IMG_Load("../sprite/weapons/grenade/24.png"), 0, 0);
	doom->sp[7].text[25] = convert_tex(IMG_Load("../sprite/weapons/grenade/25.png"), 0, 0);
	doom->sp[7].text[26] = convert_tex(IMG_Load("../sprite/weapons/grenade/26.png"), 0, 0);
	doom->sp[8].count = 0;
	doom->sp[8].frame = 15;
	doom->sp[8].zoom = ((float)doom->w / 500);
	doom->sp[8].f_hud = 1;
	doom->sp[8].text = (t_text*)malloc(sizeof(t_text) * (doom->sp[8].frame + 1));
	doom->sp[8].text[0] = convert_tex(IMG_Load("../sprite/weapons/blaster/A.bmp"), 0, 0);
	doom->sp[8].text[1] = convert_tex(IMG_Load("../sprite/weapons/blaster/B.bmp"), 0, 0);
	doom->sp[8].text[2] = convert_tex(IMG_Load("../sprite/weapons/blaster/C.bmp"), 0, 0);
	doom->sp[8].text[3] = convert_tex(IMG_Load("../sprite/weapons/blaster/D.bmp"), 0, 0);
	doom->sp[8].text[4] = convert_tex(IMG_Load("../sprite/weapons/blaster/E.bmp"), 0, 0);
	doom->sp[8].text[5] = convert_tex(IMG_Load("../sprite/weapons/blaster/F.bmp"), 0, 0);
	doom->sp[8].text[6] = convert_tex(IMG_Load("../sprite/weapons/blaster/G.bmp"), 0, 0);
	doom->sp[8].text[7] = convert_tex(IMG_Load("../sprite/weapons/blaster/H.bmp"), 0, 0);
	doom->sp[8].text[8] = convert_tex(IMG_Load("../sprite/weapons/blaster/I.bmp"), 0, 0);
	doom->sp[8].text[9] = convert_tex(IMG_Load("../sprite/weapons/blaster/J.bmp"), 0, 0);
	doom->sp[8].text[10] = convert_tex(IMG_Load("../sprite/weapons/blaster/K.bmp"), 0, 0);
	doom->sp[8].text[11] = convert_tex(IMG_Load("../sprite/weapons/blaster/L.bmp"), 0, 0);
	doom->sp[8].text[12] = convert_tex(IMG_Load("../sprite/weapons/blaster/M.bmp"), 0, 0);
	doom->sp[8].text[13] = convert_tex(IMG_Load("../sprite/weapons/blaster/N.bmp"), 0, 0);
	doom->sp[8].text[14] = convert_tex(IMG_Load("../sprite/weapons/blaster/O.bmp"), 0, 0);
	doom->sp[9].count = 0;
	doom->sp[9].frame = 41;
	doom->sp[9].zoom = 0.1;
	doom->sp[9].f_hud = 0;
	doom->sp[9].text = (t_text*)malloc(sizeof(t_text) * (doom->sp[9].frame + 1));
	doom->sp[9].text[0] = convert_tex(IMG_Load("../sprite/monsters/people/walk/A1.png"), 0, 0);
	doom->sp[9].text[1] = convert_tex(IMG_Load("../sprite/monsters/people/walk/B1.png"), 0, 0);
	doom->sp[9].text[2] = convert_tex(IMG_Load("../sprite/monsters/people/walk/C1.png"), 0, 0);
	doom->sp[9].text[3] = convert_tex(IMG_Load("../sprite/monsters/people/walk/D1.png"), 0, 0);
	doom->sp[9].text[4] = convert_tex(IMG_Load("../sprite/monsters/people/walk/A2.png"), 0, 0);
	doom->sp[9].text[5] = convert_tex(IMG_Load("../sprite/monsters/people/walk/B2.png"), 0, 0);
	doom->sp[9].text[6] = convert_tex(IMG_Load("../sprite/monsters/people/walk/C2.png"), 0, 0);
	doom->sp[9].text[7] = convert_tex(IMG_Load("../sprite/monsters/people/walk/D2.png"), 0, 0);
	doom->sp[9].text[8] = convert_tex(IMG_Load("../sprite/monsters/people/walk/A3.png"), 0, 0);
	doom->sp[9].text[9] = convert_tex(IMG_Load("../sprite/monsters/people/walk/B3.png"), 0, 0);
	doom->sp[9].text[10] = convert_tex(IMG_Load("../sprite/monsters/people/walk/C3.png"), 0, 0);
	doom->sp[9].text[11] = convert_tex(IMG_Load("../sprite/monsters/people/walk/D3.png"), 0, 0);
	doom->sp[9].text[12] = convert_tex(IMG_Load("../sprite/monsters/people/walk/A4.png"), 0, 0);
	doom->sp[9].text[13] = convert_tex(IMG_Load("../sprite/monsters/people/walk/B4.png"), 0, 0);
	doom->sp[9].text[14] = convert_tex(IMG_Load("../sprite/monsters/people/walk/C4.png"), 0, 0);
	doom->sp[9].text[15] = convert_tex(IMG_Load("../sprite/monsters/people/walk/D4.png"), 0, 0);
	doom->sp[9].text[16] = convert_tex(IMG_Load("../sprite/monsters/people/walk/A5.png"), 0, 0);
	doom->sp[9].text[17] = convert_tex(IMG_Load("../sprite/monsters/people/walk/B5.png"), 0, 0);
	doom->sp[9].text[18] = convert_tex(IMG_Load("../sprite/monsters/people/walk/C5.png"), 0, 0);
	doom->sp[9].text[19] = convert_tex(IMG_Load("../sprite/monsters/people/walk/D5.png"), 0, 0);
	doom->sp[9].text[20] = convert_tex(IMG_Load("../sprite/monsters/people/walk/A6.png"), 0, 0);
	doom->sp[9].text[21] = convert_tex(IMG_Load("../sprite/monsters/people/walk/B6.png"), 0, 0);
	doom->sp[9].text[22] = convert_tex(IMG_Load("../sprite/monsters/people/walk/C6.png"), 0, 0);
	doom->sp[9].text[23] = convert_tex(IMG_Load("../sprite/monsters/people/walk/D6.png"), 0, 0);
	doom->sp[9].text[24] = convert_tex(IMG_Load("../sprite/monsters/people/walk/A7.png"), 0, 0);
	doom->sp[9].text[25] = convert_tex(IMG_Load("../sprite/monsters/people/walk/B7.png"), 0, 0);
	doom->sp[9].text[26] = convert_tex(IMG_Load("../sprite/monsters/people/walk/C7.png"), 0, 0);
	doom->sp[9].text[27] = convert_tex(IMG_Load("../sprite/monsters/people/walk/D7.png"), 0, 0);
	doom->sp[9].text[28] = convert_tex(IMG_Load("../sprite/monsters/people/walk/A8.png"), 0, 0);
	doom->sp[9].text[29] = convert_tex(IMG_Load("../sprite/monsters/people/walk/B8.png"), 0, 0);
	doom->sp[9].text[30] = convert_tex(IMG_Load("../sprite/monsters/people/walk/C8.png"), 0, 0);
	doom->sp[9].text[31] = convert_tex(IMG_Load("../sprite/monsters/people/walk/D8.png"), 0, 0);
	doom->sp[9].text[32] = convert_tex(IMG_Load("../sprite/monsters/people/attack/E1.png"), 0, 0);
	doom->sp[9].text[33] = convert_tex(IMG_Load("../sprite/monsters/people/attack/F1.png"), 0, 0);
	doom->sp[9].text[34] = convert_tex(IMG_Load("../sprite/monsters/people/attack/G1.png"), 0, 0);
	doom->sp[9].text[35] = convert_tex(IMG_Load("../sprite/monsters/people/death/I0.png"), 0, 0);
	doom->sp[9].text[36] = convert_tex(IMG_Load("../sprite/monsters/people/death/J0.png"), 0, 0);
	doom->sp[9].text[37] = convert_tex(IMG_Load("../sprite/monsters/people/death/K0.png"), 0, 0);
	doom->sp[9].text[38] = convert_tex(IMG_Load("../sprite/monsters/people/death/L0.png"), 0, 0);
	doom->sp[9].text[39] = convert_tex(IMG_Load("../sprite/monsters/people/death/M0.png"), 0, 0);
	doom->sp[9].text[40] = convert_tex(IMG_Load("../sprite/monsters/people/death/N0.png"), 0, 0);
	doom->sp[10].count = 0;
	doom->sp[10].frame = 41;
	doom->sp[10].zoom = 1;
	doom->sp[10].f_hud = 0;
	doom->sp[10].text = (t_text*)malloc(sizeof(t_text) * (doom->sp[10].frame + 1));
	doom->sp[10].text[0] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/A1.bmp"), 0, 0);
	doom->sp[10].text[1] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/B1.bmp"), 0, 0);
	doom->sp[10].text[2] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/C1.bmp"), 0, 0);
	doom->sp[10].text[3] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/D1.bmp"), 0, 0);
	doom->sp[10].text[4] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/A2.bmp"), 0, 0);
	doom->sp[10].text[5] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/B2.bmp"), 0, 0);
	doom->sp[10].text[6] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/C2.bmp"), 0, 0);
	doom->sp[10].text[7] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/D2.bmp"), 0, 0);
	doom->sp[10].text[8] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/A3.bmp"), 0, 0);
	doom->sp[10].text[9] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/B3.bmp"), 0, 0);
	doom->sp[10].text[10] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/C3.bmp"), 0, 0);
	doom->sp[10].text[11] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/D3.bmp"), 0, 0);
	doom->sp[10].text[12] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/A4.bmp"), 0, 0);
	doom->sp[10].text[13] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/B4.bmp"), 0, 0);
	doom->sp[10].text[14] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/C4.bmp"), 0, 0);
	doom->sp[10].text[15] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/D4.bmp"), 0, 0);
	doom->sp[10].text[16] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/A5.bmp"), 0, 0);
	doom->sp[10].text[17] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/B5.bmp"), 0, 0);
	doom->sp[10].text[18] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/C5.bmp"), 0, 0);
	doom->sp[10].text[19] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/D5.bmp"), 0, 0);
	doom->sp[10].text[20] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/A6.png"), 0, 0);
	doom->sp[10].text[21] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/B6.png"), 0, 0);
	doom->sp[10].text[22] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/C6.png"), 0, 0);
	doom->sp[10].text[23] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/D6.png"), 0, 0);
	doom->sp[10].text[24] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/A7.png"), 0, 0);
	doom->sp[10].text[25] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/B7.png"), 0, 0);
	doom->sp[10].text[26] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/C7.png"), 0, 0);
	doom->sp[10].text[27] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/D7.png"), 0, 0);
	doom->sp[10].text[28] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/A8.png"), 0, 0);
	doom->sp[10].text[29] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/B8.png"), 0, 0);
	doom->sp[10].text[30] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/C8.png"), 0, 0);
	doom->sp[10].text[31] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/walk/D8.png"), 0, 0);
	doom->sp[10].text[32] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/attack/E1.bmp"), 0, 0);
	doom->sp[10].text[33] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/attack/F1.bmp"), 0, 0);
	doom->sp[10].text[34] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/attack/G1.bmp"), 0, 0);
	doom->sp[10].text[35] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/death/I0.bmp"), 0, 0);
	doom->sp[10].text[36] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/death/J0.bmp"), 0, 0);
	doom->sp[10].text[37] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/death/K0.bmp"), 0, 0);
	doom->sp[10].text[38] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/death/L0.bmp"), 0, 0);
	doom->sp[10].text[39] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/death/M0.bmp"), 0, 0);
	doom->sp[10].text[40] = convert_tex(IMG_Load("../sprite/monsters/chargingdemon/death/N0.bmp"), 0, 0);
	doom->sp[11].count = 0;
	doom->sp[11].frame = 41;
	doom->sp[11].zoom = 1;
	doom->sp[11].f_hud = 0;
	doom->sp[11].text = (t_text*)malloc(sizeof(t_text) * (doom->sp[11].frame + 1));
	doom->sp[11].text[0] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/A1.bmp"), 0, 0);
	doom->sp[11].text[1] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/B1.bmp"), 0, 0);
	doom->sp[11].text[2] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/C1.bmp"), 0, 0);
	doom->sp[11].text[3] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/D1.bmp"), 0, 0);
	doom->sp[11].text[4] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/A2.bmp"), 0, 0);
	doom->sp[11].text[5] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/B2.bmp"), 0, 0);
	doom->sp[11].text[6] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/C2.bmp"), 0, 0);
	doom->sp[11].text[7] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/D2.bmp"), 0, 0);
	doom->sp[11].text[8] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/A3.bmp"), 0, 0);
	doom->sp[11].text[9] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/B3.bmp"), 0, 0);
	doom->sp[11].text[10] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/C3.bmp"), 0, 0);
	doom->sp[11].text[11] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/D3.bmp"), 0, 0);
	doom->sp[11].text[12] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/A4.bmp"), 0, 0);
	doom->sp[11].text[13] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/B4.bmp"), 0, 0);
	doom->sp[11].text[14] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/C4.bmp"), 0, 0);
	doom->sp[11].text[15] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/D4.bmp"), 0, 0);
	doom->sp[11].text[16] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/A5.bmp"), 0, 0);
	doom->sp[11].text[17] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/B5.bmp"), 0, 0);
	doom->sp[11].text[18] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/C5.bmp"), 0, 0);
	doom->sp[11].text[19] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/D5.bmp"), 0, 0);
	doom->sp[11].text[20] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/A6.png"), 0, 0);
	doom->sp[11].text[21] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/B6.png"), 0, 0);
	doom->sp[11].text[22] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/C6.png"), 0, 0);
	doom->sp[11].text[23] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/D6.png"), 0, 0);
	doom->sp[11].text[24] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/A7.png"), 0, 0);
	doom->sp[11].text[25] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/B7.png"), 0, 0);
	doom->sp[11].text[26] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/C7.png"), 0, 0);
	doom->sp[11].text[27] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/D7.png"), 0, 0);
	doom->sp[11].text[28] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/A8.png"), 0, 0);
	doom->sp[11].text[29] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/B8.png"), 0, 0);
	doom->sp[11].text[30] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/C8.png"), 0, 0);
	doom->sp[11].text[31] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/walk/D8.png"), 0, 0);
	doom->sp[11].text[32] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/attack/E1.bmp"), 0, 0);
	doom->sp[11].text[33] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/attack/F1.bmp"), 0, 0);
	doom->sp[11].text[34] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/attack/G1.bmp"), 0, 0);
	doom->sp[11].text[35] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/death/I0.bmp"), 0, 0);
	doom->sp[11].text[36] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/death/J0.bmp"), 0, 0);
	doom->sp[11].text[37] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/death/K0.bmp"), 0, 0);
	doom->sp[11].text[38] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/death/L0.bmp"), 0, 0);
	doom->sp[11].text[39] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/death/M0.bmp"), 0, 0);
	doom->sp[11].text[40] = convert_tex(IMG_Load("../sprite/monsters/motherdemon/death/N0.bmp"), 0, 0);
	doom->sp[12].count = 0;
	doom->sp[12].frame = 12;
	doom->sp[12].zoom = 1;
	doom->sp[12].f_hud = 0;
	doom->sp[12].text = (t_text*)malloc(sizeof(t_text) * (doom->sp[12].frame + 1));
	doom->sp[12].text[0] = convert_tex(IMG_Load("../sprite/BAR1B0.png"), 0, 0);
	doom->sp[12].text[1] = convert_tex(IMG_Load("../sprite/BAR1C0.png"), 0, 0);
	doom->sp[12].text[2] = convert_tex(IMG_Load("../sprite/BAR1D0.png"), 0, 0);
	doom->sp[12].text[3] = convert_tex(IMG_Load("../sprite/BAR1E0.png"), 0, 0);
	doom->sp[12].text[4] = convert_tex(IMG_Load("../sprite/BAR1F0.png"), 0, 0);
	doom->sp[12].text[5] = convert_tex(IMG_Load("../sprite/BAR1G0.png"), 0, 0);
	doom->sp[12].text[6] = convert_tex(IMG_Load("../sprite/BAR1H0.png"), 0, 0);
	doom->sp[12].text[7] = convert_tex(IMG_Load("../sprite/BAR1I0.png"), 0, 0);
	doom->sp[12].text[8] = convert_tex(IMG_Load("../sprite/BAR1J0.png"), 0, 0);
	doom->sp[12].text[9] = convert_tex(IMG_Load("../sprite/BAR1K0.png"), 0, 0);
	doom->sp[12].text[10] = convert_tex(IMG_Load("../sprite/BAR1L0.png"), 0, 0);
	doom->sp[12].text[11] = convert_tex(IMG_Load("../sprite/BAR1M0.png"), 0, 0);
	doom->sp[13].count = 0;
	doom->sp[13].frame = 1;
	doom->sp[13].zoom = 0.15;
	doom->sp[13].f_hud = 1;
	doom->sp[13].text = (t_text*)malloc(sizeof(t_text) * (doom->sp[13].frame + 1));
	doom->sp[13].text[0] = convert_tex(IMG_Load("../sprite/armor.png"), 0, 0);
	doom->sp[14].count = 0;
	doom->sp[14].frame = 1;
	doom->sp[14].zoom = 0.15;
	doom->sp[14].f_hud = 1;
	doom->sp[14].text = (t_text*)malloc(sizeof(t_text) * (doom->sp[14].frame + 1));
	doom->sp[14].text[0] = convert_tex(IMG_Load("../sprite/medkit.png"), 0, 0);
    doom->sp[15].count = 0;
    doom->sp[15].frame = 1;
    doom->sp[15].zoom = 1;
    doom->sp[15].f_hud = 1;
    doom->sp[15].text = (t_text*)malloc(sizeof(t_text) * (doom->sp[15].frame + 1));
    doom->sp[15].text[0] = convert_tex(IMG_Load("../sprite/ammo.png"), 0, 0);
	doom->sp[16].count = 0;
	doom->sp[16].frame = 4;
	doom->sp[16].zoom = 2.2;
	doom->sp[16].f_hud = 1;
	doom->sp[16].text = (t_text*)malloc(sizeof(t_text) * (doom->sp[16].frame + 1));
	doom->sp[16].text[0] = convert_tex(IMG_Load("../sprite/weapons/pistol_1/8.png"), 0, 0);
	doom->sp[16].text[1] = convert_tex(IMG_Load("../sprite/weapons/pistol_1/9.png"), 0, 0);
	doom->sp[16].text[2] = convert_tex(IMG_Load("../sprite/weapons/pistol_1/10.png"), 0, 0);
	doom->sp[16].text[3] = convert_tex(IMG_Load("../sprite/weapons/pistol_1/11.png"), 0, 0);
	doom->sp[17].count = 0;
	doom->sp[17].frame = 2;
	doom->sp[17].f_hud = 1;
	doom->sp[17].text = (t_text*)malloc(sizeof(t_text) * (doom->sp[17].frame + 1));
	doom->sp[17].text[0] = convert_tex(IMG_Load("../sprite/weapons/blaster/BFS1A0.png"), 0, 0);
	doom->sp[17].text[1] = convert_tex(IMG_Load("../sprite/weapons/blaster/BFS1B0.png"), 0, 0);
	doom->sp[18].count = 0;
	doom->sp[18].frame = 7;
	doom->sp[18].f_hud = 1;
	doom->sp[18].text = (t_text*)malloc(sizeof(t_text) * (doom->sp[18].frame + 1));
	doom->sp[18].text[0] = convert_tex(IMG_Load("../sprite/weapons/blaster/BFGba0.png"), 0, 0);
	doom->sp[18].text[1] = convert_tex(IMG_Load("../sprite/weapons/blaster/BFGbb0.png"), 0, 0);
	doom->sp[18].text[2] = convert_tex(IMG_Load("../sprite/weapons/blaster/BFGbc0.png"), 0, 0);
	doom->sp[18].text[3] = convert_tex(IMG_Load("../sprite/weapons/blaster/BFGbd0.png"), 0, 0);
	doom->sp[18].text[4] = convert_tex(IMG_Load("../sprite/weapons/blaster/BFGbe0.png"), 0, 0);
	doom->sp[18].text[5] = convert_tex(IMG_Load("../sprite/weapons/blaster/BFGbf0.png"), 0, 0);
	doom->sp[18].text[6] = convert_tex(IMG_Load("../sprite/weapons/blaster/BFGbg0.png"), 0, 0);
    doom->sp[19].count = 0;
    doom->sp[19].frame = 4;
    doom->sp[19].f_hud = 0;
    doom->sp[19].text = (t_text*)malloc(sizeof(t_text) * (doom->sp[19].frame + 1));
    doom->sp[19].text[0] = convert_tex(IMG_Load("../sprite/TLMPA0.png"), 0, 0);
    doom->sp[19].text[1] = convert_tex(IMG_Load("../sprite/TLMPB0.png"), 0, 0);
    doom->sp[19].text[2] = convert_tex(IMG_Load("../sprite/TLMPC0.png"), 0, 0);
    doom->sp[19].text[3] = convert_tex(IMG_Load("../sprite/TLMPD0.png"), 0, 0);
//	save_text(doom);
}