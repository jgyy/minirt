#include "minirt.h"

void	free_scene(t_scene *scene)
{
	t_object	*cur;
	t_object	*next;

	cur = scene->objects;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	scene->objects = NULL;
}
