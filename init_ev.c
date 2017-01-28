/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ev.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 12:36:29 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/28 12:36:48 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
