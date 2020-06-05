/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_processor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 20:27:43 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/05 20:34:46 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		op_just_next(t_data *data, t_process *process, t_cache *c)
{
	process->todo.something_to_do = 1;
	process->todo.pc_add = 1;
	return (1);
}
