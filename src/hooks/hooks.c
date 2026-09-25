#include "minirt.h"

static void	cleanup_and_exit(t_data *data, int code)
{
	if (data->mlx)
	{
		if (data->img.ptr)
			mlx_destroy_image(data->mlx, data->img.ptr);
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free_scene(&data->scene);
	exit(code);
}

int	hook_keypress(int keycode, void *param)
{
	if (keycode == 65307)
		cleanup_and_exit((t_data *)param, 0);
	return (0);
}

int	hook_close(void *param)
{
	cleanup_and_exit((t_data *)param, 0);
	return (0);
}
