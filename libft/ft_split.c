#include "libft.h"
#include <stdlib.h>

static size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	*dup_word(const char *start, size_t len)
{
	char	*w;
	size_t	i;

	w = malloc(sizeof(char) * (len + 1));
	if (!w)
		return (NULL);
	i = 0;
	while (i < len)
	{
		w[i] = start[i];
		i++;
	}
	w[i] = '\0';
	return (w);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	len;

	arr = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		if (len > 0)
			arr[i++] = dup_word(s, len);
		s += len;
	}
	arr[i] = NULL;
	return (arr);
}

void	ft_free_split(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
