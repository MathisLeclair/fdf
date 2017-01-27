#include "fdf.h"

int		colorline(float i, t_env *ev)
{
	(void)ev;
	if (i / 9 <= 0.1)
		return(0x000099); //bleu fonce
	else if (i / 9 <= 0.2) 
		return (0x0000FF); //bleu moins fonce
	else if (i / 9 <= 0.25)
		return (0x33CCFF);//bleu claire
	else if (i / 9 <= 0.4)
		return (0x66FFFF);// bleu un peu moin claire que clqire
	else if (i / 9 <= 1.5)
		return (0xCCCC33); // jaune
	else if (i / 9 <= 4)
		return (0x339933); // vert claire
	else if (i / 9 <= 5.5)
		return (0x336600); // vert foncee
	else if (i / 9 <= 9)
		return (0x663300); // marron
	else
		return (0xFFFFFF); // blanc
}

void	draw_line(float *pts1, float *pts2, t_env *ev)
{
	float i;

	if (pts1[0] == pts2[0] && pts1[1] == pts2[1])
		mlx_pixel_put(ev->mlx, ev->win, pts1[0], pts1[1], colorline(pts1[2], ev));
	else if (fabsf(pts1[0] - pts2[0]) >= fabsf(pts1[1] - pts2[1]))
	{
		i = pts1[0] <= pts2[0] ? pts1[0] - 1 : pts2[0] - 1;
		while (++i <= (pts1[0] <= pts2[0] ? pts2[0] : pts1[0]))
			mlx_pixel_put(ev->mlx, ev->win, i, i * (pts1[1] - pts2[1]) / (pts1[0] - pts2[0]) + (pts2[1] * pts1[0] - pts2[0] * pts1[1]) / (pts1[0] - pts2[0]), colorline(pts1[2], ev));
	}
	else
	{
		i = pts1[1] <= pts2[1] ? pts1[1] - 1 : pts2[1] - 1;
		while (++i <= (pts1[1] <= pts2[1] ? pts2[1] : pts1[1]))
			mlx_pixel_put(ev->mlx, ev->win, i * (pts1[0] - pts2[0]) / (pts1[1] - pts2[1]) - (pts2[1] * pts1[0] - pts2[0] * pts1[1]) / (pts1[1] - pts2[1]), i, colorline(pts1[2], ev));
	}
}

void	printcontrol(t_env *ev)
{
	mlx_string_put(ev->mlx, ev->win, 0, 0, 0xFF0000, "ROTATION: (PAV NUM) 4 / 6 / 8 / 2");
	mlx_string_put(ev->mlx, ev->win, 0, 20, 0xFF0000, "TRANSLATION: ARROW (OR W / A / S / D)");
	mlx_string_put(ev->mlx, ev->win, 0, 40, 0xFF0000, "EXIT: ESC");
	mlx_string_put(ev->mlx, ev->win, 0, 60, 0xFF0000, "DEEPNESS : (PAV NUM) 7 / 9");
}

int		fdfinit(t_env *ev)
{
	int x;
	int y;
	float pts1[3];
	float pts2[3];
	double mx;
	double my;

	x = 0;
	while (ev->array[x])
	{
		y = 0;
		mx = (x + ev->tx * (1 - sin(ev->rx * 2 * M_PI / 360))) * ev->zoom;
		my = (y + cos(ev->rx * 2 * M_PI / 360) * ev->ty) * ev->zoom;
		while (ev->array[x][y])
		{
			mx = mx - sin(ev->rx * 2 * M_PI / 360) * ev->zoom;
			my = my + cos(ev->rx * 2 * M_PI / 360) * ev->zoom;
			if (mx <= -(ev->winx / ev->len) || mx >= ev->winx)
				++y;
			else if (my <= -(ev->winy / ev->len) || my >= ev->winx)
				++y;
			else
			{
				if (ev->array[x + 1] && ev->array[x + 1][y])
				{
					pts1[0] = mx;
					pts1[1] = my - ft_atoi(ev->array[x][y]) * ev->p * 10 / ev->len;
					pts1[2] = ft_atoi(ev->array[x][y]);
					pts2[0] = mx + ev->zoom;
					pts2[1] = my - ft_atoi(ev->array[x + 1][y]) * ev->p * 10 / ev->len;
					pts2[2] = ft_atoi(ev->array[x + 1][y]);
					draw_line(pts1, pts2, ev);
				}
				if (ev->array[x][y + 1])
				{
					pts1[0] = mx;
					pts1[1] = my - ft_atoi(ev->array[x][y]) * ev->p * 10 / ev->len;
					pts1[2] = ft_atoi(ev->array[x][y]);
					pts2[0] = mx - sin(ev->rx * 2 * M_PI / 360) * ev->zoom;
					pts2[1] = my + cos(ev->rx * 2 * M_PI / 360) * ev->zoom - ft_atoi(ev->array[x][y + 1]) * ev->p * 10 / ev->len;
					pts2[2] = ft_atoi(ev->array[x][y + 1]);
					draw_line(pts1, pts2, ev);
				}
				++y;
			}
		}
		++x;
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

char	***inv(char ***map)
{
	int i;
	int j;
	char ***mapi;

	i = 0;
	while (map[i])
		++i;
	j = 0;
	while(map[0][j])
		++j;
	mapi = malloc(sizeof(char **) * (j + 1));
	mapi[j] = 0;
	while (j--)
	{
		mapi[j] = malloc(sizeof(char *) * (i + 1));
		mapi[j][i] = 0;
	}
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			mapi[j][i] = map[i][j];
		free(map[i]);
	}
	free(map);
	return(mapi);
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
	return (inv(map));
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

int		get_max(char  ***array)
{
	int max;
	int min;
	int i;
	int j;

	i = -1;
	while (array[++i])
	{
		j = -1;
		while (array[i][++j])
		{
			if (ft_atoi(array[i][j]) > max)
				max = ft_atoi(array[i][j]);
			if (ft_atoi(array[i][j]) < min)
				min = ft_atoi(array[i][j]);
		}
	}
	return (max);
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
	ev->max = get_max(ev->array);
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
