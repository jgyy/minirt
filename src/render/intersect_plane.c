#include "minirt.h"

int	hit_plane(t_ray ray, t_object *obj, t_hit *hit)
{
	double	denom;
	double	t;

	denom = vec3_dot(obj->normal, ray.dir);
	if (fabs(denom) < EPSILON)
		return (0);
	t = vec3_dot(vec3_sub(obj->pos, ray.origin), obj->normal) / denom;
	if (t <= EPSILON)
		return (0);
	hit->t = t;
	hit->point = vec3_add(ray.origin, vec3_scale(ray.dir, t));
	if (denom > 0.0)
		hit->normal = vec3_scale(obj->normal, -1.0);
	else
		hit->normal = obj->normal;
	hit->color = obj->color;
	return (1);
}
