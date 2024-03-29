/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:50:06 by eewu              #+#    #+#             */
/*   Updated: 2024/02/05 11:41:23 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3d.h"

void	my_open(char *str, t_cub *cub)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		free(str);
		print_error_msg(PATH_FALSE, cub);
	}
	close(fd);
}

bool	check_for_dir(char *str, char *dir, t_cub *cub)
{
	int	i;

	i = 2;
	if (cub->ea != NULL && cub->no != NULL && cub->so != NULL
		&& cub->we != NULL)
	{
		free(str);
		print_error_msg(PATH_FALSE, cub);
	}
	if (ft_strncmp(str, dir, 2) == 0)
	{
		if (str[i] != ' ')
		{
			free(str);
			print_error_msg(PATH_FALSE, cub);
		}
		while (str[i] == ' ')
			i++;
		if (i != 2 && ft_strncmp(str + i, "./", 2))
			my_open(str + 3, cub);
		return (true);
	}
	return (false);
}

bool	check_for_textures(char *str, t_cub *cub)
{
	if (cub->no == NULL && check_for_dir(str, "NO", cub) == true)
		return (cub->no = ft_strdup(str + 3), true);
	else if (cub->so == NULL && check_for_dir(str, "SO", cub) == true)
		return (cub->so = ft_strdup(str + 3), true);
	else if (cub->we == NULL && check_for_dir(str, "WE", cub) == true)
		return (cub->we = ft_strdup(str + 3), true);
	else if (cub->ea == NULL && check_for_dir(str, "EA", cub) == true)
		return (cub->ea = ft_strdup(str + 3), true);
	return (false);
}
