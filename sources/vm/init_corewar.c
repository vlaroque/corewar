/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:08:38 by vlaroque          #+#    #+#             */
/*   Updated: 2020/03/06 21:46:37 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "corewar.h"

int		mars_fill(t_data *data)
{
	int		i;
	t_champ	*champ;
	int		offset;

	champ = data->champs;
	offset = 0;
	while (champ)
	{
		printf("\nnew champ\n");
		i = 0;
		while (i < CHAMP_MAX_SIZE)
		{
			data->mars[offset + i] = champ->content[i];
			i++;
		}
		new_process(data, offset, champ->id);
		champ = champ->next;
		offset += MEM_SIZE / data->nbr_champs;
	}
	return (0);
}

void	custom_id(t_data *data, t_champid *champ_id, char *str)
{
	int		nbr;

	data = 0;
	nbr = ft_atoi(str + 2);
	champ_id->carry = 1;
	champ_id->carried_nbr = nbr;
}

int		init_corewar(t_data *data, int ac, char **av)
{
	int				i;
	t_champid		champ_id;

	i = 1;
	if (ac == -1 || av == 0)
		return (0);
	while (i < ac)
	{
		if (av[i][0] != '-')
			new_champ(data, av[i], &champ_id);
		else if (av[i][1] == 'n')
			custom_id(data, &champ_id, av[i]);
		i++;
	}
	data->max_cycles = CYCLE_TO_DIE;
	data->cycles_to_die = CYCLE_TO_DIE;
//	champ_dump(data->champs);
//	champ_dump(data->champs->next);
	return (0);
}

