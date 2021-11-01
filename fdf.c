#include "fdf.h"

int	map[5 * 5] = {
	0,	0,	0,	0,	5,
	0,	10,	20,	0,	0,
	0,	10,	-5,	0,	0,
	0,	10,	-5,	0,	0,
	0,	0,	0,	0,	0
};

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

void	mlx_init_map(t_mlx_data *mlx, int *map, int width, int height)
{
	mlx->map.grid = map;
	mlx->map.size = (t_vec2){width, height};
	mlx->map.block = min(mlx->width / width, mlx->height / height);
	mlx->map.off.x = mlx->width / width / 2;
	mlx->map.off.y = mlx->height / height / 2;
}

int	on_key_press(int key, t_mlx_data *mlx)
{
	if (key == 65307)
	{
		mlx_destroy_window(mlx->ptr, mlx->win);
		exit(0);
	}
	return (0);
}

int	on_mouse_move(int x, int y, t_mlx_data *mlx)
{
	mlx->buf[x + y * mlx->width] = 0x00ffffff;
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	return (0);
}

//TODO leaks ? exit properly on close
//TODO use float between -.5 and .5 for position of point for center rotation
//TODO parsing
//TODO bonus (translate (shift middle mouse move) + rotate (middle mouse move))
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
	mlx_init_map(&mlx, map, 5, 5);
	mlx_project(&mlx, create_rot(.2, .2, 1));
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
	mlx_key_hook(mlx.win, on_key_press, (void *)&mlx);
	mlx_hook(mlx.win, 6, 64, on_mouse_move, (void *)&mlx);
	mlx_loop(mlx.ptr);
	return (0);
}
