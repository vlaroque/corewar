#include "corewar.h"

int		it_live(t_data *data, t_process *process, int champ_id)
{
	data->lives_count++;
	if (data->lives_count >= NBR_LIVE)
	{
		if (data->max_cycles - CYCLE_DELTA > 0)
			data->max_cycles -= CYCLE_DELTA;
	}
	process->life++;
	
	return (champ_id);
}

//void	*ft_memcpy(void *dst, const void *src, size_t n)

int		it_fork(t_data *data, t_process *process, int pc)
{
	new_process(data, pc, 0);
	ft_memcpy(data->processes, process, sizeof(t_process));
	op_bzero(&data->processes->todo, sizeof(t_todo));
	data->processes->pc = pc;
	return (0);
}

int		it_aff(t_data *data, t_process *process, char pc)
{
	write(0, pc, 1);
	return (0);
}

int		execute_operation(t_data *data, t_process *process)
{
	if (!process->todo.something_to_do)
		return (0);
	if (process->todo.life_cmd)
		it_live(data, process, process->todo.champ_id_life);
	if (process->todo.cmd_write_on_mars)
		write_int_mars(data, process->todo.mars_content, process->todo.pc);
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
