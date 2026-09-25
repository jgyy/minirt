#include "minirt.h"

static void	check_argc(char **tok, int expected, char *name)
{
	int	n;

	n = 0;
	while (tok[n])
		n++;
	if (n != expected)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("wrong number of arguments for element ", 2);
		ft_putendl_fd(name, 2);
		exit(1);
	}
}

static void	push_object(t_scene *scene, t_object new_obj)
{
	t_object	*node;

	node = ft_calloc(1, sizeof(t_object));
	if (!node)
		error_exit(scene, "out of memory while allocating object");
	*node = new_obj;
	node->next = scene->objects;
	scene->objects = node;
}

void	parse_sphere(t_scene *scene, char **tok)
{
	t_object	obj;

	check_argc(tok, 4, "sp");
	obj.type = OBJ_SPHERE;
	obj.pos = parse_vector(scene, tok[1]);
	obj.diameter = parse_double_strict(scene, tok[2]);
	if (obj.diameter <= 0.0)
		error_exit(scene, "sphere diameter must be positive");
	obj.color = parse_color(scene, tok[3]);
	obj.height = 0.0;
	obj.normal = (t_vec3){0, 0, 0};
	obj.next = NULL;
	push_object(scene, obj);
}

void	parse_plane(t_scene *scene, char **tok)
{
	t_object	obj;
	t_vec3		n;

	check_argc(tok, 4, "pl");
	obj.type = OBJ_PLANE;
	obj.pos = parse_vector(scene, tok[1]);
	n = parse_vector(scene, tok[2]);
	if (vec3_length(n) < EPSILON)
		error_exit(scene, "plane normal vector cannot be null");
	obj.normal = vec3_normalize(n);
	obj.color = parse_color(scene, tok[3]);
	obj.diameter = 0.0;
	obj.height = 0.0;
	obj.next = NULL;
	push_object(scene, obj);
}

void	parse_cylinder(t_scene *scene, char **tok)
{
	t_object	obj;
	t_vec3		axis;

	check_argc(tok, 6, "cy");
	obj.type = OBJ_CYLINDER;
	obj.pos = parse_vector(scene, tok[1]);
	axis = parse_vector(scene, tok[2]);
	if (vec3_length(axis) < EPSILON)
		error_exit(scene, "cylinder axis vector cannot be null");
	obj.normal = vec3_normalize(axis);
	obj.diameter = parse_double_strict(scene, tok[3]);
	obj.height = parse_double_strict(scene, tok[4]);
	if (obj.diameter <= 0.0 || obj.height <= 0.0)
		error_exit(scene, "cylinder diameter/height must be positive");
	obj.color = parse_color(scene, tok[5]);
	obj.next = NULL;
	push_object(scene, obj);
}
