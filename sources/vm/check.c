#include "op.h"
#include "corewar.h"

int		death_reaper(t_data *data)
{
	t_process		*p;
	t_process		**previous;

	p = data->processes;
	previous = &(data->processes);
	while (p)
	{
		if (p->lives_count <= 0)
		{
			*previous = p->next;
			free(p);
			p = *previous;
		}
		else
		{
			p->lives_count = 0;
			previous = &p->next;
			p = p->next;
		}
	}
	return (0);
}

int		checks(t_data *data)
{
	death_reaper(data);
	if (data->lives_count >= NBR_LIVE)
	{
		data->max_cycles -= CYCLE_DELTA;
		data->checks_count = 0;
	}
	else if (data->checks_count >= MAX_CHECKS - 1)
	{
		data->max_cycles -= CYCLE_DELTA;
		data->checks_count = 0;
	}
	else
		data->checks_count += 1;
	data->lives_count = 0;
	data->cycles_to_die = data->max_cycles;
	return (0);
}
