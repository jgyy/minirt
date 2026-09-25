#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

# define WIN_WIDTH 960
# define WIN_HEIGHT 540
# define EPSILON 1e-4
# define MRT_PI 3.14159265358979323846
# define MAX_RENDER_DEPTH 4

/* ---- math -------------------------------------------------------- */

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

/* ---- scene elements ------------------------------------------------ */

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
	int		set;
}	t_ambient;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	double	fov;
	t_vec3	right;
	t_vec3	up;
	int		set;
}	t_camera;

typedef struct s_light
{
	t_vec3	pos;
	double	ratio;
	t_color	color;
	int		set;
}	t_light;

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_obj_type;

typedef struct s_object
{
	t_obj_type			type;
	t_vec3				pos;
	t_vec3				normal;
	double				diameter;
	double				height;
	t_color				color;
	struct s_object		*next;
}	t_object;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	*objects;
}	t_scene;

typedef struct s_hit
{
	double	t;
	t_vec3	point;
	t_vec3	normal;
	t_color	color;
}	t_hit;

/* ---- image / mlx bookkeeping ---------------------------------------- */

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_scene		scene;
	int			width;
	int			height;
}	t_data;

/* ---- parser ----------------------------------------------------------- */

void		parse_scene(const char *path, t_scene *scene);
char		*read_whole_file(const char *path);
void		parse_line(t_scene *scene, char *line);
t_vec3		parse_vector(t_scene *scene, const char *s);
t_color		parse_color(t_scene *scene, const char *s);
double		parse_double_strict(t_scene *scene, const char *s);
int			parse_int_strict(t_scene *scene, const char *s);
void		parse_check_double(double v, double min, double max, char *ctx);
void		free_scene(t_scene *scene);
void		parse_ambient(t_scene *scene, char **tok);
void		parse_camera(t_scene *scene, char **tok);
void		parse_light(t_scene *scene, char **tok);
void		parse_sphere(t_scene *scene, char **tok);
void		parse_plane(t_scene *scene, char **tok);
void		parse_cylinder(t_scene *scene, char **tok);

/* ---- error handling ----------------------------------------------------- */

void		error_exit(t_scene *scene, const char *msg) __attribute__((noreturn));

/* ---- vector math -------------------------------------------------------- */

t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_sub(t_vec3 a, t_vec3 b);
t_vec3		vec3_scale(t_vec3 a, double s);
double		vec3_dot(t_vec3 a, t_vec3 b);
t_vec3		vec3_cross(t_vec3 a, t_vec3 b);
double		vec3_length(t_vec3 a);
t_vec3		vec3_normalize(t_vec3 a);
t_vec3		vec3_reflect(t_vec3 v, t_vec3 n);

/* ---- intersections -------------------------------------------------------- */

int			hit_sphere(t_ray ray, t_object *obj, t_hit *hit);
int			hit_plane(t_ray ray, t_object *obj, t_hit *hit);
int			hit_cylinder(t_ray ray, t_object *obj, t_hit *hit);
int			scene_closest_hit(t_scene *scene, t_ray ray, t_hit *hit);
int			scene_any_hit(t_scene *scene, t_ray ray, double max_dist);

/* ---- camera / render ------------------------------------------------------ */

void		camera_build_basis(t_camera *cam);
t_ray		camera_ray_for_pixel(t_camera *cam, int x, int y, int w, int h);
t_color		trace_ray(t_scene *scene, t_ray ray);
void		render_scene(t_data *data);
t_color		color_clamp(t_color c);
int			color_to_int(t_color c);

/* ---- window / hooks -------------------------------------------------------- */

void		put_pixel(t_data *data, int x, int y, int color);
int			hook_keypress(int keycode, void *param);
int			hook_close(void *param);
void		init_display(t_data *data);

/* ---- headless export -------------------------------------------------------- */

void		export_ppm(t_data *data, const char *path);

#endif
