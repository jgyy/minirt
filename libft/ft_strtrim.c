#include "libft.h"
#include <stdlib.h>

static int	in_set(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	char	*res;

	start = 0;
	while (s1[start] && in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && in_set(s1[end - 1], set))
		end--;
	res = malloc(sizeof(char) * (end - start + 1));
	if (!res)
		return (NULL);
	ft_memset(res, 0, end - start + 1);
	while (start < end)
		res[ft_strlen(res)] = s1[start++];
	return (res);
}
