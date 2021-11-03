/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:07:33 by mberger-          #+#    #+#             */
/*   Updated: 2021/11/03 11:59:52 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	err(int *allocated, char *msg)
{
	free(allocated);
	while (*msg)
		write(2, msg++, 1);
	exit(1);
}

void	mlx_map_size(t_map *map, int fd)
{
	char	buf;

	if (fd == -1)
		err(NULL, "could not open file\n");
	if (read(fd, &buf, 1) <= 0)
		err(NULL, "could not read file\n");
	map->size.y = 1;
	map->size.x = 0;
	while (buf != '\n')
	{
		if ((buf == '-' || (buf >= '0' && buf <= '9')) && ++map->size.x)
			while (read(fd, &buf, 1) > 0 && buf >= '0' && buf <= '9')
				;
		else if (buf == ' ')
		{
			if (read(fd, &buf, 1) <= 0)
				break ;
		}
		else
			err(NULL, "data not properly formatted\n");
	}
	while (read(fd, &buf, 1) > 0)
		if (buf == '\n')
			map->size.y++;
	map->size.z = map->size.x * map->size.y;
}

void	mlx_fill_map(t_map *map, int fd)
{
	int		i;
	char	buf;
	int		neg;

	i = 0;
	while (read(fd, &buf, 1) > 0)
	{
		neg = 0;
		if (buf == '-' || (buf >= '0' && buf <= '9'))
		{
			if (i >= map->size.z)
				err(map->grid, "unexpected number\n");
			if (buf == '-' && read(fd, &buf, 1) > 0)
				neg = 1;
			map->grid[i] = '0' - buf;
			while (read(fd, &buf, 1) > 0 && buf >= '0' && buf <= '9')
				map->grid[i] = map->grid[i] * 10 + '0' - buf;
			if (!neg)
				map->grid[i] = -map->grid[i];
			if (map->grid[i] > map->range || i == 0)
				map->range = map->grid[i];
			if (map->grid[i] < map->min || i == 0)
				map->min = map->grid[i];
			i++;
		}
	}
	map->range = max(map->range - map->min, 1);
}

void	mlx_parse_map(t_mlx_data *mlx, int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		err(NULL, "usage: ./fdf [filename]\n");
	fd = open(argv[1], O_RDONLY);
	mlx_map_size(&mlx->map, fd);
	close(fd);
	if (mlx->map.size.x == 0 || mlx->map.size.y == 0)
		err(NULL, "data not properly formatted\n");
	mlx->map.grid = (int *)malloc(sizeof(int)
			* mlx->map.size.x * mlx->map.size.y);
	if (mlx->map.grid == NULL)
		err(NULL, "could not malloc\n");
	fd = open(argv[1], O_RDONLY);
	mlx_fill_map(&mlx->map, fd);
	close(fd);
	mlx->map.size.z = max(mlx->map.size.x, mlx->map.size.y);
	mlx->map.off[0] = (mlx->map.size.z - mlx->map.size.x) / 2;
	mlx->map.off[1] = (mlx->map.size.z - mlx->map.size.y) / 2;
}
