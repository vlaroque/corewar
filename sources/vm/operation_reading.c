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

int			arg_content_fill(t_data *data, t_cache *c, t_args *arg, int pc)
{
	if (arg->size == 1)
	{
		arg->octet_data = read_oct_mars(data, pc);
		if (arg->octet_data < 1 || arg->octet_data > 16)
			c->op = 17;
	}
	else if (arg->size == 2)
		arg->short_data = read_short_mars(data, pc);
	else if (arg->size == 4)
		arg->int_data = read_int_mars(data, pc);
	return(arg->size);
}

int			args_fill(t_data *data, t_process *process, t_cache *c)
{
	t_octet		*types;
	int			i;

	if (c->op == 0)
		return (0);
	i = 0;
	c->pc_delta += 1;
	if (op_tab[c->op - 1].encoding_byte)
	{
		types = decode_encoding_byte(data, process, &(c->types[4]));
		if (incorrect_encoding_byte(c->op, types))
		{
			if (data->debug_option)
				printf("invalid op\n");
			c->bad_encoding_byte = 1;
		}
		c->pc_delta += 1;
	}
	else
		types = op_tab[c->op - 1].types_tab;
	while (i < op_tab[c->op - 1].param_number)
	{
		c->args[i].type = types[i];
		c->args[i].size = arg_size(c->op, types[i]);
		c->pc_delta += arg_content_fill(data, c, &(c->args[i]),
				(process->pc + c->pc_delta) % MEM_SIZE);
		i++;
	}
	return (0);
}

int			read_operation(t_data *data, t_process *process)
{
	t_cache		c;

	if (data->debug_option)
		printf("p[%d] pc[%d] read opc[%d]\n", process->id, process->pc, data->mars[process->pc]);
	op_bzero(&c, sizeof(t_cache));
	c.pc_delta = 0;
	c.bad_encoding_byte = 0;
	c.op = process->op;
	args_fill(data, process, &c);
	if (c.bad_encoding_byte)
		c.op = 17;
	pre_execute_op(data, process, &c);
	return (1);
}
