#include "minirt.h"

# define READ_CHUNK 4096

static char	*join_and_free(char *acc, char *buf, int len)
{
	char	*tmp;
	size_t	acc_len;
	int		i;

	acc_len = ft_strlen(acc);
	tmp = malloc(sizeof(char) * (acc_len + (size_t)len + 1));
	if (!tmp)
	{
		free(acc);
		return (NULL);
	}
	i = 0;
	while ((size_t)i < acc_len)
	{
		tmp[i] = acc[i];
		i++;
	}
	i = 0;
	while (i < len)
	{
		tmp[acc_len + (size_t)i] = buf[i];
		i++;
	}
	tmp[acc_len + (size_t)len] = '\0';
	free(acc);
	return (tmp);
}

char	*read_whole_file(const char *path)
{
	int		fd;
	char	buf[READ_CHUNK];
	char	*content;
	int		bytes;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	content = ft_strdup("");
	bytes = read(fd, buf, READ_CHUNK);
	while (bytes > 0)
	{
		content = join_and_free(content, buf, bytes);
		if (!content)
		{
			close(fd);
			return (NULL);
		}
		bytes = read(fd, buf, READ_CHUNK);
	}
	close(fd);
	if (bytes < 0)
	{
		free(content);
		return (NULL);
	}
	return (content);
}
