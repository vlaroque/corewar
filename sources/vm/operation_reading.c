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

/*
 ** fill the size of arguments according to the op and encoding byte or the bits
 ** sent without encoding byte
 */

int		fill_arg(t_arg *arg, t_octet bits, int direct_size_two)
{
	if (bits == 1)
	{
		arg->type = T_REG;
		arg->len = 1;
	}
	else if (bits == 2)
	{
		arg->type = T_DIR;
		if (direct_size_two)
			arg->len = 2;
		else
			arg->len = 4;
	}
	else if (bits == 3)
	{
		arg->type = T_IND;
		arg->len = 2;
	}
	return (0);
}

/*
 ** get arguments types for operations without encoding byte
 */

int		get_without_encod_byte(t_data *data, t_process *process, int *pc)
{
	int		arg_nbr;
	int		i;
	t_octet	bit;
	
	arg_nbr = op_tab[process->instruction.op_id].param_number;
	i = 0;
	while (arg_nbr)
	{
		if (op_tab[process->instruction.op_id].param_possible_types[i] == T_REG)
			bit = 1;
		else if (op_tab[process->instruction.op_id].param_possible_types[i] == T_DIR)
			bit = 2;
		else if (op_tab[process->instruction.op_id].param_possible_types[i] == T_IND)
			bit = 3;
		else
		{
			write(1, "ERROR\n", 6);
			exit (1);
		}
		fill_arg(&process->instruction.args[i], bit,
				op_tab[process->instruction.op_id].direct_size_two);
		i++;
		arg_nbr--;
	}
	return (0);
}

/*
 ** get arguments types for operations with encoding byte
 */

int		get_encoding_byte(t_data *data, t_process *process, int *pc)
{
	int		arg_nbr;
	int		i;
	t_octet	encod;

	i = 0;
	arg_nbr = op_tab[process->instruction.op_id].param_number;
	process->instruction.encod = data->mars[*pc];
	encod = data->mars[*pc];
	while (arg_nbr)
	{
		fill_arg(&process->instruction.args[i], 3 & (encod >> ((3 * 2) - (i * 2))),
				op_tab[process->instruction.op_id].direct_size_two);
		i++;
		arg_nbr--;
	}
	(*pc)++;
	return (0);
}

/*
 ** check if the pointed byte is an op_code and store it in process
 */

int		get_op(t_data *data, t_process *process, int *pc)
{
	int		operation;

	operation = 0;
	while (op_tab[operation].op_code != 0)
	{
		if (op_tab[operation].op_code == data->mars[process->pc])
		{
			process->instruction.op = op_tab[operation].op_code;
			return (operation);
		}
		operation++;
	}
	(*pc)++;
	return (-1);
}

//void	*ft_memcpy(void *dst, const void *src, size_t n)

int			fill_instruction(t_data *data, t_process *process, int *pc)
{
	int		i;

	i = 0;
	while (i < process->instruction.nbr_args)
	{
		ft_memcpy(process->instruction.args[i].content, &(data->mars[*pc]), process->instruction.args[i].len);
		*pc += process->instruction.args[i].len;
		i++;
	}
	return (0);
}

int			read_operation(t_data *data, t_process *process)
{
	int		pc;

	pc = process->pc;

//	op_bzero(&process->instruction, sizeof(t_instruction));
	process->instruction.op_id = get_op(data, process, &pc);
	if (process->instruction.op_id < 0)
		return (0);
	process->instruction.pc = process->pc;
	process->instruction.nbr_args = op_tab[process->instruction.op_id].param_number;
	process->cooldown = op_tab[process->instruction.op_id].cycle;
	pc++;
	
	if (op_tab[process->instruction.op_id].encoding_byte)
		get_encoding_byte(data, process, &pc);
	else
		get_without_encod_byte(data, process, &pc);
	fill_instruction(data, process, &pc);
	process->pc = pc;
	return (1);
}
