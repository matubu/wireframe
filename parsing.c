/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:07:33 by mberger-          #+#    #+#             */
/*   Updated: 2021/11/02 14:08:13 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WIDTH 200
#define HEIGHT 200

void	mlx_parse_map(t_mlx_data *mlx, int argc, char **argv)
{
	int	x;
	int	y;
	int	map[WIDTH * HEIGHT];

	(void)argc;
	(void)argv;
	y = HEIGHT;
	while (y--)
	{
		x = WIDTH;
		while (x--)
			map[x + y * WIDTH] = (float)rand() / RAND_MAX * 20;
	}
	mlx->map.grid = map;
	mlx->map.size = (t_vec3){WIDTH, HEIGHT, max(WIDTH, HEIGHT)};
	mlx->map.off[0] = (mlx->map.size.z - mlx->map.size.x) / 2;
	mlx->map.off[1] = (mlx->map.size.z - mlx->map.size.y) / 2;
}
