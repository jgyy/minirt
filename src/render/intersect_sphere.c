#include "minirt.h"

static int	pick_root(double a, double b, double disc, double *t)
{
	double	sq;
	double	t0;
	double	t1;

	sq = sqrt(disc);
	t0 = (-b - sq) / (2.0 * a);
	t1 = (-b + sq) / (2.0 * a);
	if (t0 > EPSILON)
		*t = t0;
	else if (t1 > EPSILON)
		*t = t1;
	else
		return (0);
	return (1);
}

int	hit_sphere(t_ray ray, t_object *obj, t_hit *hit)
{
	t_vec3	oc;
	double	radius;
	double	a;
	double	b;
	double	c;
	double	disc;

	radius = obj->diameter / 2.0;
	oc = vec3_sub(ray.origin, obj->pos);
	a = vec3_dot(ray.dir, ray.dir);
	b = 2.0 * vec3_dot(oc, ray.dir);
	c = vec3_dot(oc, oc) - radius * radius;
	disc = b * b - 4.0 * a * c;
	if (disc < 0.0 || !pick_root(a, b, disc, &hit->t))
		return (0);
	hit->point = vec3_add(ray.origin, vec3_scale(ray.dir, hit->t));
	hit->normal = vec3_normalize(vec3_sub(hit->point, obj->pos));
	hit->color = obj->color;
	return (1);
}
