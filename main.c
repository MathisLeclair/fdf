/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 12:08:24 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/28 12:44:17 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_arraysize(int fd)
{
	char	buf[1];
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

char	***inv(char ***map, int i)
{
	int		j;
	char	***mapi;

	while (map[i])
		++i;
	j = 0;
	while (map[0][j])
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
	return (mapi);
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
	return (inv(map, 0));
}

int		get_max(char ***array)
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
	if ((ev->fd = open(av[1], O_RDONLY)) == -1)
		error(-2);
	ev->len = get_arraysize(ev->fd);
	if ((ev->fd = open(av[1], O_RDONLY)) == -1)
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
