#include "minirt.h"
#include <X11/X.h>

void	init_display(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error_exit(&data->scene, "mlx_init failed (no display available)");
	data->win = mlx_new_window(data->mlx, data->width, data->height, "miniRT");
	if (!data->win)
		error_exit(&data->scene, "failed to create window");
	data->img.ptr = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img.ptr)
		error_exit(&data->scene, "failed to create image buffer");
	data->img.addr = mlx_get_data_addr(data->img.ptr, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	render_scene(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
	mlx_key_hook(data->win, hook_keypress, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask,
		(int (*)())hook_close, data);
	mlx_loop(data->mlx);
}
