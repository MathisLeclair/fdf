/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdfinit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 12:20:17 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/28 12:42:30 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdfinit3(double mx, double my, t_env *ev, int *cord)
{
	float pts1[3];
	float pts2[3];

	pts1[0] = mx;
	pts1[1] = my - ft_atoi(ev->array[cord[0]][cord[1]]) * ev->p * 10 / ev->len;
	pts1[2] = ft_atoi(ev->array[cord[0]][cord[1]]);
	pts2[0] = mx - sin(ev->rx * 2 * M_PI / 360) * ev->zoom;
	pts2[1] = my + cos(ev->rx * 2 * M_PI / 360) * ev->zoom -
	ft_atoi(ev->array[cord[0]][cord[1] + 1]) * ev->p * 10 / ev->len;
	pts2[2] = ft_atoi(ev->array[cord[0]][cord[1] + 1]);
	draw_line(pts1, pts2, ev);
}

void	fdfinit2(double mx, double my, t_env *ev, int *cord)
{
	float pts1[3];
	float pts2[3];

	pts1[0] = mx;
	pts1[1] = my - ft_atoi(ev->array[cord[0]][cord[1]]) * ev->p * 10 / ev->len;
	pts1[2] = ft_atoi(ev->array[cord[0]][cord[1]]);
	pts2[0] = mx + ev->zoom;
	pts2[1] = my - ft_atoi(ev->array[cord[0] + 1][cord[1]]) * ev->p * 10
	/ ev->len;
	pts2[2] = ft_atoi(ev->array[cord[0] + 1][cord[1]]);
	draw_line(pts1, pts2, ev);
}

void	fdfinit4(t_env *ev, int *cord, double mx, double my)
{
	if (ev->array[cord[0] + 1] && ev->array[cord[0] + 1][cord[1]])
		fdfinit2(mx, my, ev, cord);
	if (ev->array[cord[0]][cord[1] + 1])
		fdfinit3(mx, my, ev, cord);
	++cord[1];
}

int		fdfinit(t_env *ev)
{
	int		cord[2];
	double	mx;
	double	my;

	cord[0] = 0;
	while (ev->array[cord[0]])
	{
		cord[1] = 0;
		mx = (cord[0] + ev->tx * (1 - sin(ev->rx * 2 * M_PI / 360))) * ev->zoom;
		my = (cord[1] + cos(ev->rx * 2 * M_PI / 360) * ev->ty) * ev->zoom;
		while (ev->array[cord[0]][cord[1]])
		{
			mx = mx - sin(ev->rx * 2 * M_PI / 360) * ev->zoom;
			my = my + cos(ev->rx * 2 * M_PI / 360) * ev->zoom;
			if (mx <= -(ev->winx / ev->len) || mx >= ev->winx)
				++cord[1];
			else if (my <= -(ev->winy / ev->len) || my >= ev->winx)
				++cord[1];
			else
				fdfinit4(ev, cord, mx, my);
		}
		++cord[0];
	}
	return (printcontrol(ev));
}
