#include "minirt.h"

void	camera_build_basis(t_camera *cam)
{
	t_vec3	world_up;

	world_up = (t_vec3){0.0, 1.0, 0.0};
	if (fabs(vec3_dot(cam->dir, world_up)) > 0.999)
		world_up = (t_vec3){1.0, 0.0, 0.0};
	cam->right = vec3_normalize(vec3_cross(cam->dir, world_up));
	cam->up = vec3_normalize(vec3_cross(cam->right, cam->dir));
}

t_ray	camera_ray_for_pixel(t_camera *cam, int x, int y, int w, int h)
{
	double	half_w;
	double	half_h;
	double	ndc_x;
	double	ndc_y;
	t_ray	ray;

	half_w = tan((cam->fov * MRT_PI / 180.0) / 2.0);
	half_h = half_w * (double)h / (double)w;
	ndc_x = (2.0 * (((double)x + 0.5) / (double)w) - 1.0) * half_w;
	ndc_y = (1.0 - 2.0 * (((double)y + 0.5) / (double)h)) * half_h;
	ray.origin = cam->pos;
	ray.dir = vec3_normalize(vec3_add(cam->dir,
				vec3_add(vec3_scale(cam->right, ndc_x),
					vec3_scale(cam->up, ndc_y))));
	return (ray);
}
