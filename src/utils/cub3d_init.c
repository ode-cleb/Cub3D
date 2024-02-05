/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:51:11 by eewu              #+#    #+#             */
/*   Updated: 2024/02/05 11:24:59 by ode-cleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3d.h"

static int	ft_init_texture(t_vars *vars)
{
	int		i;
	t_img	wall[4];

	i = 0;
	while (i < 4)
	{
		wall[i] = vars->wall[i];
		wall[i].img = mlx_xpm_file_to_image(vars->mlx, wall[i].path, &wall[i].h,
				&wall[i].w);
		if (!wall[i].img)
			ft_free_exit((printf("Erreur xpm[%d]\n", i)), vars);
		vars->wall[i] = wall[i];
		i++;
	}
	return (0);
}

void	ft_init_mlx(t_vars *vars, t_cub cub)
{
	int		m;
	t_img	img;

	m = mlx_get_screen_size(vars->mlx, &vars->sizex, &vars->sizey);
	vars->sizey -= 69;
	vars->win = mlx_new_window(vars->mlx, vars->sizex, vars->sizey, "Cub3D");
	if (vars->win == NULL)
		ft_free_mlx(vars);
	img.mlx_img = mlx_new_image(vars->mlx, vars->sizex, vars->sizey);
	if (img.mlx_img == NULL)
		ft_free_mlx(vars);
	img.addr = (int *)mlx_get_data_addr(img.mlx_img, &img.bpp, &img.llen,
			&img.endian);
	if (img.addr == NULL)
		ft_free_mlx(vars);
	vars->img = img;
	ft_memset(vars->wall, 0, sizeof(t_img) * 4);
	vars->wall[0].path = cub.no;
	vars->wall[1].path = cub.so;
	vars->wall[2].path = cub.ea;
	vars->wall[3].path = cub.we;
	vars->dir = cub.map->dir_player;
	vars->rx = 0;
	ft_init_texture(vars);
}
