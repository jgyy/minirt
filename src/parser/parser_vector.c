#include "minirt.h"

static int	count_split(char **arr)
{
	int	n;

	n = 0;
	while (arr[n])
		n++;
	return (n);
}

t_vec3	parse_vector(t_scene *scene, const char *s)
{
	char	**parts;
	t_vec3	v;

	parts = ft_split(s, ',');
	if (!parts || count_split(parts) != 3)
	{
		ft_free_split(parts);
		error_exit(scene, "expected 3 comma-separated values (x,y,z)");
	}
	v.x = parse_double_strict(scene, parts[0]);
	v.y = parse_double_strict(scene, parts[1]);
	v.z = parse_double_strict(scene, parts[2]);
	ft_free_split(parts);
	return (v);
}

t_color	parse_color(t_scene *scene, const char *s)
{
	char	**parts;
	t_color	c;

	parts = ft_split(s, ',');
	if (!parts || count_split(parts) != 3)
	{
		ft_free_split(parts);
		error_exit(scene, "expected 3 comma-separated values (r,g,b)");
	}
	c.r = parse_int_strict(scene, parts[0]);
	c.g = parse_int_strict(scene, parts[1]);
	c.b = parse_int_strict(scene, parts[2]);
	ft_free_split(parts);
	parse_check_double(c.r, 0, 255, "color channel");
	parse_check_double(c.g, 0, 255, "color channel");
	parse_check_double(c.b, 0, 255, "color channel");
	return (c);
}
