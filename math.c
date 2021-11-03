/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:07:19 by mberger-          #+#    #+#             */
/*   Updated: 2021/11/03 08:02:28 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

t_vec3	*mlx_rotate(t_mlx_data *mlx, t_vec3 *p)
{
	float	d[3];

	d[0] = (((float)p->x + .5 + mlx->map.off[0]) / mlx->map.size.z - .5)
		* mlx->zoom;
	d[1] = (((float)p->y + .5 + mlx->map.off[1]) / mlx->map.size.z - .5)
		* mlx->zoom;
	d[2] = (((float)p->z + .5) / mlx->map.size.z / 10) * mlx->zoom;
	p->x = (d[0] * mlx->rot.matrix[0][0]
			+ d[1] * mlx->rot.matrix[0][1]
			+ d[2] * mlx->rot.matrix[0][2] + .5) * mlx->width + mlx->pos.x;
	p->y = (d[0] * mlx->rot.matrix[1][0]
			+ d[1] * mlx->rot.matrix[1][1]
			+ d[2] * mlx->rot.matrix[1][2] + .5) * mlx->height + mlx->pos.y;
	return (p);
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
	r.matrix[0][0] = r.cx * r.cy;
	r.matrix[0][1] = r.cx * r.sy * r.sz - r.sx * r.cz;
	r.matrix[0][2] = r.cx * r.sy * r.cz + r.sx * r.sz;
	r.matrix[1][0] = r.sx * r.cy;
	r.matrix[1][1] = r.sx * r.sy * r.sz + r.cx * r.cz;
	r.matrix[1][2] = r.sx * r.sy * r.cz - r.cx * r.sz;
	return (r);
}
