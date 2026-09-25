#include "minirt.h"

double	vec3_length(t_vec3 a)
{
	return (sqrt(vec3_dot(a, a)));
}

t_vec3	vec3_normalize(t_vec3 a)
{
	double	len;

	len = vec3_length(a);
	if (len < EPSILON)
		return (a);
	return (vec3_scale(a, 1.0 / len));
}

t_vec3	vec3_reflect(t_vec3 v, t_vec3 n)
{
	return (vec3_sub(v, vec3_scale(n, 2.0 * vec3_dot(v, n))));
}
