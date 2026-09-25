#include "minirt.h"

void	error_exit(t_scene *scene, const char *msg)
{
	if (scene)
		free_scene(scene);
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(msg, 2);
	exit(1);
}
