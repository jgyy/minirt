#include "minirt.h"

static double	shadow_factor(t_scene *scene, t_hit *hit, t_vec3 light_dir,
		double light_dist)
{
	t_ray	shadow_ray;

	shadow_ray.origin = vec3_add(hit->point, vec3_scale(hit->normal, EPSILON));
	shadow_ray.dir = light_dir;
	if (scene_any_hit(scene, shadow_ray, light_dist - EPSILON))
		return (0.0);
	return (1.0);
}

static double	specular_term(t_scene *scene, t_ray ray, t_hit *hit,
		t_vec3 light_dir, double visible)
{
	t_vec3	reflect_dir;
	t_vec3	view_dir;
	double	spec_angle;

	if (visible <= 0.0)
		return (0.0);
	view_dir = vec3_scale(ray.dir, -1.0);
	reflect_dir = vec3_normalize(vec3_reflect(
				vec3_scale(light_dir, -1.0), hit->normal));
	spec_angle = vec3_dot(reflect_dir, view_dir);
	if (spec_angle <= 0.0)
		return (0.0);
	return (scene->light.ratio * pow(spec_angle, 32.0));
}

t_color	shade_hit(t_scene *scene, t_ray ray, t_hit *hit)
{
	t_vec3	light_dir;
	double	light_dist;
	double	diffuse;
	double	visible;
	double	spec;
	t_color	out;

	light_dir = vec3_sub(scene->light.pos, hit->point);
	light_dist = vec3_length(light_dir);
	light_dir = vec3_normalize(light_dir);
	visible = shadow_factor(scene, hit, light_dir, light_dist);
	diffuse = visible * scene->light.ratio
		* fmax(0.0, vec3_dot(hit->normal, light_dir));
	spec = specular_term(scene, ray, hit, light_dir, diffuse);
	out.r = hit->color.r * (scene->ambient.ratio * scene->ambient.color.r
			/ 255.0 + diffuse) + 255.0 * spec;
	out.g = hit->color.g * (scene->ambient.ratio * scene->ambient.color.g
			/ 255.0 + diffuse) + 255.0 * spec;
	out.b = hit->color.b * (scene->ambient.ratio * scene->ambient.color.b
			/ 255.0 + diffuse) + 255.0 * spec;
	return (color_clamp(out));
}

t_color	trace_ray(t_scene *scene, t_ray ray)
{
	t_hit	hit;
	t_color	bg;

	bg = (t_color){10.0, 10.0, 20.0};
	if (!scene_closest_hit(scene, ray, &hit))
		return (bg);
	return (shade_hit(scene, ray, &hit));
}
