#include "minirt.h"

static int	hit_object(t_ray ray, t_object *obj, t_hit *hit)
{
	if (obj->type == OBJ_SPHERE)
		return (hit_sphere(ray, obj, hit));
	if (obj->type == OBJ_PLANE)
		return (hit_plane(ray, obj, hit));
	return (hit_cylinder(ray, obj, hit));
}

int	scene_closest_hit(t_scene *scene, t_ray ray, t_hit *hit)
{
	t_object	*obj;
	t_hit		tmp;
	int			found;

	found = 0;
	obj = scene->objects;
	while (obj)
	{
		if (hit_object(ray, obj, &tmp) && (!found || tmp.t < hit->t))
		{
			*hit = tmp;
			found = 1;
		}
		obj = obj->next;
	}
	return (found);
}

int	scene_any_hit(t_scene *scene, t_ray ray, double max_dist)
{
	t_object	*obj;
	t_hit		tmp;

	obj = scene->objects;
	while (obj)
	{
		if (hit_object(ray, obj, &tmp) && tmp.t < max_dist)
			return (1);
		obj = obj->next;
	}
	return (0);
}
