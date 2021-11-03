/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:39:51 by mberger-          #+#    #+#             */
/*   Updated: 2021/11/03 14:29:46 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mlx_init_camera(t_mlx_data *mlx)
{
	mlx->pos = (t_vec2){0, 0};
	mlx->zoom = 1;
	mlx->rot = create_rot(0, PI / 4, PI / 4);
}

//https://en.wikipedia.org/wiki/Isometric_projection
t_rot	create_rot(float x, float y, float z)
{
	t_rot		r;
	const float	oo6s = 1 / sqrt(6);

	(void)x;
	(void)y;
	(void)z;
	r.matrix[0][0] = oo6s * sqrt(3);
	r.matrix[0][1] = 0;
	r.matrix[0][2] = oo6s * -sqrt(3);
	r.matrix[1][0] = oo6s * 1;
	r.matrix[1][1] = oo6s * 2;
	r.matrix[1][2] = oo6s * 1;
	return (r);
}
