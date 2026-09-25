#include "minirt.h"

static int	is_valid_number(const char *s)
{
	int	dots;
	int	digits;

	dots = 0;
	digits = 0;
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (*s == '.')
			dots++;
		else if (ft_isdigit((unsigned char)*s))
			digits++;
		else
			return (0);
		s++;
	}
	return (dots <= 1 && digits > 0);
}

double	parse_double_strict(t_scene *scene, const char *s)
{
	if (!s || !is_valid_number(s))
		error_exit(scene, "invalid numeric value in scene file");
	return (ft_atof(s));
}

int	parse_int_strict(t_scene *scene, const char *s)
{
	if (!s || !is_valid_number(s) || ft_strchr(s, '.'))
		error_exit(scene, "invalid integer value in scene file");
	return (ft_atoi(s));
}

void	parse_check_double(double v, double min, double max, char *ctx)
{
	if (v < min - EPSILON || v > max + EPSILON)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("value out of range for ", 2);
		ft_putendl_fd(ctx, 2);
		exit(1);
	}
}
