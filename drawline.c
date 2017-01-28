/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 12:35:55 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/28 12:36:12 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(float *pts1, float *pts2, t_env *ev)
{
	float i;

	if (pts1[0] == pts2[0] && pts1[1] == pts2[1])
		mlx_pixel_put(ev->mlx, ev->win, pts1[0], pts1[1], colorline(pts1[2]));
	else if (fabsf(pts1[0] - pts2[0]) >= fabsf(pts1[1] - pts2[1]))
	{
		i = pts1[0] <= pts2[0] ? pts1[0] - 1 : pts2[0] - 1;
		while (++i <= (pts1[0] <= pts2[0] ? pts2[0] : pts1[0]))
			mlx_pixel_put(ev->mlx, ev->win, i, i * (pts1[1] - pts2[1]) /
			(pts1[0] - pts2[0]) + (pts2[1] * pts1[0] - pts2[0] * pts1[1]) /
			(pts1[0] - pts2[0]), colorline(pts1[2]));
	}
	else
	{
		i = pts1[1] <= pts2[1] ? pts1[1] - 1 : pts2[1] - 1;
		while (++i <= (pts1[1] <= pts2[1] ? pts2[1] : pts1[1]))
			mlx_pixel_put(ev->mlx, ev->win, i * (pts1[0] - pts2[0]) /
			(pts1[1] - pts2[1]) - (pts2[1] * pts1[0] - pts2[0] * pts1[1])
			/ (pts1[1] - pts2[1]), i, colorline(pts1[2]));
	}
}
