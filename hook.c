/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:26:23 by mberger-          #+#    #+#             */
/*   Updated: 2021/11/03 13:22:25 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	on_key_up(int key, t_mlx_data*mlx)
{
	if (key == 53 || key == 65307)
		clean_exit(mlx);
	return (1);
}

int	on_mouse_move(int x, int y, t_mlx_data *mlx)
{
	static int	first = 1;
	static int	last[2];

	if (first)
		first = 0;
	else
	{
		if (mlx->button == MIDDLE_MOUSE)
			mlx->pos = (t_vec2){
				mlx->pos.x + x - last[0],
				mlx->pos.y + y - last[1]
			};
		else if (mlx->button == LEFT_MOUSE)
			mlx->rot = create_rot(
					0,
					mlx->rot.y + ((float)x - (float)last[0]) / 100,
					mlx->rot.z + ((float)y - (float)last[1]) / 100
					);
		mlx_update(mlx);
	}
	last[0] = x;
	last[1] = y;
	return (1);
}

int	on_button_down(int button, int x, int y, t_mlx_data *mlx)
{
	(void)x;
	(void)y;
	mlx->button = button;
	if (button == 5)
		mlx->zoom /= .9;
	else if (button == 4)
		mlx->zoom *= .9;
	if (button == 4 || button == 5)
		mlx_update(mlx);
	return (1);
}

int	on_button_up(int button, int x, int y, t_mlx_data *mlx)
{
	(void)x;
	(void)y;
	(void)button;
	mlx->button = 0;
	return (1);
}
