/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:31:51 by mberger-          #+#    #+#             */
/*   Updated: 2021/11/03 13:32:00 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mlx_draw_3d_line(t_mlx_data *mlx, t_vec2 a, t_vec2 b)
{
	t_vec3	a3;
	t_vec3	b3;

	a3 = (t_vec3){
		a.x, a.y,
		mlx->map.grid[a.x + a.y * mlx->map.size.x]
	};
	b3 = (t_vec3){
		b.x, b.y,
		mlx->map.grid[b.x + b.y * mlx->map.size.x]
	};
	mlx_draw_line(mlx, mlx_rotate(mlx, &a3), mlx_rotate(mlx, &b3));
}
