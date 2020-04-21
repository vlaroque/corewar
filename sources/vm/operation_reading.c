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
//#include "../common/op.c"

t_octet		bits_to_octet_type(t_octet two_bits)
{
	if (two_bits == 1)
		return (T_REG);
	else if (two_bits == 2)
		return (T_DIR);
	else if (two_bits == 3)
		return (T_IND);
	else
		return (0);
}

t_octet		*decode_encoding_byte(t_data *data, t_process *process,
		t_octet *tmp_types)
{
	char	c;

	c = data->mars[(process->pc + 1) % MEM_SIZE];
	tmp_types[0] = bits_to_octet_type((c >> (3 * 2)) & 3);
	tmp_types[1] = bits_to_octet_type((c >> (2 * 2)) & 3);
	tmp_types[2] = bits_to_octet_type((c >> (1 * 2)) & 3);
	tmp_types[3] = bits_to_octet_type((c >> (0 * 2)) & 3);
	return (tmp_types);
}

int			types_fill(t_data *data, t_process *process)
{
	t_octet		tmp_types[4];
	t_octet		*types;
	
	if (op_tab[process->tmp_mem.op - 1].encoding_byte)
		types = decode_encoding_byte(data, process, tmp_types);
	else
		types = op_tab[process->tmp_mem.op - 1].param_possible_types;
	return (0);
}

int			read_operation(t_data *data, t_process *process)
{
	t_octet		args_types[4];

	process->tmp_mem.pc_delta = 0;
	process->tmp_mem.op = data->mars[process->pc + process->tmp_mem.pc_delta];
	if (process->tmp_mem.op <= 0 || process->tmp_mem.op >= 17)
	{
		process->tmp_mem.op = 0;
		return (0);
	}
	types_fill(data, process);

	op_just_next(data, process);
	usleep(100000);
	return (1);
}
