/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live_aff_badenc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:44:12 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/12 21:26:49 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		op_live(t_data *data, t_process *process, t_cache *c)
{
	(void)data;
	process->todo.cmd_life = 1;
	process->todo.champ_id_life = c->args[0].int_data;
	return (0);
}

int		op_aff(t_data *data, t_process *process, t_cache *c)
{
	(void)data;
	process->todo.cmd_aff = 1;
	process->todo.char_to_aff = c->args[0].octet_data;
	return (0);
}

int		op_bad_encoding_byte(t_data *data, t_process *process, t_cache *c)
{
	(void)data;
	(void)process;
	(void)c;
	return (0);
}
