/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:07:26 by mberger-          #+#    #+#             */
/*   Updated: 2021/11/02 14:07:28 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline void	setpix(t_mlx_data *mlx, int x, int y, int rgb)
{
	if (x < 0 || x >= mlx->width
		|| y < 0 || y >= mlx->height)
		return ;
	mlx->buf[x + y * mlx->width] = rgb;
}

static inline int	reduce(int *a)
{
	if (*a > 0)
		return ((*a)--);
	if (*a < 0)
		return ((*a)++);
	return (0);
}

void	mlx_draw_line(t_mlx_data *mlx, t_vec2 a, t_vec2 b, int rgb)
{
	int	dx;
	int	dy;

	dx = a.x - b.x;
	dy = a.y - b.y;
	if (dx == 0 && dy == 0)
		return ;
	if (abs(dx) > abs(dy))
		while (reduce(&dx))
			setpix(mlx, a.x - dx, (a.y - dy * dx / (a.x - b.x)), rgb);
	else
		while (reduce(&dy))
			setpix(mlx, a.x - dx * dy / (a.y - b.y), (a.y - dy), rgb);
}

int	mlx_rgbtoi(int r, int g, int b)
{
	return (
		((r & 255) << 16)
		| ((g & 255) << 8)
		| (b & 255)
	);
}

void	mlx_new_gradient(t_mlx_data *mlx)
{
	int	x;
	int	y;

	y = -1;
	while (++y < mlx->height)
	{
		x = -1;
		while (++x < mlx->width)
			mlx->buf[y * mlx->width + x] = mlx_rgbtoi(
					(float)x / (float)SIZE * 192.0f + 64,
					0,
					(float)y / (float)SIZE * 192.0f + 64);
	}
}
