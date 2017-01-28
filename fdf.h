/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 12:37:45 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/28 13:15:16 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "./libft/libft.h"
# include <mlx.h>
# include <math.h>

# define BUFF_SIZE 32
# define LEN_LINE 20

typedef struct	s_env
{
	void	*mlx;
	void	*win;
	int		fd;
	char	***array;
	int		tx;
	int		ty;
	int		rx;
	int		ry;
	int		p;
	int		len;
	int		zoom;
	int		winx;
	int		winy;
	int		max;
	int		min;
}				t_env;

void			error(int i);
void			*palloc(size_t size);
int				get_next_line(const int fd, char **line);
int				keymap(int keycode, t_env *ev);
char			**ft_strsplitquote(char const *s, char c, char tab);
int				fdfinit(t_env *ev);
int				colorline(float i);
int				printcontrol(t_env *ev);
void			draw_line(float *pts1, float *pts2, t_env *ev);
void			initev(t_env *ev);
int				printcontrol(t_env *ev);

#endif
