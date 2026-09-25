#include "minirt.h"

static void	dispatch(t_scene *scene, char **tok)
{
	if (ft_strncmp(tok[0], "A", 2) == 0)
		parse_ambient(scene, tok);
	else if (ft_strncmp(tok[0], "C", 2) == 0)
		parse_camera(scene, tok);
	else if (ft_strncmp(tok[0], "L", 2) == 0)
		parse_light(scene, tok);
	else if (ft_strncmp(tok[0], "sp", 3) == 0)
		parse_sphere(scene, tok);
	else if (ft_strncmp(tok[0], "pl", 3) == 0)
		parse_plane(scene, tok);
	else if (ft_strncmp(tok[0], "cy", 3) == 0)
		parse_cylinder(scene, tok);
	else
		error_exit(scene, "unknown element identifier in scene file");
}

void	parse_line(t_scene *scene, char *line)
{
	char	*trimmed;
	char	**tok;

	trimmed = ft_strtrim(line, " \t\r");
	if (!trimmed)
		error_exit(scene, "out of memory while parsing scene file");
	if (trimmed[0] == '\0')
	{
		free(trimmed);
		return ;
	}
	tok = ft_split(trimmed, ' ');
	free(trimmed);
	if (!tok || !tok[0])
	{
		ft_free_split(tok);
		return ;
	}
	dispatch(scene, tok);
	ft_free_split(tok);
}

static void	check_mandatory(t_scene *scene)
{
	if (!scene->ambient.set)
		error_exit(scene, "missing mandatory ambient light 'A' element");
	if (!scene->camera.set)
		error_exit(scene, "missing mandatory camera 'C' element");
	if (!scene->light.set)
		error_exit(scene, "missing mandatory light 'L' element");
}

void	parse_scene(const char *path, t_scene *scene)
{
	char	*content;
	char	**lines;
	int		i;

	scene->ambient.set = 0;
	scene->camera.set = 0;
	scene->light.set = 0;
	scene->objects = NULL;
	content = read_whole_file(path);
	if (!content)
		error_exit(scene, "cannot open or read scene file");
	lines = ft_split(content, '\n');
	free(content);
	if (!lines)
		error_exit(scene, "out of memory while parsing scene file");
	i = 0;
	while (lines[i])
	{
		parse_line(scene, lines[i]);
		i++;
	}
	ft_free_split(lines);
	check_mandatory(scene);
	camera_build_basis(&scene->camera);
}
