#include "minirt.h"

static void	run_headless(t_data *data, const char *out_path)
{
	int	bytes;

	data->img.bpp = 32;
	data->img.line_len = data->width * 4;
	data->img.endian = 0;
	data->img.ptr = NULL;
	bytes = data->img.line_len * data->height;
	data->img.addr = malloc((size_t)bytes);
	if (!data->img.addr)
		error_exit(&data->scene, "out of memory while allocating framebuffer");
	render_scene(data);
	export_ppm(data, out_path);
	free(data->img.addr);
	free_scene(&data->scene);
}

static void	usage(t_scene *scene)
{
	error_exit(scene, "usage: ./miniRT <scene.rt> [headless_output.ppm]");
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (argc != 2 && argc != 3)
		usage(&data.scene);
	parse_scene(argv[1], &data.scene);
	data.width = WIN_WIDTH;
	data.height = WIN_HEIGHT;
	if (argc == 3)
		run_headless(&data, argv[2]);
	else
		init_display(&data);
	return (0);
}
