#include "fdf.h"

void	draw_line(float x, float y, float a, float b, t_env *ev)
{
	float i;

	if (x == a && y == b)
		mlx_pixel_put(ev->mlx, ev->win, x, y, 0xFFFFFF);
	else if (fabsf(x - a) >= fabsf(y - b))
	{
		i = x <= a ? x - 1 : a - 1;
		while (++i <= (x <= a ? a : x))
			mlx_pixel_put(ev->mlx, ev->win, i, i * (y - b) / (x - a) + (b * x - a * y) / (x - a), 0xFFFFFF);
	}
	else
	{
		i = y <= b ? y - 1 : b - 1;
		while (++i <= (y <= b ? b : y))
			mlx_pixel_put(ev->mlx, ev->win, i * (x - a) / (y - b) - (b * x - a * y) / (y - b), i, 0xFFFFFF);
	}
}

void	printcontrol(t_env *ev)
{
	mlx_string_put(ev->mlx, ev->win, 0, 0, 0xFF0000, "ROTATION: (PAV NUM) 4 / 6 / 8 / 2");
	mlx_string_put(ev->mlx, ev->win, 0, 20, 0xFF0000, "TRANSLATION: ARROW (OR W / A / S / D)");
	mlx_string_put(ev->mlx, ev->win, 0, 40, 0xFF0000, "EXIT: ESC");
	mlx_string_put(ev->mlx, ev->win, 0, 60, 0xFF0000, "PROFONDEUR : (PAV NUM) 7 / 9");
}

int		fdfinit(t_env *ev)
{
	int x;
	int y;
	int i;

	y = 0;
	i = 100;
	while (ev->array[y])
	{
		x = 0;
		while (ev->array[y][x])
		{
//			set x y a et b et ne pas les afficher si en dehors de la map
			if (ev->array[y][x + 1])
				draw_line((x + ev->tx + 0.12 * i) * ev->zoom, (y + ev->ty + 0.12
				* i) * ev->zoom - ft_atoi(ev->array[y][x]) * ev->p * 10 /
				ev->len, (x + ev->tx + 1 + 0.12 * i) * ev->zoom, (y + ev->ty +
				0.12 * i) * ev->zoom - ft_atoi(ev->array[y][x + 1]) * ev->p * 10
				/ ev->len, ev);
			if (ev->array[y + 1] && ev->array[y + 1][x])
				draw_line((x + ev->tx + 0.12 * i) * ev->zoom, (y + ev->ty + 0.12
				* i) * ev->zoom - ft_atoi(ev->array[y][x]) * ev->p * 10 /
				ev->len, (x + ev->tx + 0.12 * (i - 1)) * ev->zoom, (y + ev->ty +
				0.12 * (i - 1) + 1) * ev->zoom - ft_atoi(ev->array[y + 1][x]) *
				ev->p * 10 / ev->len, ev);
			++x;
		}
		++y;
		--i;
	}
	printcontrol(ev);
	return (1);
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
		split = ft_strsplit(line, ' ');
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
	ev->array = NULL;
	ev->tx = 0;
	ev->ty = 0;
	ev->rx = 0;
	ev->ry = 0;
	ev->p = 1;
	ev->zoom = 50;
	ev->winx = ev->len * 86;
	ev->winy = ev->len * 43;
	if (ev->winx > 2560)
		ev->winx = 2560;
	if (ev->winy > 1440)
		ev->winy = 1440;
}

int		fdfclean(t_env *ev)
{
	mlx_clear_window(ev->mlx, ev->win);
	fdfinit(ev);
	return (0);
}

int		main(int ac, char **av)
{
	t_env	*ev;

	ev = palloc(sizeof(t_env));
	if((ev->fd = open(av[1], O_RDONLY)) == -1)
		error(-2);
	ev->len = get_arraysize(ev->fd);
	if((ev->fd = open(av[1], O_RDONLY)) == -1)
		error(-2);
	initev(ev);
	ev->array = get_map(ev->fd, ev->len);
	ev->mlx = mlx_init();
	ev->win = mlx_new_window(ev->mlx, ev->winx, ev->winy, "test");
	if (ac == 2)
	{
		mlx_key_hook(ev->win, keymap, ev);
		mlx_expose_hook(ev->win, fdfclean, ev);
		mlx_loop(ev->mlx);
	}
	else
		error(-1);
}
