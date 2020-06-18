/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_mars_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 21:36:17 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/18 21:56:12 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** colors 1 yellow 2 blue 3 red 4 green
*/

int		what_color(t_data *data, char *buff, int buff_i, int i)
{
	if (data->colors[i] == 0)
		buff_i = write_in_buffer(buff, "\e[39m", buff_i);
	else if (data->colors[i] == 1)
		buff_i = write_in_buffer(buff, "\e[32m", buff_i);
	else if (data->colors[i] == 2)
		buff_i = write_in_buffer(buff, "\e[34m", buff_i);
	else if (data->colors[i] == 3)
		buff_i = write_in_buffer(buff, "\e[31m", buff_i);
	else if (data->colors[i] == 4)
		buff_i = write_in_buffer(buff, "\e[36m", buff_i);
	return (buff_i);
}

int		color_octet(t_data *data, char *buff, int buff_i, int i)
{
	if (i == 0)
		buff_i = what_color(data, buff, buff_i, i);
	else if (data->colors[i - 1] != data->colors[i])
		buff_i = what_color(data, buff, buff_i, i);
	return (buff_i);
}
