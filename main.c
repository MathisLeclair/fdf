#include "fdf.h"

int		colorline(float i)
{
	if (i < -300)
		return(0x000099);
	else if (i < -150)
		return (0x0000FF);
	else if (i < -50)
		return (0x33CCFF);
	else if (i < 0)
		return (0x66FFFF);
	else if (i == 0)
		return (0xFFFF66);
	else if (i > 50)
		return (0x99FF33);
	else if (i > 100)
		return (0x336600);
	else if (i > 150)
		return (0x663300);
	else
		return (0xFFFFFF);
}

void	draw_line(float *pts1, float *pts2, t_env *ev)
{
	float i;

	if (pts1[0] == pts2[0] && pts1[1] == pts2[1])
		mlx_pixel_put(ev->mlx, ev->win, pts1[0], pts1[1], colorline(pts1[2]));
	else if (fabsf(pts1[0] - pts2[0]) >= fabsf(pts1[1] - pts2[1]))
	{
		i = pts1[0] <= pts2[0] ? pts1[0] - 1 : pts2[0] - 1;
		while (++i <= (pts1[0] <= pts2[0] ? pts2[0] : pts1[0]))
			mlx_pixel_put(ev->mlx, ev->win, i, i * (pts1[1] - pts2[1]) / (pts1[0] - pts2[0]) + (pts2[1] * pts1[0] - pts2[0] * pts1[1]) / (pts1[0] - pts2[0]), colorline(pts1[2]));
	}
	else
	{
		i = pts1[1] <= pts2[1] ? pts1[1] - 1 : pts2[1] - 1;
		while (++i <= (pts1[1] <= pts2[1] ? pts2[1] : pts1[1]))
			mlx_pixel_put(ev->mlx, ev->win, i * (pts1[0] - pts2[0]) / (pts1[1] - pts2[1]) - (pts2[1] * pts1[0] - pts2[0] * pts1[1]) / (pts1[1] - pts2[1]), i, colorline(pts1[2]));
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
	float pts1[3];
	float pts2[3];
	double mx;
	double my;

	y = 0;
	i = 0;
	while (ev->array[y])
	{
		x = 0;
		while (ev->array[y][x])
		{
			if ((mx = (x + ev->tx + 0.12 * i) * ev->zoom) <= -(ev->winx /
				ev->len) || mx >= ev->winx)
				++x;
			else if ((my = (y + ev->ty + 0.12 * i) * ev->zoom) <= -(ev->winy /
					ev->len) || my >= ev->winx)
				++x;
			else
			{
				if (ev->array[y][x + 1] && my <= ev->winy * 2 && my >= -200)
				{
					pts1[0] = mx;
					pts1[1] = my - ft_atoi(ev->array[y][x]) * ev->p * 10 / ev->len;
					pts1[2] = ft_atoi(ev->array[y][x]);
					pts2[0] = (x + ev->tx + 1 + 0.12 * i) * ev->zoom;
					pts2[1] = my - ft_atoi(ev->array[y][x + 1]) * ev->p * 10 / ev->len;
					pts2[2] = ft_atoi(ev->array[y][x + 1]);
					draw_line(pts1, pts2, ev);
				}
				if (ev->array[y + 1] && ev->array[y + 1][x] && my <= ev->winy
					* 2 && my >= -200)
				{
					pts1[0] = mx;
					pts1[1] = my - ft_atoi(ev->array[y][x]) * ev->p * 10 / ev->len;
					pts1[2] = ft_atoi(ev->array[y][x]);
					pts2[0] = (x + ev->tx + 0.12 * (i - 1)) * ev->zoom;
					pts2[1] = (y + ev->ty + 0.12 * (i - 1) + 1) * ev->zoom - ft_atoi(ev->array[y + 1][x]) * ev->p * 10 / ev->len;
					pts2[2] = ft_atoi(ev->array[y + 1][x]);
					draw_line(pts1, pts2, ev);
				}
				++x;
			}
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

char	***get_map(int fd, int len, int i)
{
	char	***map;
	char	**split;
	char	*line;
	int		pre_len;

	map = palloc(sizeof(char **) * (len + 1));
	map[len] = 0;
	pre_len = 0;
	split = NULL;
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
	if (!split)
		error(LEN_LINE);
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
	ev->winx = (ev->winx > 2560 ? 2560 : ev->winx);
	ev->winy = (ev->winy > 1440 ? 1440 : ev->winy);
	ev->winx = (ev->winx < 960 ? 960 : ev->winx);
	ev->winy = (ev->winy < 540 ? 540 : ev->winy);
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
	ev->array = get_map(ev->fd, ev->len, 0);
	ev->mlx = mlx_init();
	ev->win = mlx_new_window(ev->mlx, ev->winx, ev->winy, "test");
	if (ac == 2)
	{
		mlx_key_hook(ev->win, keymap, ev);
		mlx_expose_hook(ev->win, fdfinit, ev);
		mlx_loop(ev->mlx);
	}
	else
		error(-1);
}
