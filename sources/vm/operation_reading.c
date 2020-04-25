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
#include "operation_reading.h"
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

int			arg_size(int op, t_octet type)
{
	if (type == T_REG)
		return (1);
	else if (type == T_IND)
		return (2);
	else if (type == T_DIR)
	{
		if (op_tab[op - 1].direct_size_two)
			return (2);
		else
			return (4);
	}
	return (0);
}

int			arg_content_fill(t_data *data, t_args *arg, int pc)
{
	if (arg->size == 1)
		arg->octet_data = read_oct_mars(data, pc);
	else if (arg->size == 2)
		arg->short_data = read_short_mars(data, pc);
	else if (arg->size == 4)
		arg->int_data = read_short_mars(data, pc);
	return(arg->size);
}

int			args_fill(t_data *data, t_process *process, t_cache *c)
{
	t_octet		*types;
	int			i;

	i = 0;
	if (op_tab[c->op - 1].encoding_byte)
	{
		types = decode_encoding_byte(data, process, &(c->types[4]));
		c->pc_delta += 1;
	}
	else
		types = op_tab[c->op - 1].types_tab;
	while (i < op_tab[c->op - 1].param_number)
	{
		c->args[i].type = types[i];
		c->args[i].size = arg_size(c->op, types[i]);
		c->pc_delta += arg_content_fill(data, &(c->args[i]),
				(process->pc + c->pc_delta) % MEM_SIZE);
		i++;
	}
	return (0);
}

int			read_operation(t_data *data, t_process *process)
{
	t_cache		c;
	t_octet		args_types[4];

	c.pc_delta = 0;
	c.op = data->mars[process->pc];
	if (c.op <= 0 || c.op >= 17)
	{
		c.op = 0;
		op_just_next(data, process);
		return (0);
	}
	args_fill(data, process, &c);
	process->cooldown = op_tab[c.op - 1].cycle;
	process->todo.something_to_do = 1;
	process->todo.pc_add = c.pc_delta;

	usleep(1000000);
	return (1);
}
