/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 17:25:18 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/26 18:18:28 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	keymap2(int keycode, t_env *ev)
{
	if (keycode == 86)
		ev->rx += 5;
	else if (keycode == 88)
		ev->rx -= 5;
	else if (keycode == 91)
		ev->ry += 5;
	else if (keycode == 84)
		ev->ry -= 5;
	else if (keycode == 89)
		ev->p -= 1;
	else if (keycode == 92)
		ev->p += 1;
}

int		keymap(int keycode, t_env *ev)
{
	mlx_clear_window(ev->mlx, ev->win);
	if (keycode == 53)
		exit(0);
	else if (keycode == 2 || keycode == 124)
		ev->tx += 5;
	else if (keycode == 0 || keycode == 123)
		ev->tx -= 5;
	else if (keycode == 13 || keycode == 126)
		ev->ty -= 5;
	else if (keycode == 1 || keycode == 125)
		ev->ty += 5;
	else if (keycode == 78 && ev->zoom != 5)
		ev->zoom -= 5;
	else if (keycode == 69)
		ev->zoom += 5;
	keymap2(keycode, ev);
	fdfinit(ev);
	return (0);
}
