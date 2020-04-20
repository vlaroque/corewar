/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_reading.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 08:01:15 by vlaroque          #+#    #+#             */
/*   Updated: 2020/03/10 16:04:56 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "op.h"
#include "corewar.h"
#include "../common/op.c"


int		(*op_fun[18])(t_data *, t_process *) = {
op_just_next,
op_live,
op_ld,
op_st,
op_add,
op_sub,
op_and,
op_or,
op_xor,
op_zjmp,
op_ldi,
op_sti,
op_fork,
op_lld,
op_lldi,
op_lfork,
op_aff,
};

int		op_just_next(t_data *data, t_process *process)
{
	process->todo.something_to_do = 1;
	process->todo.pc_add = 1;
	return(1);
}

int			read_operation(t_data *data, t_process *process)
{
	int		pc;

	pc = process->pc;
	op_just_next(data, process);
	usleep(100000);
	return (1);
}
