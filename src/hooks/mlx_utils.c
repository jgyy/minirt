#include "minirt.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	int		offset;
	int		bytes;
	char	*p;

	if (x < 0 || y < 0 || x >= data->width || y >= data->height)
		return ;
	bytes = data->img.bpp / 8;
	offset = y * data->img.line_len + x * bytes;
	p = data->img.addr + offset;
	p[0] = (char)(color & 0xFF);
	p[1] = (char)((color >> 8) & 0xFF);
	p[2] = (char)((color >> 16) & 0xFF);
	if (bytes > 3)
		p[3] = 0;
}
