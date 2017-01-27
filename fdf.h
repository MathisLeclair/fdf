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

int		fdfinit(t_env *ev);

#endif