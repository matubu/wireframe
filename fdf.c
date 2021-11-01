/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:05:47 by mberger-          #+#    #+#             */
/*   Updated: 2021/11/01 15:30:54 by matubu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mlx.h>
#include <math.h>

#define SIZE 800
//#define PI 3.14159265358979323846
//#define PI2 PI * 2

typedef struct s_vec2 {
	int	x;
	int	y;
}	t_vec2;

typedef struct s_vec3 {
	int	x;
	int	y;
	int	z;
}	t_vec3;

typedef struct s_map {
	t_vec2	size;
	t_vec2	off;
	int		*grid;
	int		block;
}	t_map;

typedef struct s_mlx_data {
	void	*ptr;
	void	*win;
	void	*img;
	int		*buf;
	int		width;
	int		height;
	t_map	map;
}	t_mlx_data;

typedef struct s_rot {
	float	x;
	float	y;
	float	z;
	float	cx;
	float	sx;
	float	cy;
	float	sy;
	float	cz;
	float	sz;
	t_vec3	matrix[2];
}	t_rot;

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
			mlx->buf[(a.x - dx)
				+ (a.y - dy * dx / (a.x - b.x)) * mlx->width] = rgb;
	else
		while (reduce(&dy))
			mlx->buf[(a.x - dx * dy / (a.y - b.y))
				+ (a.y - dy) * mlx->width] = rgb;
}

int	mlx_rgbtoi(int r, int g, int b)
{
	return (
		((r & 255) << 16)
		| ((g & 255) << 8)
		| (b & 255)
	);
}

int	map[4 * 4] = {
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

int	min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

t_vec2	mlx_rotate(t_vec3 p, t_rot *r)
{
	t_vec2	vec;

	vec.x = p.x * r->matrix[0].x + p.y * r->matrix[0].y + p.z * r->matrix[0].z;
	vec.y = p.x * r->matrix[1].x + p.y * r->matrix[1].y + p.z * r->matrix[1].z;
	return (vec);
}

void	mlx_draw_3d_line(t_mlx_data *mlx, t_rot *rot, t_vec2 a, t_vec2 b)
{
	const t_vec3	a3 = {
		a.x * mlx->map.block + mlx->map.off.x,
		a.y * mlx->map.block + mlx->map.off.y,
		mlx->map.grid[a.x + a.y * mlx->map.size.x]
	};
	const t_vec3	b3 = {
		b.x * mlx->map.block + mlx->map.off.x,
		b.y * mlx->map.block + mlx->map.off.y,
		mlx->map.grid[b.x + b.y * mlx->map.size.x]
	};

	mlx_draw_line(mlx, mlx_rotate(a3, rot), mlx_rotate(b3, rot), 0x00dd88dd);
}

void	mlx_project(t_mlx_data *mlx, t_rot rot)
{
	t_vec2	pos;

	pos.y = mlx->map.size.y;
	while (pos.y--)
	{
		pos.x = mlx->map.size.x;
		while (--pos.x)
			mlx_draw_3d_line(mlx, &rot, pos, (t_vec2){pos.x - 1, pos.y});
	}
	pos.y = mlx->map.size.y;
	while (--pos.y)
	{
		pos.x = mlx->map.size.x;
		while (pos.x--)
			mlx_draw_3d_line(mlx, &rot, pos, (t_vec2){pos.x, pos.y - 1});
	}

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

void	mlx_init_map(t_mlx_data *mlx, int *map, int width, int height)
{
	mlx->map.grid = map;
	mlx->map.size = (t_vec2){width, height};
	mlx->map.block = min(mlx->width / width, mlx->height / height);
	mlx->map.off.x = mlx->width / width / 2;
	mlx->map.off.y = mlx->height / height / 2;
}

t_rot	create_rot(float x, float y, float z)
{
	t_rot	r;
	
	r.x = x;
	r.y = y;
	r.z = z;
	r.cx = cos(x);
	r.sx = sin(x);
	r.cy = cos(y);
	r.sy = sin(y);
	r.cz = cos(z);
	r.sz = sin(z);
	r.matrix[0] = (t_vec3){
		r.cx * r.cy,
		r.cx * r.sy * r.sz - r.sx * r.cz,
		r.cx * r.sy * r.cz + r.sx * r.sz};
	r.matrix[1] = (t_vec3){
		r.sx * r.cy,
		r.sx * r.sy * r.sz + r.cx * r.cz,
		r.sx * r.sy * r.cz - r.cx * r.sz};
	return (r);
}

//TODO leaks ? exit properly on close
int	main(void)
{
	t_mlx_data	mlx;
	int			null;

	mlx.ptr = mlx_init();
	if (mlx.ptr == NULL)
		return (1);
	mlx.width = SIZE;
	mlx.height = SIZE;
	mlx.win = mlx_new_window(mlx.ptr, mlx.width, mlx.height, "FDF");
	if (mlx.win == NULL)
		return (1);
	mlx.img = mlx_new_image(mlx.ptr, mlx.width, mlx.height);
	if (mlx.img == NULL)
	{
		mlx_destroy_window(mlx.ptr, mlx.win);
		return (1);
	}
	mlx.buf = (int *)mlx_get_data_addr(mlx.img, &null, &null, &null);
	mlx_new_gradient(&mlx);
	mlx_init_map(&mlx, map, 4, 4);
	mlx_project(&mlx, create_rot(0.0001, 0, 0));
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.ptr);
	return (0);
}
