/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_from_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 20:40:35 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/05 20:43:13 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "corewar.h"

int		get_int_from_direct_arg(t_data *d, t_process *p, t_args *arg,
		int idx_lim)
{
	int		res;

	if (arg->type == T_REG)
		res = p->reg[arg->octet_data];
	else if (arg->type == T_IND && idx_lim)
		res = read_int_mars(d, ((p->pc + arg->short_data) % IDX_MOD)
				% MEM_SIZE);
	else if (arg->type == T_IND)
		res = read_int_mars(d, (p->pc + arg->short_data) % MEM_SIZE);
	else if (arg->type == T_DIR)
		res = arg->int_data;
	return (res);
}

int		get_int_from_indirect_arg(t_data *d, t_process *p, t_args *arg,
		int idx_lim)
{
	int		res;

	if (arg->type == T_REG)
		res = p->reg[arg->octet_data];
	else if (arg->type == T_IND && idx_lim)
		res = read_int_mars(d, ((p->pc + arg->short_data) % IDX_MOD)
				% MEM_SIZE);
	else if (arg->type == T_IND)
		res = read_int_mars(d, (p->pc + arg->short_data) % MEM_SIZE);
	else if (arg->type == T_DIR)
		res = arg->short_data;
	return (res);
}
