/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   todo_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 20:59:56 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/05 21:09:42 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	todo_change_reg(t_process *p, int reg_id, int content)
{
	char		c;

	p->todo.cmd_change_register = 1;
	p->todo.reg = reg_id;
	p->todo.reg_content = content;
}

void	todo_write_mars(t_process *p, int where, int what)
{
	p->todo.cmd_write_on_mars = 1;
	p->todo.pc = where;
	p->todo.mars_content = what;
}

void	todo_fork(t_process *p, int where)
{
	p->todo.cmd_fork = 1;
	p->todo.fork_pc = where;
}

void	todo_carry(t_process *p, int carry)
{
	p->todo.cmd_change_carry = 1;
	p->todo.carry_content = carry;
}

void	todo_change_pc(t_process *p, int pc)
{
	int		res;

	res = pc % IDX_MOD;
	p->todo.pc_add = res;
}
