#include "fdf.h"

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
