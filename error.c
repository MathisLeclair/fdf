/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 12:36:19 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/28 12:42:01 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error(int i)
{
	if (i == -1)
		ft_putstr("usage : ./fdf \"file_to_analyze.fdf\" ...\n");
	else if (i == -2)
		ft_putstr("File open error, are you sure it's a valid file ? Tard !\n");
	else if (i == -3)
		ft_putstr("malloc error, please hang yourself\n");
	else if (i == LEN_LINE)
		ft_putstr("Map error : missing point(s), ARSEHOLE.\n");
	exit(-1);
}

void	*palloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		error(-3);
	return (ptr);
}
