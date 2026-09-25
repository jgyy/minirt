#include "minirt.h"

static void	write_uint_fd(int fd, unsigned int n)
{
	char	digit;

	if (n >= 10)
		write_uint_fd(fd, n / 10);
	digit = (char)('0' + n % 10);
	write(fd, &digit, 1);
}

static void	write_header(int fd, int width, int height)
{
	write(fd, "P6\n", 3);
	write_uint_fd(fd, (unsigned int)width);
	write(fd, " ", 1);
	write_uint_fd(fd, (unsigned int)height);
	write(fd, "\n255\n", 5);
}

static void	write_pixels(int fd, t_data *data)
{
	int		x;
	int		y;
	int		bytes;
	char	*p;
	char	rgb[3];

	bytes = data->img.bpp / 8;
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			p = data->img.addr + y * data->img.line_len + x * bytes;
			rgb[0] = p[2];
			rgb[1] = p[1];
			rgb[2] = p[0];
			write(fd, rgb, 3);
			x++;
		}
		y++;
	}
}

void	export_ppm(t_data *data, const char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		error_exit(&data->scene, "cannot open output file for headless render");
	write_header(fd, data->width, data->height);
	write_pixels(fd, data);
	close(fd);
}
