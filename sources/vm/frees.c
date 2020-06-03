#include "op.h"
#include "corewar.h"

int		free_data(t_data *data)
{
	t_champ		*champ;
	t_champ		*champ_to_free;
	t_process	*process;
	t_process	*process_to_free;

	champ = data->champs;
	process = data->processes;
	while (champ)
	{
		champ_to_free = champ;
		champ = champ->next;
		free (champ_to_free);
	}
	while (process)
	{
		process_to_free = process;
		process = process->next;
		free (process_to_free);
	}
	return (0);
}

int		exit_error(t_data *data, char* str)
{
	free_data(data);
	ft_putstr(str);
	return (0);
}
