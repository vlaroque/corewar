#include "corewar.h"

int		it_live(t_data *data, t_process *process, int champ_id)
{
	return (champ_id);
}

int		it_fork(t_data *data, t_process *process, int pc)
{
	return (0);
}

int		it_aff(t_data *data, t_process *process, char pc)
{
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
	if (process->todo.something_to_do)
		return (1);
	else
		read_int_mars(data, process->todo.pc);
}
