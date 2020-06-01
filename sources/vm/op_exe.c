#include <unistd.h>
#include "corewar.h"

int		it_live(t_data *data, t_process *process, int champ_id)
{
	t_champ		*champ;

	data->lives_count++;
	process->lives_count++;
	champ = data->champs;
	while (champ)
	{
		if (champ->id == champ_id)
			data->last_alive = champ_id;
		champ = champ->next;
	}
	
	return (champ_id);
}

//void	*ft_memcpy(void *dst, const void *src, size_t n)

void	process_copy(t_process *src, t_process *dst)
{
	int		i;

	dst->carry = src->carry;
	i = 0;
	while (i < REG_NUMBER + 1)
	{
		dst->reg[i] = src->reg[i];
		i++;
	}
}

int		it_fork(t_data *data, t_process *process, int pc)
{
	new_process(data, pc, 0);
	process_copy(process, data->processes);
	op_bzero(&data->processes->todo, sizeof(t_todo));
	data->processes->pc = pc;
	return (0);
}

int		it_aff(t_data *data, t_process *process, char pc)
{
	write(0, &pc, 1);
	return (0);
}

void		color_mars(t_data *data, int color, int pc)
{
	data->colors[pc % MEM_SIZE] = color;
	data->colors[(pc + 1) % MEM_SIZE] = color;
	data->colors[(pc + 2) % MEM_SIZE] = color;
	data->colors[(pc + 3) % MEM_SIZE] = color;
}

int		execute_operation(t_data *data, t_process *process)
{
	if (!process->todo.something_to_do)
		return (0);
	if (process->todo.pc_add)
		process->pc = pc_fix((process->todo.pc_add + process->pc) % MEM_SIZE);
	if (process->todo.cmd_life)
		it_live(data, process, process->todo.champ_id_life);
	if (process->todo.cmd_write_on_mars)
	{
		write_int_mars(data, process->todo.mars_content, process->todo.pc);
		color_mars(data, process->color, process->todo.pc);
	}
	if (process->todo.cmd_change_register)
		process->reg[process->todo.reg] = process->todo.reg_content;
	if (process->todo.cmd_change_carry)
		process->carry = process->todo.carry_content;
	if (process->todo.cmd_fork)
		it_fork(data, process, process->todo.fork_pc);
	if (process->todo.cmd_aff)
		it_aff(data, process, process->todo.char_to_aff);
	op_bzero(&process->todo, sizeof(t_todo));
	return (1);
}
