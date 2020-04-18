#include "corewar.h"

t_octet		read_oct_mars(t_data *data, int pc)
{
	return (data->mars[pc % MEM_SIZE]);
}

short		read_short_mars(t_data *data, int pc)
{
	t_subint ret;

	ret.char_nbr[1] = read_oct_mars(data, pc);
	ret.char_nbr[0] = read_oct_mars(data, pc + 1);
	return (ret.short_nbr);
}

int			read_int_mars(t_data *data, int pc)
{
	t_subint ret;

	ret.char_nbr[3] = read_oct_mars(data, pc);
	ret.char_nbr[2] = read_oct_mars(data, pc + 1);
	ret.char_nbr[1] = read_oct_mars(data, pc + 2);
	ret.char_nbr[0] = read_oct_mars(data, pc + 3);
	return (ret.nbr);
}
