/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:07:11 by mberger-          #+#    #+#             */
/*   Updated: 2021/11/03 14:33:30 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>

# define SIZE 800
# define PI 3.1415926535

typedef enum e_mouse {
	LEFT_MOUSE=1,
	MIDDLE_MOUSE=3
}	t_mouse;

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
	t_vec3	size;
	float	off[2];
	int		*grid;
	float	min;
	float	range;
}	t_map;

typedef struct s_mlx_data {
	void	*ptr;
	void	*win;
	void	*img;
	int		*buf;
	int		width;
	int		height;
	t_map	map;
	t_rot	rot;
	float	zoom;
	t_mouse	button;
	t_vec2	pos;
}	t_mlx_data;

int		reduce(int *a);
float	divz(float a, float b);
int		min(int a, int b);
int		max(int a, int b);

int		clean_exit(t_mlx_data *mlx);

int		rgb(int r, int g, int b);
void	init_rot(t_rot *r, float x, float y, float z);
void	mlx_draw_line(t_mlx_data *mlx, t_vec3 *a, t_vec3 *b);
void	mlx_new_gradient(t_mlx_data *mlx);

t_vec3	*mlx_rotate(t_mlx_data *mlx, t_vec3 *p);
void	mlx_update(t_mlx_data *mlx);
void	mlx_parse_map(t_mlx_data *mlx, int argc, char **argv);

int		on_key_up(int key, t_mlx_data *mlx);
int		on_mouse_move(int x, int y, t_mlx_data *mlx);
int		on_button_down(int button, int x, int y, t_mlx_data *mlx);
int		on_button_up(int button, int x, int y, t_mlx_data *mlx);

t_rot	create_rot(float x, float y, float z);
void	mlx_init_camera(t_mlx_data *mlx);

#endif
