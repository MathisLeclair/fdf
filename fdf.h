/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 14:19:46 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/26 14:44:15 by mleclair         ###   ########.fr       */
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

# define BUFF_SIZE 32
# define LEN_LINE 20

typedef struct	s_env
{
	void	*mlx;
	void	*win;
	int		fd;
	char	***array;
	int		rotx;
	int		roty;
	int		zoom;
}				t_env;

/*
** error.c
*/

void			error(int i);
void			*palloc(size_t size);


/*
** getnextline
*/

int				get_next_line(const int fd, char **line);

int				keymap(int keycode, t_env *ev);


char		**ft_strsplitquote(char const *s, char c, char tab);

#endif