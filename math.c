#include "fdf.h"

int	reduce(int *a)
{
	if (*a > 0)
		return ((*a)--);
	if (*a < 0)
		return ((*a)++);
	return (0);
}

int	min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

t_vec2	mlx_rotate(t_vec3 p, t_rot *r)
{
	t_vec2	vec;

	vec.x = p.x * r->matrix[0][0] + p.y * r->matrix[0][1] + p.z * 10 * r->matrix[0][2];
	vec.y = p.x * r->matrix[1][0] + p.y * r->matrix[1][1] + p.z * 10 * r->matrix[1][2];
	return (vec);
}

t_rot	create_rot(float x, float y, float z)
{
	t_rot	r;
	
	r.x = x;
	r.y = y;
	r.z = z;
	r.cx = cos(x);
	r.sx = sin(x);
	r.cy = cos(y);
	r.sy = sin(y);
	r.cz = cos(z);
	r.sz = sin(z);
	r.matrix[0][0] = r.cx * r.cy;
	r.matrix[0][1] = r.cx * r.sy * r.sz - r.sx * r.cz;
	r.matrix[0][2] = r.cx * r.sy * r.cz + r.sx * r.sz;
	r.matrix[1][0] = r.sx * r.cy;
	r.matrix[1][1] = r.sx * r.sy * r.sz + r.cx * r.cz;
	r.matrix[1][2] = r.sx * r.sy * r.cz - r.cx * r.sz;
	return (r);
}
