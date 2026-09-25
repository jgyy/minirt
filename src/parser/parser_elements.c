#include "minirt.h"

static int	tok_count(char **tok)
{
	int	n;

	n = 0;
	while (tok[n])
		n++;
	return (n);
}

static void	check_argc(char **tok, int expected, char *name)
{
	if (tok_count(tok) != expected)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("wrong number of arguments for element ", 2);
		ft_putendl_fd(name, 2);
		exit(1);
	}
}

void	parse_ambient(t_scene *scene, char **tok)
{
	check_argc(tok, 3, "A");
	if (scene->ambient.set)
		error_exit(scene, "ambient light 'A' declared more than once");
	scene->ambient.ratio = parse_double_strict(scene, tok[1]);
	parse_check_double(scene->ambient.ratio, 0.0, 1.0, "ambient ratio");
	scene->ambient.color = parse_color(scene, tok[2]);
	scene->ambient.set = 1;
}

void	parse_camera(t_scene *scene, char **tok)
{
	t_vec3	dir;

	check_argc(tok, 4, "C");
	if (scene->camera.set)
		error_exit(scene, "camera 'C' declared more than once");
	scene->camera.pos = parse_vector(scene, tok[1]);
	dir = parse_vector(scene, tok[2]);
	parse_check_double(dir.x, -1.0, 1.0, "camera direction");
	parse_check_double(dir.y, -1.0, 1.0, "camera direction");
	parse_check_double(dir.z, -1.0, 1.0, "camera direction");
	if (vec3_length(dir) < EPSILON)
		error_exit(scene, "camera direction vector cannot be null");
	scene->camera.dir = vec3_normalize(dir);
	scene->camera.fov = parse_double_strict(scene, tok[3]);
	parse_check_double(scene->camera.fov, 0.0, 180.0, "camera fov");
	scene->camera.set = 1;
}

void	parse_light(t_scene *scene, char **tok)
{
	check_argc(tok, 4, "L");
	if (scene->light.set)
		error_exit(scene, "light 'L' declared more than once");
	scene->light.pos = parse_vector(scene, tok[1]);
	scene->light.ratio = parse_double_strict(scene, tok[2]);
	parse_check_double(scene->light.ratio, 0.0, 1.0, "light ratio");
	scene->light.color = parse_color(scene, tok[3]);
	scene->light.set = 1;
}
