/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:40:00 by mberger-          #+#    #+#             */
/*   Updated: 2021/11/03 14:31:35 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mlx_init_camera(t_mlx_data *mlx)
{
	mlx->button = 0;
	mlx->pos = (t_vec2){0, 0};
	mlx->zoom = 1;
	mlx->rot = create_rot(0, PI / 4, PI / 4);
	mlx_hook(mlx->win, 4, 1 << 2, on_button_down, mlx);
	mlx_hook(mlx->win, 5, 1 << 3, on_button_up, mlx);
	mlx_hook(mlx->win, 6, 64, on_mouse_move, mlx);
}

//https://en.wikipedia.org/wiki/Rotation_matrix
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
