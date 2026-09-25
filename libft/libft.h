/* libft.h - minimal, self-contained helper library for miniRT.
 * Re-implements the handful of libc-ish helpers the project needs, since
 * the subject's allowed external functions do not include string.h/stdlib.h
 * helpers such as strlen, strdup, memset or calloc. */
#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

int		ft_isdigit(int c);
int		ft_isspace(int c);
int		ft_isalpha(int c);
int		ft_isprint_num(int c);

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strtrim(const char *s1, const char *set);
char	**ft_split(const char *s, char c);
void	ft_free_split(char **arr);

int		ft_atoi(const char *str);
double	ft_atof(const char *str);

void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);

void	ft_putstr_fd(const char *s, int fd);
void	ft_putendl_fd(const char *s, int fd);

#endif
