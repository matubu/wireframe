/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:07:06 by mberger-          #+#    #+#             */
/*   Updated: 2021/11/03 14:46:02 by mberger-         ###   ########.fr       */
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

void	mlx_project(t_mlx_data *mlx)
{
	t_vec2	pos;

	pos.y = mlx->map.size.y;
	while (pos.y--)
	{
		pos.x = mlx->map.size.x;
		while (--pos.x)
			mlx_draw_3d_line(mlx, pos, (t_vec2){pos.x - 1, pos.y});
	}
	pos.y = mlx->map.size.y;
	while (--pos.y)
	{
		pos.x = mlx->map.size.x;
		while (pos.x--)
			mlx_draw_3d_line(mlx, pos, (t_vec2){pos.x, pos.y - 1});
	}
}

void	mlx_update(t_mlx_data *mlx)
{
	mlx_new_gradient(mlx);
	mlx_project(mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
}

int	clean_exit(t_mlx_data *mlx)
{
	free(mlx->map.grid);
	mlx_destroy_window(mlx->ptr, mlx->win);
	exit(0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_mlx_data	mlx;
	int			null;

	mlx_parse_map(&mlx, argc, argv);
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
		clean_exit(&mlx);
	mlx.buf = (int *)mlx_get_data_addr(mlx.img, &null, &null, &null);
	mlx_hook(mlx.win, 3, 2, on_key_up, &mlx);
	mlx_init_camera(&mlx);
	mlx_update(&mlx);
	mlx_hook(mlx.win, 17, 0, clean_exit, &mlx);
	mlx_loop(mlx.ptr);
	return (0);
}
