#include "fdf.h"

char	***ft_getmap(int fd, int len)
{
	char	***map;
	char	**split;
	char	*line;
	int		pre_len;
	int		i;

	map = malloc(sizeof(char **) * len + 1);
	map[len] = 0;
	i = 0;
	pre_len = 0;
	while (get_next_line(fd, &line))
	{
		split = ft_strsplit(line, ' ');
		len = 0;
		while (split[len])
			++len;
		if ((pre_len != 0 && pre_len != len) || len == 0)
			error(LEN_LINE);
		pre_len = len;
		map[i] = split;
		++i;
	}
	return (map);
}
