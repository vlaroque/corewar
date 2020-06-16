/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:08:38 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/16 21:14:25 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "corewar.h"

int		mars_fill(t_data *data)
{
	int		i;
	int		color;
	t_champ	*champ;
	int		offset;

	champ = data->champs;
	offset = 0;
	color = 1;
	while (champ)
	{
		i = 0;
		while (i < champ->prog_size)
		{
			data->mars[offset + i] = champ->content[i];
			data->colors[offset + i] = color;
			i++;
		}
		new_process(data, offset, champ->id);
		champ = champ->next;
		offset += MEM_SIZE / data->nbr_champs;
		color++;
	}
	return (0);
}

int		dump_option(t_data *data, int ac, char **av, int *head_ac)
{
	int		nbr_cycles;

	(*head_ac) += 1;
	if (*head_ac > ac)
		print_error(data, 3);
	if (!ft_isnbr(av[*head_ac]))
		print_error(data, 1);
	nbr_cycles = ft_atoi(av[*head_ac]);
	if (nbr_cycles < 0)
		print_error(data, 2);
	data->cycles_before_dump = nbr_cycles;
	data->dump_option = 1;
	return (0);
}

int		champ_id_option(t_data *data, int *head_ac, t_champid *champ_id)
{
	int		nbr;

	(*head_ac) += 1;
	if (*head_ac > data->ac)
		print_error(data, 10);
	if (!ft_isnbr(data->av[*head_ac]))
		print_error(data, 11);
	nbr = ft_atoi(data->av[*head_ac]);
	champ_id->carry = 1;
	champ_id->carried_nbr = nbr;
	return (0);
}

int		verbose_option(t_data *data, int ac, char **av, int *head_ac)
{
	int		verbosity;

	(*head_ac) += 1;
	if (*head_ac > ac)
		print_error(data, 3);
	if (!ft_isnbr(av[*head_ac]))
		print_error(data, 1);
	verbosity = ft_atoi(av[*head_ac]);
	data->verbosity = verbosity;
	return (0);
}

int		init_corewar(t_data *data, int ac, char **av)
{
	int				head_ac;
	t_champid		champ_id;

	op_bzero(&champ_id, sizeof(t_champid));
	head_ac = 1;
	while (head_ac < ac)
	{
		if (av[head_ac][0] != '-')
			new_champ(data, av[head_ac], &champ_id);
		else if (!ft_strncmp(av[head_ac], "-dump", 5))
			dump_option(data, ac, av, &head_ac);
		else if (!ft_strncmp(av[head_ac], "-n", 2))
			champ_id_option(data, &head_ac, &champ_id);
		else if (!ft_strncmp(av[head_ac], "-c", 2))
			data->visual_option = 1;
		else if (!ft_strncmp(av[head_ac], "-d", 2))
			data->debug_option = 1;
		else if (!ft_strncmp(av[head_ac], "-v", 2))
			verbose_option(data, ac, av, &head_ac);
		else if (!ft_strncmp(av[head_ac], "-a", 2))
			data->aff_option = 1;
		head_ac++;
	}
	return (0);
}
