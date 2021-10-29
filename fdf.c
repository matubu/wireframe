/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:05:47 by mberger-          #+#    #+#             */
/*   Updated: 2021/10/29 18:07:47 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mlx.h>
#include <math.h>

#define SIZE 800

typedef struct s_vec2 {
	int	x;
	int	y;
}	t_vec2;

typedef struct s_vec3 {
	int	x;
	int	y;
	int	z;
}	t_vec3;

typedef struct s_mlx_data {
	void	*ptr;
	void	*win;
}	t_mlx_data;

int	reduce(int *a)
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
			mlx_pixel_put(mlx->ptr, mlx->win,
					a.x - dx,
					a.y - dy * dx / (a.x - b.x),
					rgb);
	else
		while (reduce(&dy))
			mlx_pixel_put(mlx->ptr, mlx->win,
					a.x - dx * dy / (a.y - b.y),
					a.y - dy,
					rgb);
}

int	mlx_rgbtoi(int r, int g, int b)
{
	return (
		((r & 255) << 16)
		| ((g & 255) << 8)
		| (b & 255)
	);
}

const int	map[4 * 4] = {
	0,	0,	0,	0,
	0,	10,	10,	0,
	0,	10,	0,	0,
	0,	0,	0,	0
};

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	mlx_draw_3d_line(t_mlx_data *mlx, t_vec3 rot, t_vec3 a, t_vec3 b)
{
	(void)rot;
	mlx_draw_line(mlx, (t_vec2){a.x + a.z, a.y - a.z * 5}, (t_vec2){b.x + b.z, b.y - b.z * 5}, 0x00FFFFFF);
}

void	mlx_project(t_mlx_data *mlx, int *map, t_vec2 map_size, t_vec3 rot)
{
	t_vec2	pos;
	t_vec2	off;
	int		block_size;

	block_size = SIZE / max(map_size.x, map_size.y);
	off.x = SIZE / map_size.x / 2;
	off.y = SIZE / map_size.y / 2;

	pos.y = map_size.y;
	while (pos.y--)
	{
		pos.x = map_size.x;
		while (--pos.x)
			mlx_draw_3d_line(mlx,
					rot,
					(t_vec3){
						pos.x * block_size + off.x,
						pos.y * block_size + off.y,
						map[pos.y * map_size.x + pos.x]
						},
					(t_vec3){
						(pos.x - 1) * block_size + off.x,
						pos.y * block_size + off.y,
						map[pos.y * map_size.x + pos.x - 1]
						});
	}

	pos.y = map_size.y;
	while (--pos.y)
	{
		pos.x = map_size.x;
		while (pos.x--)
			mlx_draw_3d_line(mlx,
					rot,
					(t_vec3){
						pos.x * block_size + off.x,
						pos.y * block_size + off.y,
						map[pos.y * map_size.x + pos.x]
						},
					(t_vec3){
						pos.x * block_size + off.x,
						(pos.y - 1) * block_size + off.y,
						map[pos.y * map_size.x + pos.x - map_size.x]
						});
	}

}

int	main(void)
{
	t_mlx_data	mlx;
	int			x;
	int			y;

	mlx.ptr = mlx_init();
	if (mlx.ptr == NULL)
		return (1);
	mlx.win = mlx_new_window(mlx.ptr, SIZE, SIZE, "FDF");
	if (mlx.win == NULL)
		return (1);
	y = -1;
	while (++y < SIZE)
	{
		x = -1;
		while (++x < SIZE)
			mlx_pixel_put(mlx.ptr, mlx.win, x, y, mlx_rgbtoi(
					(float)x / (float)SIZE * 192.0f + 64,
					0,
					(float)y / (float)SIZE * 192.0f + 64));
	}
	//mlx_draw_line(&mlx, (t_vec2){10, 100}, (t_vec2){10, 10}, 0x00FFFFFF);
	mlx_project(&mlx, (int *)map, (t_vec2){4, 4}, (t_vec3){0, 0, 0});
	mlx_loop(mlx.ptr);
	return (0);
}
