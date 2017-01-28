/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 12:18:36 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/28 12:38:40 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		colorline(float i)
{
	if (i / 9 <= 0.1)
		return (0x000099);
	else if (i / 9 <= 0.2)
		return (0x0000FF);
	else if (i / 9 <= 0.25)
		return (0x33CCFF);
	else if (i / 9 <= 0.4)
		return (0x66FFFF);
	else if (i / 9 <= 1.5)
		return (0xCCCC33);
	else if (i / 9 <= 4)
		return (0x339933);
	else if (i / 9 <= 5.5)
		return (0x336600);
	else if (i / 9 <= 9)
		return (0x663300);
	else
		return (0xFFFFFF);
}
