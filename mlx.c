/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:07:26 by mberger-          #+#    #+#             */
/*   Updated: 2021/11/03 10:45:37 by mberger-         ###   ########.fr       */
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

int	mix(const t_vec3 *a, const t_vec3 *b, float fac)
{
	float	inv;

	if (fac > 1.0)
		fac = 1.0;
	else if (fac < 0.0)
		fac = 0.0;
	inv = 1.0 - fac;
	return (rgb(
			(int)((float)a->x * fac + (float)b->x * inv),
		(int)((float)a->y * fac + (float)b->y * inv),
		(int)((float)a->z * fac + (float)b->z * inv)
		));
}

float	divz(float a, float b)
{
	if (b == 0)
		return (0);
	return (a / b);
}

void	mlx_draw_line(t_mlx_data *mlx, t_vec3 *a, t_vec3 *b)
{
	const t_vec3	from = {0xff, 0xc8, 0xcd};
	const t_vec3	to = {0x9c, 0x19, 0xcc};
	const t_vec3	d = {a->x - b->x, a->y - b->y, a->z - b->z};
	const float		fac[2] = {divz(d.x, d.z), divz(d.y, d.z)};
	t_vec2			p;

	p = (t_vec2){d.x, d.y};
	if ((p.x == 0 && p.y == 0)
		|| ((a->x < 0 || a->y < 0 || a->x >= mlx->width || a->y >= mlx->height)
			&& (b->x < 0 || b->y < 0
				|| b->x >= mlx->width || b->y >= mlx->height)))
		return ;
	if (abs(p.x) > abs(p.y))
		while (reduce(&p.x))
			setpix(mlx, a->x - p.x, (a->y - p.y * p.x / d.x),
				mix(&from, &to,
					(fac[0] * p.x + b->z - mlx->map.min) / mlx->map.range));
	else
		while (reduce(&p.y))
			setpix(mlx, a->x - p.x * p.y / d.y, (a->y - p.y),
				mix(&from, &to,
					(fac[1] * p.y + b->z - mlx->map.min) / mlx->map.range));
}

int	rgb(int r, int g, int b)
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
			mlx->buf[y * mlx->width + x] = rgb(
					(float)x / (float)SIZE * 192.0f + 64,
					0,
					(float)y / (float)SIZE * 192.0f + 64);
	}
}
