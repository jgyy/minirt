#include "minirt.h"

typedef struct s_cyl
{
	t_vec3	center;
	t_vec3	axis;
	double	radius;
	double	half_h;
}	t_cyl;

static t_cyl	make_cyl(t_object *obj)
{
	t_cyl	c;

	c.center = obj->pos;
	c.axis = obj->normal;
	c.radius = obj->diameter / 2.0;
	c.half_h = obj->height / 2.0;
	return (c);
}

static int	try_root(t_ray ray, t_cyl c, double t, double *t_out)
{
	double	m;

	m = vec3_dot(c.axis, vec3_sub(ray.origin, c.center)) + t * vec3_dot(c.axis, ray.dir);
	if (t > EPSILON && m >= -c.half_h && m <= c.half_h)
	{
		*t_out = t;
		return (1);
	}
	return (0);
}

static int	side_root(t_ray ray, t_cyl c, double *t_out)
{
	t_vec3	oc;
	t_vec3	d_perp;
	t_vec3	oc_perp;
	double	a;
	double	b;
	double	cc;
	double	disc;

	oc = vec3_sub(ray.origin, c.center);
	d_perp = vec3_sub(ray.dir, vec3_scale(c.axis, vec3_dot(c.axis, ray.dir)));
	oc_perp = vec3_sub(oc, vec3_scale(c.axis, vec3_dot(c.axis, oc)));
	a = vec3_dot(d_perp, d_perp);
	if (a < EPSILON)
		return (0);
	b = 2.0 * vec3_dot(d_perp, oc_perp);
	cc = vec3_dot(oc_perp, oc_perp) - c.radius * c.radius;
	disc = b * b - 4.0 * a * cc;
	if (disc < 0.0)
		return (0);
	disc = sqrt(disc);
	if (try_root(ray, c, (-b - disc) / (2.0 * a), t_out))
		return (1);
	return (try_root(ray, c, (-b + disc) / (2.0 * a), t_out));
}

static int	cap_root(t_ray ray, t_vec3 cap_center, t_vec3 n, double r, double *t)
{
	double	denom;
	t_vec3	point;

	denom = vec3_dot(n, ray.dir);
	if (fabs(denom) < EPSILON)
		return (0);
	*t = vec3_dot(vec3_sub(cap_center, ray.origin), n) / denom;
	if (*t <= EPSILON)
		return (0);
	point = vec3_add(ray.origin, vec3_scale(ray.dir, *t));
	if (vec3_length(vec3_sub(point, cap_center)) > r)
		return (0);
	return (1);
}

static t_vec3	side_normal(t_cyl c, t_vec3 point)
{
	t_vec3	proj;

	proj = vec3_add(c.center, vec3_scale(c.axis,
				vec3_dot(vec3_sub(point, c.center), c.axis)));
	return (vec3_normalize(vec3_sub(point, proj)));
}

int	hit_cylinder(t_ray ray, t_object *obj, t_hit *hit)
{
	t_cyl	c;
	t_vec3	top;
	t_vec3	bot;
	double	t_side;
	double	t_top;
	double	t_bot;
	int		has[3];

	c = make_cyl(obj);
	top = vec3_add(c.center, vec3_scale(c.axis, c.half_h));
	bot = vec3_sub(c.center, vec3_scale(c.axis, c.half_h));
	has[0] = side_root(ray, c, &t_side);
	has[1] = cap_root(ray, top, c.axis, c.radius, &t_top);
	has[2] = cap_root(ray, bot, vec3_scale(c.axis, -1.0), c.radius, &t_bot);
	hit->t = -1.0;
	if (has[0] && (hit->t < 0.0 || t_side < hit->t))
		hit->t = t_side;
	if (has[1] && (hit->t < 0.0 || t_top < hit->t))
		hit->t = t_top;
	if (has[2] && (hit->t < 0.0 || t_bot < hit->t))
		hit->t = t_bot;
	if (hit->t < 0.0)
		return (0);
	hit->point = vec3_add(ray.origin, vec3_scale(ray.dir, hit->t));
	hit->color = obj->color;
	if (has[1] && fabs(hit->t - t_top) < EPSILON)
		hit->normal = c.axis;
	else if (has[2] && fabs(hit->t - t_bot) < EPSILON)
		hit->normal = vec3_scale(c.axis, -1.0);
	else
		hit->normal = side_normal(c, hit->point);
	return (1);
}
