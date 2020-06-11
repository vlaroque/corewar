/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbosity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:14:57 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/11 23:29:04 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		show_turn(t_data *data, int i)
{
	if (data->turn == 0)
		return (0);
	if (!(data->verbosity & 2))
		return (0);
	ft_putstr("It is now cycle ");
	ft_putnbr(i);
	ft_putstr("\n");
	return (0);
}

int		show_cycle_to_die(t_data *data, int i)
{
	if (!(data->verbosity & 2))
		return (0);
	ft_putstr("Cycle to die is now ");
	ft_putnbr(i);
	ft_putstr("\n");
	return (0);
}

int		show_live(t_data *data, t_champ *champ)
{
	if (!(data->verbosity & 1))
		return (0);
	ft_putstr("Player ");
	ft_putnbr(champ->champ_rank);
	ft_putstr(" (");
	ft_putstr(champ->prog_name);
	ft_putstr(") is said to be alive\n");
	return (0);
}

//Process 1 hasn't lived for 50 cycles (CTD 36)
int		show_process_death(t_data *data, t_process *process)
{
	if (!(data->verbosity & 8))
		return (0);
	ft_putstr("Process ");
	ft_putnbr(process->id);
	ft_putstr(" hasn't lived for ");
	ft_putnbr(data->turn - process->last_live_turn);
	ft_putstr(" cycles (CTD ");
	ft_putnbr(data->max_cycles);
	ft_putstr(")\n");
	return (0);
}
