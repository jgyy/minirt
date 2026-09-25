#include "minirt.h"

static double	clamp(double v, double lo, double hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}

t_color	color_clamp(t_color c)
{
	c.r = clamp(c.r, 0.0, 255.0);
	c.g = clamp(c.g, 0.0, 255.0);
	c.b = clamp(c.b, 0.0, 255.0);
	return (c);
}

int	color_to_int(t_color c)
{
	c = color_clamp(c);
	return (((int)c.r << 16) | ((int)c.g << 8) | (int)c.b);
}
