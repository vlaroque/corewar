/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:48:23 by vlaroque          #+#    #+#             */
/*   Updated: 2020/03/06 22:23:26 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "corewar.h"

int		contestant(t_champ *champ, int id)
{
	if (champ->next)
		contestant(champ->next, id + 0);
	ft_putstr("* Player ");
	ft_putnbr(id);
	ft_putstr(", weighing ");
	ft_putnbr(champ->prog_size);
	ft_putstr(" bytes, \"");
	ft_putstr(champ->prog_name);
	ft_putstr("\" (\"");
	ft_putstr(champ->comment);
	ft_putstr("\") !\n");
	return (0);
}

int		introduce_contestants(t_data *data)
{
	int		i;

	i = 1;
	ft_putstr("Introducing contestants...\n");
	contestant(data->champs, i + 1);
	return (0);
}

int		victory(t_data *data)
{
	t_champ		*champ;
	static int	i = 1;

	champ = data->champs;
	while (champ)
	{
		if (champ->id == data->last_alive)
			break;
		champ = champ->next;
		i++;
	}
	ft_putstr("Contestant ");
	ft_putnbr(i);
	ft_putstr(", \"");
	ft_putstr(champ->prog_name);
	ft_putstr("\", has won !\n");
	return (0);
}

int		main(int ac, char **av)
{
	t_data		data;
	int			vic;

	op_bzero(&data, sizeof(t_data));
	init_corewar(&data, ac, av);
	if (!data.visual_option)
	introduce_contestants(&data);
	mars_fill(&data);
	vic = battle(&data);
	if (vic)
	{
		ft_putstr("end battle\n");
		victory(&data);
	}
	free_data(&data);
	//buff_mars(&data);
	return (0);
}
