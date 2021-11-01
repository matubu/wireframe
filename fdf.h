#ifndef FDF_H
# define FDF_h

#include <stdlib.h>
#include <mlx.h>
#include <math.h>

# define SIZE 800

typedef struct s_vec2 {
	int	x;
	int	y;
}	t_vec2;

typedef struct s_vec3 {
	int	x;
	int	y;
	int	z;
}	t_vec3;

typedef struct s_rot {
	float	x;
	float	y;
	float	z;
	float	cx;
	float	sx;
	float	cy;
	float	sy;
	float	cz;
	float	sz;
	float	matrix[2][3];
}	t_rot;

typedef struct s_map {
	t_vec2	size;
	t_vec2	off;
	int		*grid;
	int		block;
}	t_map;

typedef struct s_mlx_data {
	void	*ptr;
	void	*win;
	void	*img;
	int		*buf;
	int		width;
	int		height;
	t_map	map;
}	t_mlx_data;

int		min(int a, int b);
int		reduce(int *a);
t_rot	create_rot(float x, float y, float z);
int		mlx_rgbtoi(int r, int g, int b);
t_vec2	mlx_rotate(t_vec3 p, t_rot *r);
void	mlx_draw_line(t_mlx_data *mlx, t_vec2 a, t_vec2 b, int rgb);
void	mlx_new_gradient(t_mlx_data *mlx);

#endif
