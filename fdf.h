/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:07:11 by mberger-          #+#    #+#             */
/*   Updated: 2021/11/02 14:07:13 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

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
	t_vec3	size;
	float	off[2];
	int		*grid;
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
	int		shift;
	t_vec2	pos;
}	t_mlx_data;

int		min(int a, int b);
int		max(int a, int b);
t_rot	create_rot(float x, float y, float z);
int		mlx_rgbtoi(int r, int g, int b);
t_vec2	mlx_rotate(t_mlx_data *mlx, t_vec3 p);
void	mlx_draw_line(t_mlx_data *mlx, t_vec2 a, t_vec2 b, int rgb);
void	mlx_new_gradient(t_mlx_data *mlx);
void	mlx_parse_map(t_mlx_data *mlx, int argc, char **argv);
int		clean_exit(t_mlx_data *mlx);

#endif
