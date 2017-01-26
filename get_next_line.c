/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:46:26 by bfrochot          #+#    #+#             */
/*   Updated: 2017/01/26 15:16:07 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_fillit(char **line, char *buff, char *save, char *done)
{
	int i;
	int j;

	save[0] = '\0';
	i = 0;
	while ((*line)[i])
		++i;
	j = -1;
	while (buff[++j] && buff[j] != '\n')
		(*line)[i + j] = buff[j];
	(*line)[i + j] = '\0';
	if (buff[j] == '\n')
	{
		*done = 0;
		i = 0;
		while (buff[j + 1])
		{
			save[i] = buff[j + 1];
			++j;
			++i;
		}
		save[i] = '\0';
	}
}

char	ft_fill(char **line, char *buff, char *done)
{
	static char save[BUFF_SIZE + 1];
	int			i;
	int			j;

	i = -1;
	while (save[++i] && save[i] != '\n')
		(*line)[i] = save[i];
	if (save[0])
		(*line)[i] = '\0';
	if (save[i] == '\0')
	{
		ft_fillit(line, buff, save, done);
		return (0);
	}
	else
	{
		j = 0;
		while (save[++i])
		{
			save[j] = save[i];
			++j;
		}
		save[j] = '\0';
		return (1);
	}
}

char	*ft_alloc(char **line, int n)
{
	char	*new;
	int		i;

	new = malloc(BUFF_SIZE * n + 1);
	i = 0;
	while ((*line)[i])
	{
		new[i] = (*line)[i];
		++i;
	}
	new[i] = '\0';
	free(*line);
	return (new);
}

int		ft_2long(const int fd, char **line, char *buff, char done)
{
	int	i;
	int n;

	n = 2;
	while (done)
	{
		++n;
		if ((i = read(fd, buff, BUFF_SIZE)) > 0)
		{
			buff[i] = '\0';
			*line = ft_alloc(line, n);
			ft_fill(line, buff, &done);
		}
		else if (i == 0 && (*line)[0] == '\0')
			return (0);
		else if (i == 0 && (*line)[0])
			return (1);
		else
			return (-1);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	char buff[BUFF_SIZE + 1];
	char done;

	done = 1;
	buff[0] = '\0';
	if (line == NULL)
		return (-1);
	(*line) = malloc(BUFF_SIZE + 1);
	(*line)[0] = '\0';
	if (ft_fill(line, buff, &done))
		return (1);
	return (ft_2long(fd, line, buff, done));
}
