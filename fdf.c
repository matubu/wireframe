/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:07:06 by mberger-          #+#    #+#             */
/*   Updated: 2021/11/02 14:07:07 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mlx_draw_3d_line(t_mlx_data *mlx, t_vec2 a, t_vec2 b)
{
	const t_vec3	a3 = {
		a.x, a.y,
		mlx->map.grid[a.x + a.y * mlx->map.size.x]
	};
	const t_vec3	b3 = {
		b.x, b.y,
		mlx->map.grid[b.x + b.y * mlx->map.size.x]
	};

	mlx_draw_line(mlx, mlx_rotate(mlx, a3), mlx_rotate(mlx, b3), 0x00dd88dd);
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
	mlx_destroy_window(mlx->ptr, mlx->win);
	exit(0);
	return (1);
}

int	on_esc(int key, t_mlx_data*mlx)
{
	if (key == 53 || key == 65307)
		clean_exit(mlx);
	return (1);
}

int	on_key_up(int key, t_mlx_data *mlx)
{
	if (key == 257)
		mlx->shift = 0;
	on_esc(key, mlx);
	return (1);
}

int	on_key_down(int key, t_mlx_data *mlx)
{
	if (key == 257)
		mlx->shift = 1;
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
		if (mlx->shift)
			mlx->pos = (t_vec2){mlx->pos.x + x - last[0], mlx->pos.y + y - last[1]};
		else
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


int	on_zoom(int button, int x, int y, t_mlx_data *mlx)
{
	(void)x;
	(void)y;
	if (button == 5)
		mlx->zoom /= .9;
	else if (button == 4)
		mlx->zoom *= .9;
	if (button == 4 || button == 5)
		mlx_update(mlx);
	return (1);
}

void	mlx_init_movement(t_mlx_data *mlx)
{
	mlx->shift = 0;
	mlx->pos = (t_vec2){0, 0};
	mlx->zoom = 1;
	mlx->rot = create_rot(1.57079 / 2, 0, 1.57079 / 2);
	mlx_hook(mlx->win, 2, 1, on_key_down, mlx);
	mlx_hook(mlx->win, 3, 2, on_key_up, mlx);
	mlx_mouse_hook(mlx->win, on_zoom, mlx);
	mlx_hook(mlx->win, 6, 64, on_mouse_move, mlx);
}

//TODO leaks ?
//TODO bus error
//TODO parsing
//TODO other projection with flag
//TODO color distance camera
int	main(int argc, char **argv)
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
		clean_exit(&mlx);
	mlx.buf = (int *)mlx_get_data_addr(mlx.img, &null, &null, &null);
	mlx_parse_map(&mlx, argc, argv);
	mlx_hook(mlx.win, 3, 2, on_esc, &mlx);
	mlx_init_movement(&mlx);
	mlx_update(&mlx);
	mlx_hook(mlx.win, 17, 0, clean_exit, &mlx);
	mlx_loop(mlx.ptr);
	return (0);
}
