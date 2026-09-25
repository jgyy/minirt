#include "minirt.h"

void	render_scene(t_data *data)
{
	int		x;
	int		y;
	t_ray	ray;
	t_color	color;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			ray = camera_ray_for_pixel(&data->scene.camera, x, y,
					data->width, data->height);
			color = trace_ray(&data->scene, ray);
			put_pixel(data, x, y, color_to_int(color));
			x++;
		}
		y++;
	}
}
