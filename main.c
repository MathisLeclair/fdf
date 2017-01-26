#include "fdf.h"

void	draw_line(int x, int y, int a, int b, t_env *ev)
{
	int i;

	if (x == a && y == b)
		mlx_pixel_put(ev->mlx, ev->win, x, y, 0255255000);
	else if (abs(x - a) >= abs(y - b))
	{
		i = x <= a ? x - 1 : a - 1;
		while (++i <= (x <= a ? a : x))
			mlx_pixel_put(ev->mlx, ev->win, i, i * (y - b) / (x - a) + (b * x - a * y) / (x - a), 0255255000);
	}
	else
	{
		i = y <= b ? y - 1 : b - 1;
		while (++i <= (y <= b ? b : y))
			mlx_pixel_put(ev->mlx, ev->win, i * (x - a) / (y - b) - (b * x - a * y) / (y - b), i, 0255255000);
	}
}

int		fdfinit(t_env *ev)
{

	ev->zoom = 10;
	ev->roty = 1;
	ev->roty = 1;
	draw_line(100, 100, 200, 100, ev);
	return (1);
}

int init(int i)
{
	return (i);
}

int		get_arraysize(int fd)
{
	char 	buf[1];
	int		i;

	i = 0;
	while (read(fd, buf, 1))
		if (buf[0] == '\n')
			++i;
	if (buf[0] != '\n')
		++i;
	close(fd);
	return (i);
}

char	***get_map(int fd, int len)
{
	char	***map;
	char	**split;
	char	*line;
	int		pre_len;
	int		i;

	map = palloc(sizeof(char **) * (len + 1));
	map[len] = 0;
	i = 0;
	pre_len = 0;
	while (get_next_line(fd, &line))
	{
		split = ft_strsplitquote(line, ' ', 0);
		len = 0;
		while (split[len])
			++len;
		if ((pre_len != 0 && pre_len != len) || len == 0)
			error(LEN_LINE);
		pre_len = len;
		map[i] = split;
		++i;
		free(line);
	}
	return (map);
}

void	initev(t_env *ev)
{
	ev->mlx = NULL;
	ev->win = NULL;
	ev->fd = 0;
	ev->array = NULL;
	ev->rotx = 0;
	ev->roty = 0;
	ev->zoom = 0;
}

int		main(int ac, char **av)
{
	t_env	*ev;
	int		i;

	ev = palloc(sizeof(t_env));
	initev(ev);
	if((ev->fd = open(av[1], O_RDONLY)) == -1)
		error(-2);
	i = get_arraysize(ev->fd);
	if((ev->fd = open(av[1], O_RDONLY)) == -1)
		error(-2);
	ev->mlx = mlx_init();
	ev->win = mlx_new_window(ev->mlx, 1280, 720, "test");
	ev->array = get_map(ev->fd, i);
	if (ac == 2)
	{
		draw_line(50, 10, 200, 10, ev);
		draw_line(200, 10, 200, 100, ev);
		mlx_loop_hook(ev->mlx, fdfinit, ev);
		mlx_key_hook(ev->win, fdfinit, ev);
		mlx_loop(ev->mlx);
	}
	else
		error(-1);
}